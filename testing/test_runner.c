#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <regex.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

// Configuration. CMake build takes care of all of these.
#ifndef SOURCE_DIR
#    error "Please define SOURCE_DIR to point to the root of the source directory."
#endif
#ifndef LIB_DIR
#    error "Please define LIB_DIR to point to the directory of built libraries."
#endif
#ifndef DEFAULT_TEST_DIR
#    error "Please define DEFAULT_TEST_DIR to point to a sensible tests directory (probably SOURCE_DIR/tests)."
#endif
#ifndef DEFAULT_CACHE_DIR
#    error "Please define DEFAULT_CACHE_DIR to point to a directory to store test build executables and cache."
#endif
#ifndef COMPILER
#    error "Please define COMPILER macro to path to the compiler to use."
#endif
#ifndef COMPILER_IS_CLANG
#    error "Please define COMPILER_IS_CLANG 0/1."
#endif
#ifndef COMPILER_IS_GCC
#    error "Please define COMPILER_IS_GCC 0/1."
#endif
#ifndef OPT_IS_DEBUG
#    error "Please define OPT_IS_DEBUG 0/1."
#endif
#ifndef OPT_IS_RELEASE
#    error "Please define OPT_IS_RELEASE 0/1."
#endif

extern char* const* environ;

enum {
    NUM_EXPECTATION_CLAUSES_SUPPORTED = 4,  // EXPECT:NO_COMPILE, EXPECT:STEPS, EXPECT:EXIT and REQUEST:SKIP
    TESTS_INITIAL_CAPACITY = 8,
    STRING_INITIAL_CAPACITY = 128,
    ALWAYS_ERROR_EXIT_CODE = 7,  // Tests are NOT allowed to expect to exit with code 7, so this will always be a test fail.
    MAX_NEGATIVE_COMPILE_RUNS = 999,
};
#define PATH_SEP '/'
#define PATH_SEP_STR "/"

#define MAX_NEGATIVE_COMPILE_RUNS_STR "999"
#define TEST_OUTPUT_FORMAT "------ BEGIN TEST OUTPUT ------\n%s\n------  END  TEST OUTPUT ------\n"
#define COMPILER_OUTPUT_FORMAT "------ BEGIN COMPILER OUTPUT ------\n%s\n------  END  COMPILER OUTPUT ------\n"

static char cmd_line_base[]
  = "" COMPILER "\0"
    "-std=c++20\0"
#if OPT_IS_DEBUG
    "-g\0"
#endif
#if OPT_IS_RELEASE
    "-O3\0"
#endif
  ;

static char cmd_line_include[]
  = "-nostdinc++\0"
    "-I" SOURCE_DIR PATH_SEP_STR "include\0"
    "-I" SOURCE_DIR PATH_SEP_STR "testing\0"
#if __APPLE__
    "-isysroot\0"
    "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/\0"
#endif
  ;

static char cmd_line_compile[]
  = "-c\0"       // Emit object file
    "-MMD\0"     // Emit dependencies file
    "-Werror\0"  // Add warning flags for positive-compile tests.
    "-Wall\0"
    "-Wextra\0"
    "-Wunused\0"
    "-Wpedantic\0"
    "-Wconversion\0"
    "-Wsign-conversion\0"
    "-Wsign-compare\0"
    "-Wnull-dereference\0"
    "-Wformat=2\0"
    "-Wimplicit-fallthrough\0"
    "-Wnon-virtual-dtor\0"
    "-Wold-style-cast\0"
    "-Wcast-align\0"
    "-Woverloaded-virtual\0"
#if COMPILER_IS_CLANG
    "-Wno-deprecated-volatile\0"     // TODO: fix this flag.
#endif
#if COMPILER_IS_GCC
    "-Wmisleading-indentation\0"
    "-Wduplicated-cond\0"
    "-Wduplicated-branches\0"
    "-Wlogical-op\0"
    "-Wno-unknown-pragmas\0"     // TODO: fix this flag.
    "-Wno-attributes\0"          // TODO: fix this flag.
    "-Wno-ignored-qualifiers\0"  // TODO: fix this flag.
#endif
    "-o\0"
    "@path_to_obj_file@\0"
    "-MF\0"
    "@path_to_dep_file@\0"
    "@path_to_source_file@\0";

static char cmd_line_neg_compile[]
  = "-fsyntax-only\0"
    "-DNEGATIVE_COMPILE_ITERATION=" MAX_NEGATIVE_COMPILE_RUNS_STR "\0"
    "@path_to_source_file@\0";

static char cmd_line_link[]
  =
#if COMPILER_IS_GCC
    "-nodefaultlibs\0"
#else
    "-nostdlib++\0"
#endif
    "@path_to_obj_file@\0"
    "-o\0"
    "@path_to_exe_file@\0"
    "" LIB_DIR PATH_SEP_STR "liblightcxx_static.a\0"
    "" LIB_DIR PATH_SEP_STR "libtesting.a\0"
#if COMPILER_IS_GCC
    "-lgcc\0"
    "-lgcc_eh\0"
#endif
#if !__APPLE__
    "-lc\0"
    "-lpthread\0"
    "-ldl\0"
#endif
#if __APPLE__
    "-L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib\0"
#endif
#if __APPLE__ && COMPILER_IS_GCC
    "-lSystem\0"
#endif
  ;

static bool flag_die_on_fail;
static bool flag_print_on_success;
static bool flag_todos;
static bool flag_colors;
static bool flag_interactive;
static int num_lines_interactive = 0;

static const char* color_error_begin(void) {
    if (!flag_colors) {
        return "";
    }
    return "\033[31m";
}
static const char* color_warning_begin(void) {
    if (!flag_colors) {
        return "";
    }
    return "\033[33m";
}
static const char* color_success_begin(void) {
    if (!flag_colors) {
        return "";
    }
    return "\033[32m";
}
static const char* color_reset(void) {
    if (!flag_colors) {
        return "";
    }
    return "\033[0m";
}

static void interactive_clear(void) {
    if (flag_interactive && num_lines_interactive > 0) {
        // Move to the start of the current line and clear it.
        printf("\r\033[K");
        for (int i = 1; i < num_lines_interactive; i++) {
            // move to the start of the previous line and clear it.
            printf("\033[F\033[K");
        }
        num_lines_interactive = 0;
    }
}

static void interactive_flush(void) {
    if (flag_interactive) {
        fflush(stdout);
    }
}

static __attribute__((format(printf, 1, 2))) void print_todo(const char* fmt, ...) {
    if (!flag_todos) {
        return;
    }
    printf("%sTODO%s: ", color_warning_begin(), color_reset());
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

static __attribute__((format(printf, 2, 3))) bool config_error(const char* test_path, const char* fmt, ...) {
    printf("%sMis-configured test%s %s\n\t", color_error_begin(), color_reset(), test_path);
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n\n");
    return false;
}

static __attribute__((__noreturn__)) __attribute__((format(printf, 1, 2))) void fatal_error(const char* fmt, ...) {
    printf("\n%sError%s: ", color_error_begin(), color_reset());
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

static const char* get_flag_raw(const char* flag, const char* env_var, const char* default_val, int* argc_ptr, char*** argv_ptr, bool take_next) {
    const char* val = NULL;
    char** argv = *argv_ptr;
    size_t flag_len = strlen(flag);
    for (int i = 0; i < *argc_ptr; i++) {
        if (argv[i][0] == '-') {
            char* flag_start = argv[i] + 1;
            if (argv[i][1] == '-') {
                flag_start++;
            }
            if (strncmp(flag_start, flag, flag_len)) {
                continue;
            }
            memmove(argv + i, argv + i + 1, sizeof(char*) * (size_t)((*argc_ptr) - i - 1));
            (*argc_ptr)--;
            if (flag_start[flag_len] == '\0') {
                if (take_next && i != *argc_ptr && argv[i][0] != '-') {
                    val = argv[i];  // take the next argument
                    memmove(argv + i, argv + i + 1, sizeof(char*) * (size_t)((*argc_ptr) - i - 1));
                    (*argc_ptr)--;
                } else {
                    val = flag_start + flag_len;
                }
            } else if (flag_start[flag_len] == '=') {
                val = flag_start + flag_len + 1;
            } else {
                val = flag_start + flag_len;
            }
            break;
        }
    }
    if (val == NULL) {
        val = getenv(env_var);
    }
    return val != NULL ? val : default_val;
}

static const char* get_flag_string(const char* flag, const char* env_var, const char* default_val, int* argc_ptr, char*** argv_ptr) {
    return get_flag_raw(flag, env_var, default_val, argc_ptr, argv_ptr, true);
}

static bool get_flag_bool(const char* flag, const char* env_var, bool default_val, int* argc_ptr, char*** argv_ptr) {
    const char* val = get_flag_raw(flag, env_var, default_val ? "1" : "0", argc_ptr, argv_ptr, false);
    return val[0] == '\0'
           || (strcasecmp(val, "no")
               && strcasecmp(val, "false")
               && strcasecmp(val, "off")
               && strcasecmp(val, "disabled")
               && strcasecmp(val, "0")
               && strcasecmp(val, "-"));
}

static int get_flag_int(const char* flag, const char* env_var, const char* default_val, int* argc_ptr, char*** argv_ptr) {
    const char* raw_val = get_flag_raw(flag, env_var, default_val, argc_ptr, argv_ptr, true);
    return atoi(raw_val);
}

static bool timespec_before(struct timespec a, struct timespec b) {
    if (a.tv_sec == b.tv_sec) {
        return a.tv_nsec < b.tv_nsec;
    }
    return a.tv_sec < b.tv_sec;
}

struct string_view {
    const char* start;
    const char* end;
};

static size_t sv_len(struct string_view view) {
    return (size_t)(view.end - view.start);
}

struct string {
    char* data;
    size_t len;
    size_t capacity;
};

static void string_clear(struct string* str) {
    str->len = 0;
    str->data[str->len] = '\0';
}

static void string_init(struct string* str) {
    str->capacity = STRING_INITIAL_CAPACITY;
    str->data = malloc(str->capacity);
    string_clear(str);
}

static void string_destroy(struct string* str) {
    free(str->data);
}

static void string_reserve(struct string* str, size_t sz) {
    if (str->capacity <= sz) {
        while (str->capacity <= sz) {
            str->capacity *= 2;
        }
        str->data = realloc(str->data, str->capacity);
    }
}

static void path_init_realpath(struct string* path, const char* from) {
    path->data = realpath(from, NULL);
    path->len = strlen(path->data);
    path->capacity = path->len + 1;
}

static void path_ensure_trailing_slash(struct string* path) {
    if (path->data[path->len - 1] != PATH_SEP) {
        string_reserve(path, path->len + 1);
        path->data[path->len++] = PATH_SEP;
        path->data[path->len] = '\0';
    }
}

static void path_append(struct string* path, const char* part) {
    if (part[0] == PATH_SEP && path->data[path->len - 1] == PATH_SEP) {
        part++;
    } else if (part[0] != PATH_SEP) {
        path_ensure_trailing_slash(path);
    }
    const size_t part_len = strlen(part);
    string_reserve(path, path->len + part_len);
    memcpy(path->data + path->len, part, part_len + 1);
    path->len += part_len;
}

static void path_pop(struct string* path) {
    if (path->data[path->len - 1] == PATH_SEP) {
        path->len--;
    }
    while (path->data[path->len - 1] != PATH_SEP) {
        path->len--;
    }
    path->data[path->len--] = '\0';
}

static void path_stat(const char* path, bool* exists, struct timespec* last_touch_ts, bool* is_dir) {
    struct stat st_buf;
    int result = stat(path, &st_buf);
    if (result != 0) {
        if (errno == ENOENT) {
            *exists = false;
            last_touch_ts->tv_sec = 0;
            last_touch_ts->tv_nsec = 0;
            *is_dir = false;
            return;
        }
        fatal_error("Failed stat() on %s: error=%d %s\n", path, errno, strerror(errno));
    }
    *exists = true;
#if __APPLE__
    *last_touch_ts = st_buf.st_mtimespec;
#else
    *last_touch_ts = st_buf.st_mtim;
#endif
    if ((st_buf.st_mode & S_IFDIR) != 0) {
        *is_dir = true;
    } else if ((st_buf.st_mode & S_IFREG) != 0) {
        *is_dir = false;
    } else {
        fatal_error("%s is not a regular file or a directory. st_mode=%d\n", path, (int)st_buf.st_mode);
    }
}

typedef double chronometer_t;

static chronometer_t chronometer_start(void) {
    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    return (double)start_time.tv_sec * 1e3 + (double)start_time.tv_nsec * 1.e-6;
}

static double chronometer_ms_elapsed(chronometer_t timer) {
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    return (double)end_time.tv_sec * 1e3 + (double)end_time.tv_nsec * 1.e-6 - timer;
}

struct cmd_line {
    char** argv;
    int argc;
    char* argv_buf;
    size_t argv_buf_size;
};

static void cmd_line_init(struct cmd_line* cmd_line, int num_sections, ...) {
    va_list sections;

    int num_args = 0;
    size_t argv_buf_size = 0;
    va_start(sections, num_sections);
    for (int section_id = 0; section_id < num_sections; section_id++) {
        const char* section = va_arg(sections, const char*);
        while (*section != '\0') {
            size_t arg_size = strlen(section);
            num_args += 1;
            section += arg_size + 1;
            argv_buf_size += arg_size + 1;
        }
    }
    va_end(sections);

    cmd_line->argc = 0;
    cmd_line->argv = malloc(sizeof(char*) * (size_t)(num_args + 1));
    cmd_line->argv_buf = malloc(sizeof(char) * argv_buf_size);
    cmd_line->argv_buf_size = 0;
    va_start(sections, num_sections);
    for (int section_id = 0; section_id < num_sections; section_id++) {
        const char* section = va_arg(sections, const char*);
        while (*section != '\0') {
            size_t arg_size = strlen(section);
            memcpy(cmd_line->argv_buf + cmd_line->argv_buf_size, section, arg_size + 1);
            cmd_line->argv[cmd_line->argc++] = cmd_line->argv_buf + cmd_line->argv_buf_size;
            section += arg_size + 1;
            cmd_line->argv_buf_size += arg_size + 1;
        }
    }
    va_end(sections);
    cmd_line->argv[cmd_line->argc] = NULL;
}

static void cmd_line_destroy(struct cmd_line* cmd_line) {
    free(cmd_line->argv_buf);
    free(cmd_line->argv);
}

static const char* cmd_line_to_str(struct cmd_line* cmd_line, struct string* str) {
    if (cmd_line->argc == 0) {
        string_clear(str);
        return str->data;
    }
    size_t argv0_size = strlen(cmd_line->argv[0]);
    size_t size = argv0_size + (size_t)(cmd_line->argc - 1) /* spaces */;
    for (int i = 1; i < cmd_line->argc; i++) {
        size_t arg_size = strlen(cmd_line->argv[i]);
        size += arg_size;
        size_t escape_size = 0;
        for (size_t j = 0; j < arg_size; j++) {
            if (cmd_line->argv[i][j] == '"' || cmd_line->argv[i][j] == '\\') {
                escape_size += 1;
            }
        }
        size += escape_size;
        if (escape_size) {
            size += 2;
        }
    }
    string_reserve(str, size);
    memcpy(str->data, cmd_line->argv[0], argv0_size);
    size = argv0_size;
    for (int i = 1; i < cmd_line->argc; i++) {
        str->data[size++] = ' ';
        bool escape = false;
        char* start = str->data + size;
        for (char* p = cmd_line->argv[i]; *p; p++) {
            if (*p == '"' || *p == '\\') {
                str->data[size++] = '\\';
                escape = true;
            }
            str->data[size++] = *p;
        }
        if (escape) {
            memmove(start + 1, start, (size_t)((str->data + size) - start));
            *start = '"';
            str->data[size++] = '"';
        }
    }
    str->len = size;
    str->data[str->len] = '\0';
    return str->data;
}

struct subprocess {
    pid_t pid;
    int child_stdout_fd;
    int child_stderr_fd;
    bool is_done;
    int exit_status;
    struct string output_buf;
};

static void subprocess_init(struct subprocess* result) {
    result->pid = 0;
    result->child_stdout_fd = 0;
    result->child_stderr_fd = 0;
    result->is_done = false;
    result->exit_status = 0;
    string_init(&result->output_buf);
}

static void subprocess_destroy(struct subprocess* result) {
    string_destroy(&result->output_buf);
}

enum subprocess_fail_exit {
    fail_exit_abort,
    fail_exit_code_0,
};

static void subprocess_start(struct subprocess* result, struct cmd_line* cmd, enum subprocess_fail_exit exit_strategy) {
    int stdout_pipe_fd[2];
    int stderr_pipe_fd[2];
    if (pipe(stdout_pipe_fd) < 0) {
        fatal_error("pipe failed: error: %d %s\n", errno, strerror(errno));
    }
    if (pipe(stderr_pipe_fd) < 0) {
        fatal_error("pipe failed: error: %d %s\n", errno, strerror(errno));
    }
    pid_t child_pid = fork();
    if (child_pid < 0) {
        fatal_error("fork failed: error: %d %s\n", errno, strerror(errno));
    }
    if (child_pid == 0) {
        close(stdout_pipe_fd[0]);                          // close pipe read end in child
        close(stderr_pipe_fd[0]);                          // close pipe read end in child
        if (dup2(stdout_pipe_fd[1], STDOUT_FILENO) < 0) {  // pipe stdout to parent
            fprintf(stderr, "[CHILD]: dup2 failed: error: %d %s\n", errno, strerror(errno));
            if (exit_strategy == fail_exit_abort) {
                abort();
            } else {
                _Exit(exit_strategy == fail_exit_code_0 ? 0 : ALWAYS_ERROR_EXIT_CODE);
            }
        }
        close(stdout_pipe_fd[1]);  // close pipe write end after dup

        if (dup2(stderr_pipe_fd[1], STDERR_FILENO) < 0) {  // pipe stderr to parent
            fprintf(stderr, "[CHILD]: dup2 failed: error: %d %s\n", errno, strerror(errno));
            if (exit_strategy == fail_exit_abort) {
                abort();
            } else {
                _Exit(exit_strategy == fail_exit_code_0 ? 0 : ALWAYS_ERROR_EXIT_CODE);
            }
        }
        close(stderr_pipe_fd[1]);  // close pipe write end after dup

        execve(cmd->argv[0], cmd->argv, environ);
        fprintf(stderr, "[CHILD]: execve failed: error: %d %s\n", errno, strerror(errno));
        if (exit_strategy == fail_exit_abort) {
            abort();
        } else {
            exit(exit_strategy == fail_exit_code_0 ? 0 : 1);
        }
    }

    result->pid = child_pid;

    close(stdout_pipe_fd[1]);  // close write end in parent.
    if (fcntl(stdout_pipe_fd[0], F_SETFL, O_NONBLOCK) < 0) {
        fatal_error("fcntl(stdout_pipe_fd[0], F_SETFL, O_NONBLOCK) failed: error: %d %s\n", errno, strerror(errno));
    }
    result->child_stdout_fd = stdout_pipe_fd[0];

    close(stderr_pipe_fd[1]);  // close write end in parent.
    if (fcntl(stderr_pipe_fd[0], F_SETFL, O_NONBLOCK) < 0) {
        fatal_error("fcntl(stderr_pipe_fd[0], F_SETFL, O_NONBLOCK) failed: error: %d %s\n", errno, strerror(errno));
    }
    result->child_stderr_fd = stderr_pipe_fd[0];

    result->is_done = false;
    result->exit_status = 0;
    string_clear(&result->output_buf);
}

static void subprocess_poll_output(struct subprocess* result, int fd, bool to_eof) {
    while (1) {
        // Ensure at least 512 bytes can be read from the subprocess output in one call to read().
        string_reserve(&result->output_buf, result->output_buf.len + 512);
        errno = 0;
        ssize_t num_bytes = read(fd, result->output_buf.data + result->output_buf.len, result->output_buf.capacity - result->output_buf.len);
        if (num_bytes < 0) {
            if (errno == EAGAIN) {
                if (to_eof) {
                    continue;  // keep waiting.
                }
                break;
            }
            fatal_error("read failed: errno=%d message=%s\n", errno, strerror(errno));
        }
        if (num_bytes == 0) {
            break;
        }
        result->output_buf.len += (size_t)num_bytes;
    }
}

static bool subprocess_poll(struct subprocess* result) {
    if (result->is_done) {
        return true;
    }
    pid_t status;
    while (1) {
        errno = 0;
        status = waitpid(result->pid, &result->exit_status, WNOHANG);
        if (status >= 0) {
            break;
        }
        if (errno == EINTR) {
            continue;
        }
        fatal_error("waitpid failed: errno=%d message=%s\n", errno, strerror(errno));
    }
    if (status == 0) {
        subprocess_poll_output(result, result->child_stdout_fd, false);
        subprocess_poll_output(result, result->child_stderr_fd, false);
        return false;
    }
    if (fcntl(result->child_stdout_fd, F_SETFL, 0) < 0) {
        fatal_error("fcntl(child_stdout_fd, F_SETFL, 0) failed: error: %d %s\n", errno, strerror(errno));
    }
    if (fcntl(result->child_stderr_fd, F_SETFL, 0) < 0) {
        fatal_error("fcntl(child_stderr_fd, F_SETFL, 0) failed: error: %d %s\n", errno, strerror(errno));
    }
    subprocess_poll_output(result, result->child_stdout_fd, true);
    subprocess_poll_output(result, result->child_stderr_fd, true);
    result->output_buf.data[result->output_buf.len] = '\0';
    close(result->child_stdout_fd);
    close(result->child_stderr_fd);
    return true;
}

struct test {
    struct timespec source_file_lmt;
    char* file_path;      // This is also where the memory buffer for all these paths starts.
    char* test_name;      // [<section>].<test_file_stem>
    char* dep_file_path;  // <build_cache_dir><section>.<test_file_stem>.d   (<build_cache_dir> must end in PATH_SEP)  // TODO: Maybe don't store, copy on-demand.
    char* obj_file_path;  // <build_cache_dir><section>.<test_file_stem>.o   (<build_cache_dir> must end in PATH_SEP)  // TODO: Maybe don't store, copy on-demand.
    char* exe_file_path;  // <build_cache_dir><section>.<test_file_stem>     (<build_cache_dir> must end in PATH_SEP)
    char* expect_steps;
    int expect_exit_code;
    int expect_exit_signal;
    int expect_no_compile_num_runs;
    bool expect_no_compile_has_pattern;
    regex_t expect_no_compile_pattern;

    struct timespec obj_file_lmt;
    bool requires_re_compile;
    bool requires_re_link;
};

// If a test fails, it will stay in one of the intermediary steps (to know when it failed).
enum test_run_step {
    s_starting = 0,
    s_compiling = 1,
    s_linking = 2,
    s_running = 3,
    s_success = 4,
};
struct test_run {
    size_t id;
    size_t num_tests;
    struct test* test;
    bool failed;
    enum test_run_step step;
    int no_compile_run_id;
    struct subprocess proc;
    struct cmd_line compile_command;
    struct cmd_line link_command;
    struct cmd_line negative_compile_command;
    struct string scratch_space;
};

static void test_run_init(struct test_run* test_run) {
    subprocess_init(&test_run->proc);
    cmd_line_init(&test_run->compile_command, 3, cmd_line_base, cmd_line_include, cmd_line_compile);
    cmd_line_init(&test_run->link_command, 2, cmd_line_base, cmd_line_link);
    cmd_line_init(&test_run->negative_compile_command, 3, cmd_line_base, cmd_line_include, cmd_line_neg_compile);
    string_init(&test_run->scratch_space);
}

static void test_run_destroy(struct test_run* test_run) {
    string_destroy(&test_run->scratch_space);
    cmd_line_destroy(&test_run->negative_compile_command);
    cmd_line_destroy(&test_run->link_command);
    cmd_line_destroy(&test_run->compile_command);
    subprocess_destroy(&test_run->proc);
}

struct tests_db {
    // Tests
    struct test* tests;
    size_t num_tests;
    size_t capacity;

    // Runners
    size_t num_test_runs;
    struct test_run* test_runs;

    // Stats
    size_t num_mis_configured_tests;
    size_t num_tests_to_compile;
    size_t num_tests_to_link;
    size_t num_neg_compile_tests;
};

static void tests_db_init(struct tests_db* tests, int num_jobs) {
    tests->num_tests = 0;
    tests->capacity = TESTS_INITIAL_CAPACITY;
    tests->tests = malloc(sizeof(struct test) * tests->capacity);
    tests->num_mis_configured_tests = 0;
    tests->num_tests_to_compile = 0;
    tests->num_tests_to_link = 0;
    tests->num_test_runs = (size_t)num_jobs;
    tests->test_runs = malloc(sizeof(struct test_run) * tests->num_test_runs);
    for (size_t i = 0; i < tests->num_test_runs; i++) {
        test_run_init(tests->test_runs + i);
    }
}

static void tests_db_destroy(struct tests_db* tests) {
    for (size_t i = 0; i < tests->num_test_runs; i++) {
        test_run_destroy(tests->test_runs + i);
    }
    free(tests->test_runs);
    for (size_t i = 0; i < tests->num_tests; i++) {
        free(tests->tests[i].file_path);
        if (tests->tests[i].expect_no_compile_has_pattern) {
            regfree(&tests->tests[i].expect_no_compile_pattern);
        }
    }
    free(tests->tests);
}

static bool parse_test_single_expectation(const char* file_contents, const char* pattern, struct string_view* result) {
    const size_t pattern_len = strlen(pattern);
    const char* cursor = file_contents;
    while (true) {
        if (strncmp(cursor, pattern, pattern_len) == 0) {
            result->start = cursor + pattern_len;
            while (*result->start == ' ' || *result->start == '\t') {
                result->start++;
            }
            result->end = strchr(result->start, '\n');
            if (result->end == NULL) {
                result->end = result->start + strlen(result->start);
            }
            while (result->start != result->end && (*(result->end - 1) == ' ' || *(result->end - 1) == '\t')) {
                result->end--;
            }
            return true;
        }
        cursor = strchr(cursor, '\n');
        if (cursor == NULL) {
            break;
        }
        cursor++;
    }
    result->start = result->end = NULL;
    return false;
}

static bool exit_expectation_config_error(const char* test_path, struct string_view expect_exit) {
    return config_error(test_path,
                        "Invalid EXPECT:EXIT request. Must be one of:\n"
                        "\t// EXPECT:EXIT CODE = n\n"
                        "\t// EXPECT:EXIT KILLED BY SIGNAL n\n"
                        "\t// EXPECT:EXIT KILLED BY SIGNAL SIGABRT\n"
                        "\n"
                        "\tInstead found: '// EXPECT:EXIT %.*s'",
                        (int)sv_len(expect_exit), expect_exit.start);
}

static bool parse_exit_expectation(const char* test_path, struct string_view expect_exit, int* exit_code, int* exit_signal) {
    *exit_code = 0;
    *exit_signal = 0;
    if (expect_exit.start == NULL) {
        return true;
    }

    if (sv_len(expect_exit) > 7 && strncmp(expect_exit.start, "CODE = ", 7) == 0) {
        const char* cursor = expect_exit.start + 7;
        while (cursor != expect_exit.end) {
            if ('0' <= *cursor && *cursor <= '9') {
                *exit_code = (*exit_code) * 10 + *cursor - '0';
                cursor++;
            } else {
                return exit_expectation_config_error(test_path, expect_exit);
            }
        }
    } else if (sv_len(expect_exit) > 17 && strncmp(expect_exit.start, "KILLED BY SIGNAL ", 17) == 0) {
        if (sv_len(expect_exit) == 17 + 7 && strncmp(expect_exit.start + 17, "SIGABRT", 7) == 0) {
            *exit_signal = SIGABRT;
        } else {
            const char* cursor = expect_exit.start + 17;
            while (cursor != expect_exit.end) {
                if ('0' <= *cursor && *cursor <= '9') {
                    *exit_signal = *exit_signal * 10 + *cursor;
                    cursor++;
                } else {
                    return exit_expectation_config_error(test_path, expect_exit);
                }
            }
        }
    } else {
        return exit_expectation_config_error(test_path, expect_exit);
    }

    if (*exit_code == ALWAYS_ERROR_EXIT_CODE) {
        return config_error(test_path,
                            "Invalid EXPECT:EXIT request: exit code %d is reserved for expectation failures.\n"
                            "\tPick a different exit code to expect.",
                            ALWAYS_ERROR_EXIT_CODE);
    }
    return true;
}

static bool parse_no_compile_expectation(const char* test_path, struct string_view expect_no_compile, int* num_runs, bool* has_pattern, regex_t* pattern) {
    *num_runs = 0;
    *has_pattern = false;
    if (expect_no_compile.start == NULL) {
        return true;
    }

    const char* raw_pattern = "";
    *num_runs = atoi(expect_no_compile.start);
    if (*num_runs < 0 || *num_runs > MAX_NEGATIVE_COMPILE_RUNS) {
        return config_error(test_path,
                            "Invalid EXPECT:NO_COMPILE request: number of runs must be 1 to %d, got %d.",
                            MAX_NEGATIVE_COMPILE_RUNS, *num_runs);
    }
    if (*num_runs == 0) {
        *num_runs = 1;
        size_t pattern_len = sv_len(expect_no_compile);
        if (pattern_len < 2 || expect_no_compile.start[0] != '"' || expect_no_compile.end[-1] != '"') {
            return config_error(test_path,
                                "Invalid EXPECT:NO_COMPILE request: must be either number of runs, or pattern enclosed in '\"'.\n"
                                "\tInstead got: // EXPECT:NO_COMPILE %.*s",
                                (int)sv_len(expect_no_compile), expect_no_compile.start);
        }
        // This is "safe", because it points into the scratch space. Once the regex_t pattern is constructed,
        // this data is no longer used.
        // TODO: This should still be refactored.
        ((char*)expect_no_compile.end)[-1] = '\0';
        raw_pattern = expect_no_compile.start + 1;
    }
    *has_pattern = (raw_pattern[0] != '\0') && (raw_pattern[0] != '.' || raw_pattern[1] != '*' || raw_pattern[2] != '\0');
    if (*has_pattern) {
        int regcomp_status = regcomp(pattern, raw_pattern, REG_EXTENDED | REG_NOSUB);
        if (regcomp_status != 0) {
            char regerror_msg[256];
            regerror(regcomp_status, pattern, regerror_msg, 256);
            return config_error(test_path,
                                "Invalid EXPECT:NO_COMPILE request: failed to compile pattern '%s': %s",
                                raw_pattern, regerror_msg);
        }
    }
    return true;
}

// Parse the test source file to discover expectations.
// Results are pointing inside scratch_space. scratch_space may be resized, according to needs.
static bool parse_test_expectations(struct string* scratch_space,
                                    bool* misconfigured,
                                    const struct string* test_path,
                                    struct string_view* section,
                                    struct string_view* test_file_stem,
                                    struct string_view* skip_reason,
                                    struct string_view* expect_steps,
                                    int* expect_exit_code,
                                    int* expect_exit_signal,
                                    int* expect_no_compile_num_runs,
                                    bool* expect_no_compile_has_pattern,
                                    regex_t* expect_no_compile_pattern) {
    *misconfigured = false;

    // Parse the test path to discover section and test name stem.
    test_file_stem->end = test_path->data + test_path->len - 4;
    section->end = test_file_stem->end;
    while (*section->end != PATH_SEP) {
        section->end--;
    }
    test_file_stem->start = section->end + 1;
    section->start = section->end - 1;
    while (*section->start != PATH_SEP) {
        section->start--;
    }
    section->start++;

    errno = 0;
    FILE* test_source_file = fopen(test_path->data, "r");
    if (test_source_file == NULL) {
        fatal_error("Failed to fopen() test source file %s: error: %d %s", test_path->data, errno, strerror(errno));
    }
    if (ferror(test_source_file)) {
        fatal_error("Failed to read expectations from test file %s: fopen failed error: %d %s\n",
                    test_path->data, ferror(test_source_file), strerror(ferror(test_source_file)));
    }

    string_clear(scratch_space);
    for (int i = 0; i < NUM_EXPECTATION_CLAUSES_SUPPORTED;) {
        char* result = fgets(scratch_space->data + scratch_space->len, (int)(scratch_space->capacity - scratch_space->len), test_source_file);
        if (result == NULL || ferror(test_source_file)) {
            if (feof(test_source_file)) {
                break;
            }
            fatal_error("Failed to read expectations from test file %s: fgets failed error: %d %s\n",
                        test_path->data, ferror(test_source_file), strerror(ferror(test_source_file)));
        }
        scratch_space->len += strlen(scratch_space->data + scratch_space->len);
        if (scratch_space->len + 1 == scratch_space->capacity) {
            string_reserve(scratch_space, scratch_space->len + 1);
            continue;  // Didn't finish reading the line, skip incrementing loop counter.
        }
        i++;
    }
    fclose(test_source_file);

    parse_test_single_expectation(scratch_space->data, "// REQUEST:SKIP", skip_reason);
    if (skip_reason->start != NULL) {
        print_todo("skipped test [%.*s].%.*s : %.*s\n",
                   (int)sv_len(*section), section->start,
                   (int)sv_len(*test_file_stem), test_file_stem->start,
                   (int)sv_len(*skip_reason), skip_reason->start);
        return false;
    }

    parse_test_single_expectation(scratch_space->data, "// EXPECT:STEPS", expect_steps);

    struct string_view expect_exit;
    parse_test_single_expectation(scratch_space->data, "// EXPECT:EXIT", &expect_exit);
    if (!parse_exit_expectation(test_path->data, expect_exit, expect_exit_code, expect_exit_signal)) {
        *misconfigured = true;
        return false;
    }

    struct string_view expect_no_compile;
    parse_test_single_expectation(scratch_space->data, "// EXPECT:NO_COMPILE", &expect_no_compile);
    if (!parse_no_compile_expectation(test_path->data, expect_no_compile, expect_no_compile_num_runs, expect_no_compile_has_pattern, expect_no_compile_pattern)) {
        *misconfigured = true;
        return false;
    }
    return true;
}

static void tests_db_add_test(struct tests_db* tests, struct string* test_path, struct timespec lmt, struct string* build_cache_dir_path) {
    bool misconfigured;
    struct string_view section;
    struct string_view test_file_stem;
    struct string_view reason_skip;
    struct string_view expect_steps;
    int expect_exit_code;
    int expect_exit_signal;
    int expect_no_compile_num_runs;
    bool expect_no_compile_has_pattern;
    regex_t expect_no_compile_pattern;
    if (!parse_test_expectations(&tests->test_runs[0].scratch_space,
                                 &misconfigured,
                                 test_path,
                                 &section,
                                 &test_file_stem,
                                 &reason_skip,
                                 &expect_steps,
                                 &expect_exit_code,
                                 &expect_exit_signal,
                                 &expect_no_compile_num_runs,
                                 &expect_no_compile_has_pattern,
                                 &expect_no_compile_pattern)) {
        tests->num_mis_configured_tests += misconfigured;
        return;
    }

    if (tests->num_tests == tests->capacity) {
        tests->capacity *= 2;
        tests->tests = realloc(tests->tests, sizeof(struct test) * tests->capacity);
    }
    struct test* test = tests->tests + tests->num_tests;
    tests->num_tests++;

    const size_t file_path_len = test_path->len;
    const size_t test_name_len = 1 /*[*/ + sv_len(section) + 2 /*].*/ + sv_len(test_file_stem);
    const size_t dep_file_path_len = build_cache_dir_path->len + sv_len(section) + 1 /*.*/ + sv_len(test_file_stem) + 2 /*.d*/;
    const size_t obj_file_path_len = build_cache_dir_path->len + sv_len(section) + 1 /*.*/ + sv_len(test_file_stem) + 2 /*.o*/;
    const size_t exe_file_path_len = build_cache_dir_path->len + sv_len(section) + 1 /*.*/ + sv_len(test_file_stem);

    test->source_file_lmt = lmt;
    // Total memory required is sum of all of the above, plus null terminators.
    test->file_path = malloc(file_path_len + 1
                             + test_name_len + 1
                             + dep_file_path_len + 1
                             + obj_file_path_len + 1
                             + exe_file_path_len + 1
                             + sv_len(expect_steps) + 1);
    memcpy(test->file_path, test_path->data, test_path->len + 1);  // Include the null terminator.

    test->test_name = test->file_path + test_path->len + 1;
    test->test_name[0] = '[';
    memcpy(test->test_name + 1, section.start, sv_len(section));
    test->test_name[sv_len(section) + 1] = ']';
    test->test_name[sv_len(section) + 2] = '.';
    memcpy(test->test_name + sv_len(section) + 3, test_file_stem.start, sv_len(test_file_stem));
    test->test_name[test_name_len] = '\0';

    test->dep_file_path = test->test_name + test_name_len + 1;
    memcpy(test->dep_file_path, build_cache_dir_path->data, build_cache_dir_path->len);
    memcpy(test->dep_file_path + build_cache_dir_path->len, section.start, sv_len(section));
    test->dep_file_path[build_cache_dir_path->len + sv_len(section)] = '.';
    memcpy(test->dep_file_path + build_cache_dir_path->len + sv_len(section) + 1, test_file_stem.start, sv_len(test_file_stem));
    test->dep_file_path[build_cache_dir_path->len + sv_len(section) + 1 + sv_len(test_file_stem)] = '.';
    test->dep_file_path[build_cache_dir_path->len + sv_len(section) + 1 + sv_len(test_file_stem) + 1] = 'd';
    test->dep_file_path[dep_file_path_len] = '\0';

    test->obj_file_path = test->dep_file_path + dep_file_path_len + 1;
    memcpy(test->obj_file_path, build_cache_dir_path->data, build_cache_dir_path->len);
    memcpy(test->obj_file_path + build_cache_dir_path->len, section.start, sv_len(section));
    test->obj_file_path[build_cache_dir_path->len + sv_len(section)] = '.';
    memcpy(test->obj_file_path + build_cache_dir_path->len + sv_len(section) + 1, test_file_stem.start, sv_len(test_file_stem));
    test->obj_file_path[build_cache_dir_path->len + sv_len(section) + 1 + sv_len(test_file_stem)] = '.';
    test->obj_file_path[build_cache_dir_path->len + sv_len(section) + 1 + sv_len(test_file_stem) + 1] = 'o';
    test->obj_file_path[obj_file_path_len] = '\0';

    test->exe_file_path = test->obj_file_path + obj_file_path_len + 1;
    memcpy(test->exe_file_path, build_cache_dir_path->data, build_cache_dir_path->len);
    memcpy(test->exe_file_path + build_cache_dir_path->len, section.start, sv_len(section));
    test->exe_file_path[build_cache_dir_path->len + sv_len(section)] = '.';
    memcpy(test->exe_file_path + build_cache_dir_path->len + sv_len(section) + 1, test_file_stem.start, sv_len(test_file_stem));
    test->exe_file_path[build_cache_dir_path->len + sv_len(section) + 1 + sv_len(test_file_stem)] = '\0';

    test->expect_steps = test->exe_file_path + exe_file_path_len + 1;
    if (sv_len(expect_steps)) {
        memcpy(test->expect_steps, expect_steps.start, sv_len(expect_steps));
    }
    test->expect_steps[sv_len(expect_steps)] = '\0';

    test->expect_no_compile_num_runs = expect_no_compile_num_runs;
    test->expect_no_compile_has_pattern = expect_no_compile_has_pattern;
    test->expect_no_compile_pattern = expect_no_compile_pattern;

    test->expect_exit_code = expect_exit_code;
    test->expect_exit_signal = expect_exit_signal;
}

static void tests_db_scan_dir(struct tests_db* tests, struct string* test_path, struct string* build_cache_dir_path) {
    bool exists, is_dir;
    struct timespec lmt;
    path_stat(test_path->data, &exists, &lmt, &is_dir);
    if (!exists) {
        fatal_error("%s: No such file or directory.\n", test_path->data);
    }
    if (is_dir) {
        DIR* dir = opendir(test_path->data);
        if (dir == NULL) {
            fatal_error("Failed to opendir() directory %s: error=%d %s\n", test_path->data, errno, strerror(errno));
        }
        while (true) {
            errno = 0;
            struct dirent* entry = readdir(dir);
            if (entry == NULL) {
                if (errno != 0) {
                    fatal_error("Failed to readdir() directory %s: error=%d %s\n", test_path->data, errno, strerror(errno));
                }
                break;
            }
            if (entry->d_name[0] != '.' && strcmp(entry->d_name, "nothing_to_do.cpp") != 0) {
                path_append(test_path, entry->d_name);
                tests_db_scan_dir(tests, test_path, build_cache_dir_path);
                path_pop(test_path);
            }
        }
        closedir(dir);
    } else if (test_path->len > 4 && memcmp(test_path->data + test_path->len - 4, ".cpp", 4) == 0) {
        tests_db_add_test(tests, test_path, lmt, build_cache_dir_path);
    }
}

static void tests_db_scan(struct tests_db* tests, const char* test_dir, const char* build_cache_dir) {
    bool exists, is_dir;
    struct timespec lmt;
    path_stat(build_cache_dir, &exists, &lmt, &is_dir);
    if (!exists) {
        fatal_error("Cache directory %s does not exist.\n", build_cache_dir);
    }
    if (!is_dir) {
        fatal_error("Cache directory %s is not a directory.\n", build_cache_dir);
    }
    path_stat(test_dir, &exists, &lmt, &is_dir);
    if (!exists) {
        fatal_error("Tests path %s does not exist.\n", test_dir);
    }

    struct string build_cache_dir_path;
    path_init_realpath(&build_cache_dir_path, build_cache_dir);
    path_ensure_trailing_slash(&build_cache_dir_path);

    struct string test_path;
    path_init_realpath(&test_path, test_dir);

    tests_db_scan_dir(tests, &test_path, &build_cache_dir_path);

    string_destroy(&build_cache_dir_path);
    string_destroy(&test_path);
}

static bool find_header_dep_with_lmt_gt(struct string* scratch_space, struct timespec lmt, const char* dep_file_path) {
    FILE* dep_file = fopen(dep_file_path, "r");
    if (dep_file == NULL) {
        fatal_error("Failed to fopen() dependencies file %s: error: %d %s", dep_file_path, errno, strerror(errno));
    }
    if (ferror(dep_file)) {
        fatal_error("Failed to read test header dependencies from file %s: fopen failed error: %d %s\n",
                    dep_file_path, ferror(dep_file), strerror(ferror(dep_file)));
    }
    string_clear(scratch_space);
    while (!feof(dep_file)) {
        char* result = fgets(scratch_space->data + scratch_space->len, (int)(scratch_space->capacity - scratch_space->len), dep_file);
        if (result == NULL || ferror(dep_file)) {
            if (feof(dep_file)) {
                fclose(dep_file);
                return false;
            }
            fatal_error("Failed to read test header dependencies from file %s: fgets failed error: %d %s\n",
                        dep_file_path, ferror(dep_file), strerror(ferror(dep_file)));
        }
        scratch_space->len += strlen(scratch_space->data + scratch_space->len);
        if (scratch_space->len + 1 == scratch_space->capacity) {
            string_reserve(scratch_space, scratch_space->len + 1);
            continue;  // Didn't finish reading the line, continue reading.
        }
        // Tokenize the line to scan header dependencies
        while (scratch_space->len > 0
               && (scratch_space->data[scratch_space->len - 1] == ' '
                   || scratch_space->data[scratch_space->len - 1] == '\\'
                   || scratch_space->data[scratch_space->len - 1] == '\n')) {
            scratch_space->data[--scratch_space->len] = '\0';
        }
        scratch_space->data[scratch_space->len++] = ' ';
        scratch_space->data[scratch_space->len] = '\0';
        char* start = strchr(scratch_space->data, ':');
        char* p = strtok(start == NULL ? scratch_space->data : start + 1, " ");
        for (; p != NULL; p = strtok(NULL, " ")) {
            if (*p != '\0') {  // non-empty tokens only
                bool exists, is_dir;
                struct timespec header_lmt;
                path_stat(p, &exists, &header_lmt, &is_dir);  // TODO: cache map of header files lmt-s!
                // If we can't find a dependency, or it's somehow a directory now, re-compile.
                if (!exists || is_dir || timespec_before(lmt, header_lmt)) {
                    fclose(dep_file);
                    return true;
                }
                while (*p == ' ') {
                    p++;
                }
            }
        }
        string_clear(scratch_space);
    }
    fclose(dep_file);
    return false;
}

static bool check_test_requires_re_compile(struct string* scratch_space, struct test* test) {
    if (test->expect_no_compile_num_runs > 0) {
        // A negative compile test is never compiled (running the test involves doing the compilation).
        return false;
    }
    bool exists, is_dir;
    path_stat(test->obj_file_path, &exists, &test->obj_file_lmt, &is_dir);
    if (is_dir) {
        fatal_error("path to object file %s is a directory!\n", test->obj_file_path);
    }
    if (!exists || timespec_before(test->obj_file_lmt, test->source_file_lmt)) {
        // if the object file doesn't exist or is older than source file, must be compiled.
        return true;
    }

    struct timespec dep_file_lmt;
    path_stat(test->dep_file_path, &exists, &dep_file_lmt, &is_dir);
    if (is_dir) {
        fatal_error("path to dependencies file %s is a directory!\n", test->obj_file_path);
    }
    if (!exists || timespec_before(dep_file_lmt, test->source_file_lmt)) {
        // if the dependencies file doesn't exist or is older than source file, must be re-compiled.
        return true;
    }
    // Source file did not change. Check header dependencies now.
    return find_header_dep_with_lmt_gt(scratch_space, test->obj_file_lmt, test->dep_file_path);
}

static bool check_test_requires_re_link(struct test* test, struct timespec libs_lmt) {
    if (test->expect_no_compile_num_runs > 0) {
        // A negative compile test is never linked (running the test involves doing the compilation).
        return false;
    }
    if (test->requires_re_compile) {
        // A test that is recompiled must also be relinked.
        return true;
    }
    bool exe_exists, is_dir;
    struct timespec exe_lmt;
    path_stat(test->exe_file_path, &exe_exists, &exe_lmt, &is_dir);
    if (is_dir) {
        fatal_error("path to executable %s is a directory!\n", test->exe_file_path);
    }
    // If the executable is older than either the object file or the libs, will need to re-link.
    return !exe_exists || timespec_before(exe_lmt, libs_lmt) || timespec_before(exe_lmt, test->obj_file_lmt);
}

static void tests_db_prepare(struct tests_db* db) {
    struct timespec libs_lmt;
    libs_lmt.tv_sec = 0;
    libs_lmt.tv_nsec = 0;
    const char* libs[] = {
      LIB_DIR PATH_SEP_STR "liblightcxx_static.a",
      LIB_DIR PATH_SEP_STR "libtesting.a",
      NULL,
    };
    for (size_t i = 0; libs[i]; i++) {
        bool exists, is_dir;
        struct timespec lib_lmt;
        path_stat(libs[i], &exists, &lib_lmt, &is_dir);
        if (!exists) {
            fatal_error("library %s does not exist. Hint: run the cmake build before running the tests.\n", libs[i]);
        }
        if (is_dir) {
            fatal_error("expected to find library %s, but is a directory!\n", libs[i]);
        }
        if (timespec_before(libs_lmt, lib_lmt)) {
            libs_lmt = lib_lmt;
        }
    }

    db->num_tests_to_compile = 0;
    db->num_tests_to_link = 0;
    db->num_neg_compile_tests = 0;
    for (size_t i = 0; i < db->num_tests; i++) {
        db->tests[i].requires_re_compile = check_test_requires_re_compile(&db->test_runs[0].scratch_space, db->tests + i);
        db->num_tests_to_compile += db->tests[i].requires_re_compile;

        db->tests[i].requires_re_link = check_test_requires_re_link(db->tests + i, libs_lmt);
        db->num_tests_to_link += db->tests[i].requires_re_link;

        db->num_neg_compile_tests += (db->tests[i].expect_no_compile_num_runs > 0);
    }
}

static void test_run_print(struct test_run* test_run) {
    printf("(%zu/%zu) %s", test_run->id, test_run->num_tests, test_run->test->test_name);
    if (test_run->test->requires_re_compile && test_run->step >= s_compiling) {
        printf(" compiling...");
    }
    if (test_run->test->requires_re_link && test_run->step >= s_linking) {
        printf(" linking...");
    }
    if (test_run->step >= s_running) {
        printf(" running...");
    }
    if (test_run->test->expect_no_compile_num_runs > 0) {
        for (int i = 0; i <= test_run->no_compile_run_id; i++) {
            printf("#%d..", i);
        }
    }
    if (test_run->step >= s_success) {
        printf("%ssuccess%s", color_success_begin(), color_reset());
    }
    if (test_run->failed) {
        printf("%sfailed%s", color_error_begin(), color_reset());
    }
}

// returns true, to mark that the execution is done.
static __attribute__((format(printf, 2, 3))) bool test_fail(struct test_run* test_run, const char* fmt, ...) {
    test_run->failed = true;
    interactive_clear();
    test_run_print(test_run);
    printf("\n");
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    interactive_flush();
    if (flag_die_on_fail) {
        printf("\n%sExiting early...%s\n", color_error_begin(), color_reset());
        // TODO: Wait/kill all other test_run processes!
        exit(EXIT_FAILURE);
    }
    return true;
}

static void test_run_set_test(struct tests_db* tests, struct test_run* test_run, size_t i) {
    test_run->id = i + 1;
    test_run->num_tests = tests->num_tests;
    test_run->test = tests->tests + i;
    test_run->failed = false;
    test_run->step = s_starting;
    test_run->no_compile_run_id = 0;

    // Last arguments of compile command are -o obj_file -MF dep_file source_file
    test_run->compile_command.argv[test_run->compile_command.argc - 4] = test_run->test->obj_file_path;
    test_run->compile_command.argv[test_run->compile_command.argc - 2] = test_run->test->dep_file_path;
    test_run->compile_command.argv[test_run->compile_command.argc - 1] = test_run->test->file_path;

    test_run->link_command.argv[4] = test_run->test->obj_file_path;
    test_run->link_command.argv[6] = test_run->test->exe_file_path;

    test_run->negative_compile_command.argv[test_run->negative_compile_command.argc - 1] = test_run->test->file_path;
}

static void test_run_start_execute_no_compile(struct test_run* test_run) {
    sprintf(test_run->negative_compile_command.argv[test_run->negative_compile_command.argc - 2], "-DNEGATIVE_COMPILE_ITERATION=%d", test_run->no_compile_run_id);
    subprocess_start(&test_run->proc, &test_run->negative_compile_command, fail_exit_code_0);
}

static bool test_run_check_execute_no_compile(struct test_run* test_run) {
    struct test* test = test_run->test;
    if (WIFSIGNALED(test_run->proc.exit_status)) {
        return test_fail(test_run,
                         "Compiler killed by signal %d.\n"
                         "Compiler command: %s\n" COMPILER_OUTPUT_FORMAT,
                         (int)(WTERMSIG(test_run->proc.exit_status)),
                         cmd_line_to_str(&test_run->negative_compile_command, &test_run->scratch_space),
                         test_run->proc.output_buf.data);
    }
    if (WEXITSTATUS(test_run->proc.exit_status) == 0) {
        return test_fail(test_run,
                         "Compiler exited with code 0.\n"
                         "Compiler command: %s\n" COMPILER_OUTPUT_FORMAT,
                         cmd_line_to_str(&test_run->negative_compile_command, &test_run->scratch_space),
                         test_run->proc.output_buf.data);
    }

    if (test->expect_no_compile_has_pattern) {
        int regexec_status = regexec(&test->expect_no_compile_pattern, test_run->proc.output_buf.data, 0, NULL, 0);
        if (regexec_status == REG_NOMATCH) {
            return test_fail(test_run,
                             "Expected pattern not found in compiler output.\n"
                             "Compiler command: %s\n" COMPILER_OUTPUT_FORMAT,
                             cmd_line_to_str(&test_run->negative_compile_command, &test_run->scratch_space),
                             test_run->proc.output_buf.data);
        }
    }
    if (test_run->no_compile_run_id + 1 == test->expect_no_compile_num_runs) {
        test_run->step = s_success;
        return true;
    }
    test_run->no_compile_run_id++;
    test_run_start_execute_no_compile(test_run);
    return false;
}

static void test_run_start_execute(struct test_run* test_run) {
    test_run->step = s_running;
    if (test_run->test->expect_no_compile_num_runs > 0) {
        test_run->no_compile_run_id = 0;
        test_run_start_execute_no_compile(test_run);
        return;
    }
    char* argv[2];
    argv[0] = test_run->test->exe_file_path;
    argv[1] = NULL;
    struct cmd_line test_cmd_line;
    test_cmd_line.argc = 1;
    test_cmd_line.argv = argv;
    subprocess_start(&test_run->proc, &test_cmd_line, test_run->test->expect_exit_signal ? fail_exit_code_0 : fail_exit_abort);
}

static bool test_run_check_execute(struct test_run* test_run) {
    if (test_run->test->expect_no_compile_num_runs > 0) {
        return test_run_check_execute_no_compile(test_run);
    }
    if (strstr(test_run->proc.output_buf.data, "EXPECTATION FAILED") != NULL) {
        return test_fail(test_run,
                         "Found 'EXPECTATION FAILED' in output, test failed regardless of child exit code / signal.\n" TEST_OUTPUT_FORMAT,
                         test_run->proc.output_buf.data);
    }
    if (WIFSIGNALED(test_run->proc.exit_status)) {
        if (test_run->test->expect_exit_signal == 0) {
            return test_fail(test_run, "Test process killed by signal %d (expected exit with code = %d)\n",
                             (int)(WTERMSIG(test_run->proc.exit_status)), test_run->test->expect_exit_code);
        }
        if (test_run->test->expect_exit_signal != (int)(WTERMSIG(test_run->proc.exit_status))) {
            return test_fail(test_run, "Test process killed by signal %d (expected exit with signal %d)\n",
                             (int)(WTERMSIG(test_run->proc.exit_status)), test_run->test->expect_exit_signal);
        }
    }
    if (WIFEXITED(test_run->proc.exit_status)) {
        if (test_run->test->expect_exit_signal != 0) {
            return test_fail(test_run, "Test process exited with code %d (expected exit with signal %d)\n",
                             (int)(WEXITSTATUS(test_run->proc.exit_status)), test_run->test->expect_exit_signal);
        }
        if (test_run->test->expect_exit_code != (int)(WEXITSTATUS(test_run->proc.exit_status))) {
            return test_fail(test_run, "Test process exited with code %d (expected exit with code = %d)\n",
                             (int)(WEXITSTATUS(test_run->proc.exit_status)), test_run->test->expect_exit_code);
        }
    }

    char* output_steps = test_run->scratch_space.data;
    size_t output_steps_size = 0;
    const char* output_cursor = test_run->proc.output_buf.data;
    while (1) {
        char* next = strstr(output_cursor, "STEP: ");
        if (next == NULL) {
            break;
        }
        char* step_end = strchr(next, '\n');
        if (step_end == NULL) {
            return test_fail(test_run, "Found unfinished step line in output!\n" TEST_OUTPUT_FORMAT, test_run->proc.output_buf.data);
        }
        if (output_steps_size > 0) {
            string_reserve(&test_run->scratch_space, output_steps_size + 1);
            output_steps[output_steps_size++] = ',';
        }
        size_t step_size = (size_t)(step_end - (next + 6));
        string_reserve(&test_run->scratch_space, output_steps_size + step_size);
        memcpy(output_steps + output_steps_size, next + 6, step_size);
        output_steps_size += step_size;
        output_cursor = step_end;
    }
    output_steps[output_steps_size] = '\0';
    if (test_run->test->expect_steps[0] != '\0') {
        if (strcmp(test_run->test->expect_steps, output_steps) != 0) {
            return test_fail(test_run,
                             "Steps checking failed!\n"
                             "Expected steps: %s\n"
                             "Actual   steps: %s\n" TEST_OUTPUT_FORMAT,
                             test_run->test->expect_steps, output_steps, test_run->proc.output_buf.data);
        }
    } else {
        if (output_steps_size > 0) {
            return test_fail(test_run,
                             "Output includes unexpected steps: %s\n"
                             "Did you forget to add // EXPECT:STEPS comment to the test?" TEST_OUTPUT_FORMAT,
                             output_steps, test_run->proc.output_buf.data);
        }
    }
    test_run->step = s_success;
    return true;
}

static void test_run_start_link(struct test_run* test_run) {
    test_run->step = s_linking;
    subprocess_start(&test_run->proc, &test_run->link_command, fail_exit_abort);
}

static bool test_run_check_link(struct test_run* test_run) {
    if (WIFEXITED(test_run->proc.exit_status) == 0 || WEXITSTATUS(test_run->proc.exit_status) != 0) {
        return test_fail(test_run,
                         "Link command: %s\n" COMPILER_OUTPUT_FORMAT,
                         cmd_line_to_str(&test_run->link_command, &test_run->scratch_space),
                         test_run->proc.output_buf.data);
    }
    test_run_start_execute(test_run);
    return false;
}

static void test_run_start_compile(struct test_run* test_run) {
    test_run->step = s_compiling;
    subprocess_start(&test_run->proc, &test_run->compile_command, fail_exit_abort);
}

static bool test_run_check_compile(struct test_run* test_run) {
    if (WIFEXITED(test_run->proc.exit_status) == 0 || WEXITSTATUS(test_run->proc.exit_status) != 0) {
        return test_fail(test_run,
                         "Compile command: %s\n" COMPILER_OUTPUT_FORMAT,
                         cmd_line_to_str(&test_run->compile_command, &test_run->scratch_space),
                         test_run->proc.output_buf.data);
    }
    if (test_run->test->requires_re_link) {
        test_run_start_link(test_run);
    } else {
        test_run_start_execute(test_run);
    }
    return false;
}

static void test_run_start(struct test_run* test_run) {
    if (test_run->test->requires_re_compile) {
        test_run_start_compile(test_run);
    } else if (test_run->test->requires_re_link) {
        test_run_start_link(test_run);
    } else {
        test_run_start_execute(test_run);
    }
}

// Returns whether the running test is done.
static bool test_run_poll(struct test_run* test_run, bool* did_state_change) {
    if (!(*did_state_change = subprocess_poll(&test_run->proc))) {
        return false;
    }
    switch (test_run->step) {
        case s_compiling: return test_run_check_compile(test_run);
        case s_linking: return test_run_check_link(test_run);
        case s_running: return test_run_check_execute(test_run);
        default: fatal_error("Internal error: unexpected test_run step = %d\n", (int)test_run->step);
    }
}

static void test_run_print_interactive(struct test_run* test_runs, size_t num_test_runs) {
    if (flag_interactive) {
        interactive_clear();
        for (size_t i = 0; i < num_test_runs; i++) {
            test_run_print(test_runs + i);
            if (i + 1 != num_test_runs) {
                printf("\n");
            }
        }
        num_lines_interactive = (int)num_test_runs;
        interactive_flush();
    }
}

static void test_run_poll_all(struct test_run* test_runs, size_t* num_test_runs, size_t* num_tests_succeeded) {
    bool did_state_change = false;
    for (size_t i = 0; i < *num_test_runs;) {
        if (test_run_poll(&test_runs[i], &did_state_change)) {
            did_state_change = true;
            if (!test_runs[i].failed) {
                *num_tests_succeeded += 1;
                if (flag_print_on_success) {
                    interactive_clear();
                    test_run_print(&test_runs[i]);
                    printf("\n");
                }
            }
            if (i + 1 < *num_test_runs) {
                struct test_run run = test_runs[i];
                memmove(test_runs + i, test_runs + i + 1, sizeof(struct test_run) * (*num_test_runs - i - 1));
                test_runs[*num_test_runs - 1] = run;
            }
            *num_test_runs -= 1;
        } else {
            i++;
        }
    }
    if (did_state_change) {
        test_run_print_interactive(test_runs, *num_test_runs);
    }
}

static size_t tests_db_execute(struct tests_db* tests) {
    size_t num_tests_succeeded = 0;
    size_t num_tests_running = 0;
    for (size_t i = 0; i < tests->num_tests; i++) {
        while (num_tests_running == tests->num_test_runs) {
            // Poll all test runners until one is free.
            test_run_poll_all(tests->test_runs, &num_tests_running, &num_tests_succeeded);
        }
        struct test_run* test_run = tests->test_runs + (num_tests_running++);
        test_run_set_test(tests, test_run, i);
        test_run_start(test_run);
        test_run_print_interactive(tests->test_runs, num_tests_running);
    }
    while (num_tests_running > 0) {
        // Poll all test runs until all are done.
        test_run_poll_all(tests->test_runs, &num_tests_running, &num_tests_succeeded);
    }
    return num_tests_succeeded;
}

int main(int argc, char** argv) {
    chronometer_t entire_duration_start = chronometer_start();

    bool is_term_output = isatty(STDOUT_FILENO);

    const char* cache_dir = get_flag_string("cache-dir", "TEST_CACHE_DIR", DEFAULT_CACHE_DIR, &argc, &argv);
    flag_todos = get_flag_bool("T", "TEST_TODOS", false, &argc, &argv);
    flag_die_on_fail = get_flag_bool("x", "TEST_DIE_ON_FAIL", false, &argc, &argv);
    flag_print_on_success = get_flag_bool("v", "TEST_PRINT_ON_SUCCESS", !is_term_output, &argc, &argv);
    flag_colors = get_flag_bool("c", "TEST_COLORS", is_term_output, &argc, &argv);
    flag_interactive = get_flag_bool("i", "TEST_INTERACTIVE", is_term_output, &argc, &argv);
    bool num_jobs_all = get_flag_bool("ja", "TEST_JOBS_ALL", false, &argc, &argv);
    int num_jobs;
    if (num_jobs_all) {
        num_jobs = (int)sysconf(_SC_NPROCESSORS_ONLN);
        printf("Running at most %d parallel jobs\n", num_jobs);
    } else {
        num_jobs = get_flag_int("j", "TEST_JOBS", "1", &argc, &argv);
        if (num_jobs <= 0 || num_jobs > 256) {
            fatal_error("Invalid num jobs. Expected number between 1 and 256.\n");
        }
    }

    if (flag_interactive && (BUFSIZ < 65536)) {
        // For interactive mode, output looks smoother if we control
        // exact flushing with interactive_flush(). If this fails, we
        // don't really care as it's an optional enhancement.
        setvbuf(stdout, NULL, _IOFBF, 65536);
    }

    if (argc > 2) {
        printf("Usage: %s [options] [<tests-directory/test-file>]\n"
               "  Default tests directory: %s\n",
               argv[0], DEFAULT_TEST_DIR);
        return 1;
    }

    const char* test_dir = DEFAULT_TEST_DIR;
    if (argc == 2) {
        test_dir = argv[1];
    }
    printf("Testing %s\n", test_dir);
    if (flag_todos) {
        printf("\n");
    }

    struct tests_db tests;
    tests_db_init(&tests, num_jobs);
    tests_db_scan(&tests, test_dir, cache_dir);
    tests_db_prepare(&tests);

    size_t num_test_files = tests.num_tests + tests.num_mis_configured_tests;
    printf("\nFound %zu test file%s\n", num_test_files, num_test_files > 1 ? "s" : "");
    if (tests.num_mis_configured_tests > 0) {
        printf("\t%s%zu%s test%s are mis-configured\n",
               color_error_begin(), tests.num_mis_configured_tests, color_reset(),
               tests.num_mis_configured_tests > 1 ? "s" : "");
    }
    printf("\t%3zu test%s to re-compile\n"
           "\t%3zu test%s to re-link\n"
           "\t%3zu test%s to run\n"
           "\t%3zu negative compile test%s\n"
           "\n",
           tests.num_tests_to_compile,
           tests.num_tests_to_compile > 1 ? "s" : "",
           tests.num_tests_to_link,
           tests.num_tests_to_link > 1 ? "s" : "",
           tests.num_tests - tests.num_neg_compile_tests,
           tests.num_tests - tests.num_neg_compile_tests > 1 ? "s" : "",
           tests.num_neg_compile_tests,
           tests.num_neg_compile_tests > 1 ? "s" : "");

    size_t num_tests_succeeded = tests_db_execute(&tests);

    if (tests.num_mis_configured_tests > 0) {
        printf("%s%zu test%s mis-configured.%s\n",
               color_error_begin(),
               tests.num_mis_configured_tests, tests.num_mis_configured_tests > 1 ? "s" : "",
               color_reset());
    }
    if (tests.num_tests == 0) {
        printf("%sNo tests run!%s\n", color_warning_begin(), color_reset());
    }
    if (num_tests_succeeded > 0) {
        printf("%s%zu test%s succeeded.%s\n",
               color_success_begin(),
               num_tests_succeeded, num_tests_succeeded > 1 ? "s" : "",
               color_reset());
    }
    if (num_tests_succeeded < tests.num_tests) {
        printf("%s%zu test%s failed.%s\n",
               color_error_begin(),
               tests.num_tests - num_tests_succeeded,
               tests.num_tests - num_tests_succeeded > 1 ? "s" : "",
               color_reset());
    }

    const int exit_code = (tests.num_mis_configured_tests == 0 && tests.num_tests > 0 && num_tests_succeeded == tests.num_tests)
                            ? EXIT_SUCCESS
                            : EXIT_FAILURE;

    tests_db_destroy(&tests);

    double entire_duration_ms = chronometer_ms_elapsed(entire_duration_start);
    printf("Testing done in %s%.3lf%s seconds.\n", color_success_begin(), entire_duration_ms * 1e-3, color_reset());

    return exit_code;
}
