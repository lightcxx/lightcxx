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
#ifndef DEFAULT_BUILD_CACHE_DIR
#    error "Please define DEFAULT_BUILD_CACHE_DIR to point to a directory to store test build executables and cache."
#endif
#ifndef PLATFORM_IS_APPLE
#    error "Please define PLATFORM_IS_APPLE 0/1."
#endif
#ifndef PLATFORM_IS_LINUX
#    error "Please define PLATFORM_IS_LINUX 0/1."
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
#if PLATFORM_IS_APPLE
#    ifndef APPLE_ISYSROOT
#        error "Please define APPLE_ISYSROOT to point to the framework root on Mac OS. This is not used on other platforms."
#    endif
#endif

extern char* const* environ;

const int NUM_EXPECTATION_CLAUSES_SUPPORTED = 4;  // EXPECT:NO_COMPILE, EXPECT:STEPS, EXPECT:EXIT and REQUEST:SKIP
const int CMD_LINE_INITIAL_CAPACITY = 64;
const size_t PATH_INITIAL_CAPACITY = 256;
const size_t TESTS_INITIAL_CAPACITY = 512;
const size_t STR_BUF_INITIAL_CAPACITY = 4096;
const char PATH_SEP = '/';
#define PATH_SEP_STR "/"

#define MAX_NEGATIVE_COMPILE_RUNS 999
#define MAX_NEGATIVE_COMPILE_RUNS_STR "999"
#define TEST_OUTPUT_FORMAT "------ BEGIN TEST OUTPUT ------\n%s\n------  END  TEST OUTPUT ------\n"
#define COMPILER_OUTPUT_FORMAT "------ BEGIN COMPILER OUTPUT ------\n%s\n------  END  COMPILER OUTPUT ------\n"

bool flag_no_colors = false;
bool flag_die_on_fail = false;
bool flag_print_on_success = false;

size_t peak_memory_allocated = 0;
size_t current_memory_allocated = 0;
void* malloc_traced(size_t size) {
    current_memory_allocated += (size > 16 ? size : 16);
    if (current_memory_allocated > peak_memory_allocated) {
        peak_memory_allocated = current_memory_allocated;
    }
    return malloc(size);
}
void* realloc_traced(void* from, size_t prev, size_t next) {
    current_memory_allocated -= (prev > 16 ? prev : 16);
    current_memory_allocated += (next > 16 ? next : 16);
    if (current_memory_allocated > peak_memory_allocated) {
        peak_memory_allocated = current_memory_allocated;
    }
    return realloc(from, next);
}
void free_traced(void* ptr, size_t size) {
    current_memory_allocated -= (size > 16 ? size : 16);
    free(ptr);
}

#define malloc "THIS FUNCTION IS NOT ALLOWED. USE malloc_traced INSTEAD."
#define calloc "THIS FUNCTION IS NOT ALLOWED. USE malloc_traced INSTEAD."
#define realloc "THIS FUNCTION IS NOT ALLOWED. USE relloc_traced INSTEAD."
#define free "THIS FUNCTION IS NOT ALLOWED. USE free_traced INSTEAD."

const char* color_error_begin(void) {
    if (flag_no_colors) {
        return "";
    }
    return "\033[31m";
}
const char* color_warning_begin(void) {
    if (flag_no_colors) {
        return "";
    }
    return "\033[33m";
}
const char* color_success_begin(void) {
    if (flag_no_colors) {
        return "";
    }
    return "\033[32m";
}
const char* color_reset(void) {
    if (flag_no_colors) {
        return "";
    }
    return "\033[0m";
}

__attribute__((format(printf, 1, 2))) void print_warning(const char* fmt, ...) {
    printf("\n%sWarning%s: ", color_warning_begin(), color_reset());
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

__attribute__((__noreturn__)) __attribute__((format(printf, 1, 2))) void fatal_error(const char* fmt, ...) {
    printf("\n%sError%s: ", color_error_begin(), color_reset());
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    abort();
}

__attribute__((format(printf, 1, 2))) void print_todo(const char* fmt, ...) {
    printf("%sTODO%s: ", color_warning_begin(), color_reset());
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

bool timespec_before(struct timespec a, struct timespec b) {
    if (a.tv_sec == b.tv_sec) {
        return a.tv_nsec < b.tv_nsec;
    }
    return a.tv_sec < b.tv_sec;
}

struct path {
    char* data;
    size_t len;
    size_t capacity;
};

void path_new(struct path* path, const char* from) {
    path->capacity = PATH_INITIAL_CAPACITY;
    path->len = strlen(from);
    while (path->len >= path->capacity) {
        path->capacity *= 2;
    }
    path->data = malloc_traced(path->capacity);
    memcpy(path->data, from, path->len + 1);
}

void path_append(struct path* path, const char* part) {
    if (part[0] == PATH_SEP && path->data[path->len - 1] == PATH_SEP) {
        part++;
    } else if (part[0] != PATH_SEP && path->data[path->len - 1] != PATH_SEP) {
        path_append(path, PATH_SEP_STR);
    }
    const size_t part_len = strlen(part);
    if (path->len + part_len >= path->capacity) {
        print_warning("path resized! capacity=%zu, required=%zu.\n"
                      "  Double up PATH_INITIAL_CAPACITY in test_runner.c.\n",
                      path->capacity, path->len + part_len + 1);
        const size_t prev = path->capacity;
        while (path->len + part_len >= path->capacity) {
            path->capacity *= 2;
        }
        path->data = realloc_traced(path->data, prev, path->capacity);
    }
    memcpy(path->data + path->len, part, part_len + 1);
    path->len += part_len;
}

void path_pop(struct path* path) {
    if (path->data[path->len - 1] == PATH_SEP) {
        path->len--;
    }
    while (path->data[path->len - 1] != PATH_SEP) {
        path->len--;
    }
    path->data[path->len--] = '\0';
}

void path_stat(const char* path, bool* exists, struct timespec* last_touch_ts, bool* is_dir) {
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
#if PLATFORM_IS_APPLE
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

chronometer_t chronometer_start(void) {
    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    return (double)start_time.tv_sec * 1e3 + (double)start_time.tv_nsec * 1.e-6;
}

double chronometer_ms_elapsed(chronometer_t timer) {
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    return (double)end_time.tv_sec * 1e3 + (double)end_time.tv_nsec * 1.e-6 - timer;
}

struct cmd_line {
    char** argv;
    int argc;
    int argc_capacity;
};

void cmd_line_init(struct cmd_line* cmd_line) {
    cmd_line->argc = 0;
    cmd_line->argc_capacity = CMD_LINE_INITIAL_CAPACITY;
    cmd_line->argv = malloc_traced(sizeof(char*) * (size_t)cmd_line->argc_capacity);
    cmd_line->argv[0] = NULL;
}

void cmd_line_append(struct cmd_line* cmd_line, const char* data) {
    if (cmd_line->argc + 1 == cmd_line->argc_capacity) {
        print_warning("cmd_line resized! capacity=%d, required=%d.\n"
                      "Double up CMD_LINE_INITIAL_CAPACITY in test_runner.c.\n",
                      cmd_line->argc_capacity, cmd_line->argc_capacity + 1);
        const size_t prev = sizeof(char*) * (size_t)cmd_line->argc_capacity;
        cmd_line->argc_capacity *= 2;
        cmd_line->argv = realloc_traced(cmd_line->argv, prev, sizeof(char*) * (size_t)cmd_line->argc_capacity);
    }
    char* arg;
    if (data == NULL) {
        arg = NULL;
    } else {
        size_t data_len = strlen(data);
        arg = malloc_traced(data_len + 1);
        memcpy(arg, data, data_len + 1);
    }
    cmd_line->argv[cmd_line->argc++] = arg;
    cmd_line->argv[cmd_line->argc] = NULL;
}

const char* cmd_line_to_str(struct cmd_line* cmd_line, char** buf, size_t* buf_capacity) {
    if (cmd_line->argc == 0) {
        **buf = '\0';
        return *buf;
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
    if (*buf_capacity <= size) {
        size_t initial = *buf_capacity;
        while (*buf_capacity <= size) {
            *buf_capacity *= 2;
        }
        *buf = realloc_traced(*buf, initial, *buf_capacity);
    }
    memcpy(*buf, cmd_line->argv[0], argv0_size);
    size = argv0_size;
    for (int i = 1; i < cmd_line->argc; i++) {
        (*buf)[size++] = ' ';
        bool escape = false;
        char* start = *buf + size;
        for (char* p = cmd_line->argv[i]; *p; p++) {
            if (*p == '"' || *p == '\\') {
                (*buf)[size++] = '\\';
                escape = true;
            }
            (*buf)[size++] = *p;
        }
        if (escape) {
            memmove(start + 1, start, (size_t)((*buf + size) - start));
            *start = '"';
            (*buf)[size++] = '"';
        }
    }
    (*buf)[size] = '\0';
    return *buf;
}

struct test {
    struct timespec source_file_lmt;
    char* file_path;      // This is also where the memory buffer for all these paths starts.
    char* test_name;      // [<section>].<test_file_stem>
    char* dep_file_path;  // <build_cache_dir><section>.<test_file_stem>.d   (<build_cache_dir> must end in PATH_SEP)  // TODO: Maybe don't store, copy on-demand.
    char* obj_file_path;  // <build_cache_dir><section>.<test_file_stem>.o   (<build_cache_dir> must end in PATH_SEP)  // TODO: Maybe don't store, copy on-demand.
    char* exe_file_path;  // <build_cache_dir><section>.<test_file_stem>     (<build_cache_dir> must end in PATH_SEP)
    char* expect_steps;
    char* expect_exit;
    char* expect_no_compile;

    struct timespec obj_file_lmt;
    bool requires_re_compile;
    bool requires_re_link;
};

struct test_run {
    // Tests
    struct test* tests;
    size_t num_tests;
    size_t capacity;

    // Compilation command stubs
    struct cmd_line compile_command;
    struct cmd_line negative_compile_command;
    struct cmd_line link_command;

    // Buffer for reading test expectations
    char* scratch_space;
    size_t scratch_space_cap;

    // Stats
    size_t num_tests_to_compile;
    size_t num_tests_to_link;
};

void test_run_init(struct test_run* tests) {
    tests->num_tests = 0;
    tests->capacity = TESTS_INITIAL_CAPACITY;
    tests->tests = malloc_traced(sizeof(struct test) * tests->capacity);
    tests->scratch_space_cap = STR_BUF_INITIAL_CAPACITY;
    tests->scratch_space = malloc_traced(tests->scratch_space_cap);
}

struct string_view {
    const char* start;
    const char* end;
};

size_t sv_len(struct string_view view) {
    return (size_t)(view.end - view.start);
}

// Parse the test path to discover section and test name stem.
void parse_test_path(struct path* test_path, struct string_view* section, struct string_view* test_file_stem) {
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
}

bool parse_test_single_expectation(const char* file_contents, const char* pattern, struct string_view* result) {
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

// Parse the test source file to discover expectations. Results are pointing inside test_run->test_expectations_buf.
bool parse_test_expectations(struct test_run* test_run, struct path* test_path,
                             struct string_view* skip_reason,
                             struct string_view* expect_steps,
                             struct string_view* expect_exit,
                             struct string_view* expect_no_compile) {
    errno = 0;
    FILE* test_source_file = fopen(test_path->data, "r");
    if (test_source_file == NULL) {
        fatal_error("Failed to fopen() test source file %s: error: %d %s", test_path->data, errno, strerror(errno));
    }
    if (ferror(test_source_file)) {
        fatal_error("Failed to read expectations from test file %s: fopen failed error: %d %s\n",
                    test_path->data, ferror(test_source_file), strerror(ferror(test_source_file)));
    }
    char* cursor = test_run->scratch_space;
    *cursor = '\0';
    for (int i = 0; i < NUM_EXPECTATION_CLAUSES_SUPPORTED;) {
        char* result = fgets(cursor, (int)(test_run->scratch_space_cap - (size_t)(cursor - test_run->scratch_space)), test_source_file);
        if (result == NULL || ferror(test_source_file)) {
            if (feof(test_source_file)) {
                break;
            }
            fatal_error("Failed to read expectations from test file %s: fgets failed error: %d %s\n",
                        test_path->data, ferror(test_source_file), strerror(ferror(test_source_file)));
        }
        cursor = cursor + strlen(cursor);
        if (cursor == test_run->scratch_space + test_run->scratch_space_cap) {
            print_warning("reading expectations from test file %s: expectations too large!\n"
                          "  Split or fix this test so the first %d lines add up to less than %zu bytes,\n"
                          "  or increase STR_BUF_INITIAL_CAPACITY in test_runner.c.\n",
                          test_path->data, NUM_EXPECTATION_CLAUSES_SUPPORTED, (size_t)STR_BUF_INITIAL_CAPACITY);
            test_run->scratch_space = realloc_traced(test_run->scratch_space, test_run->scratch_space_cap, test_run->scratch_space_cap * 2);
            cursor = test_run->scratch_space + test_run->scratch_space_cap;
            test_run->scratch_space_cap *= 2;
            continue;  // Didn't finish reading the line, skip incrementing loop counter.
        }
        i++;
    }
    fclose(test_source_file);

    parse_test_single_expectation(test_run->scratch_space, "// REQUEST:SKIP", skip_reason);
    if (skip_reason->start != NULL) {
        return false;
    }

    parse_test_single_expectation(test_run->scratch_space, "// EXPECT:STEPS", expect_steps);
    parse_test_single_expectation(test_run->scratch_space, "// EXPECT:EXIT", expect_exit);
    parse_test_single_expectation(test_run->scratch_space, "// EXPECT:NO_COMPILE", expect_no_compile);
    return true;
}

void test_run_add_test(struct test_run* test_run, struct path* test_path, struct timespec lmt, struct path* build_cache_dir_path) {
    struct string_view section;
    struct string_view test_file_stem;
    parse_test_path(test_path, &section, &test_file_stem);

    struct string_view reason_skip;
    struct string_view expect_steps;
    struct string_view expect_exit;
    struct string_view expect_no_compile;
    if (!parse_test_expectations(test_run, test_path, &reason_skip, &expect_steps, &expect_exit, &expect_no_compile)) {
        print_todo("skipped    test [%.*s].%.*s : %.*s\n", (int)sv_len(section), section.start, (int)sv_len(test_file_stem), test_file_stem.start, (int)(reason_skip.end - reason_skip.start), reason_skip.start);
        return;
    }

    if (test_run->num_tests == test_run->capacity) {
        print_warning("test_run db resized! capacity=%zu, required=%zu.\n"
                      "Double up TESTS_INITIAL_CAPACITY in test_runner.c.\n",
                      test_run->capacity, test_run->capacity + 1);
        const size_t prev = sizeof(struct test) * test_run->capacity;
        test_run->capacity *= 2;
        test_run->tests = realloc_traced(test_run->tests, prev, sizeof(struct test) * test_run->capacity);
    }
    struct test* test = test_run->tests + test_run->num_tests;
    test_run->num_tests++;

    const size_t file_path_len = test_path->len;
    const size_t test_name_len = 1 /*[*/ + sv_len(section) + 2 /*].*/ + sv_len(test_file_stem);
    const size_t dep_file_path_len = build_cache_dir_path->len + sv_len(section) + 1 /*.*/ + sv_len(test_file_stem) + 2 /*.d*/;
    const size_t obj_file_path_len = build_cache_dir_path->len + sv_len(section) + 1 /*.*/ + sv_len(test_file_stem) + 2 /*.o*/;
    const size_t exe_file_path_len = build_cache_dir_path->len + sv_len(section) + 1 /*.*/ + sv_len(test_file_stem);

    test->source_file_lmt = lmt;
    // Total memory required is sum of all of the above, plus null terminators.
    test->file_path = malloc_traced(file_path_len + 1
                                    + test_name_len + 1
                                    + dep_file_path_len + 1
                                    + obj_file_path_len + 1
                                    + exe_file_path_len + 1
                                    + sv_len(expect_steps) + 1
                                    + sv_len(expect_exit) + 1
                                    + sv_len(expect_no_compile) + 1);
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

    test->expect_exit = test->expect_steps + sv_len(expect_steps) + 1;
    if (sv_len(expect_exit)) {
        memcpy(test->expect_exit, expect_exit.start, sv_len(expect_exit));
    }
    test->expect_exit[sv_len(expect_exit)] = '\0';

    test->expect_no_compile = test->expect_exit + sv_len(expect_exit) + 1;
    if (sv_len(expect_no_compile)) {
        memcpy(test->expect_no_compile, expect_no_compile.start, sv_len(expect_no_compile));
    }
    test->expect_no_compile[sv_len(expect_no_compile)] = '\0';
}

void test_run_scan_dir(struct test_run* test_run, struct path* test_path, struct path* build_cache_dir_path) {
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
            if (strcmp(entry->d_name, "skipped.cpp") == 0) {
                const char* last_slash = test_path->data + test_path->len - 1;
                const char* end = test_path->data + test_path->len;
                if (*last_slash == PATH_SEP) {
                    --last_slash;
                    --end;
                }
                while (*last_slash != PATH_SEP) {
                    --last_slash;
                }
                print_todo("skipped section [%.*s]\n", (int)(end - last_slash - 1), last_slash + 1);
            } else if (entry->d_name[0] != '.' && strcmp(entry->d_name, "nothing_to_do.cpp") != 0) {
                path_append(test_path, entry->d_name);
                test_run_scan_dir(test_run, test_path, build_cache_dir_path);
                path_pop(test_path);
            }
        }
    } else if (test_path->len > 4 && memcmp(test_path->data + test_path->len - 4, ".cpp", 4) == 0) {
        test_run_add_test(test_run, test_path, lmt, build_cache_dir_path);
    }
}

void test_run_scan(struct test_run* test_run, const char* test_dir, const char* build_cache_dir) {
    chronometer_t timer = chronometer_start();

    bool exists, is_dir;
    struct timespec lmt;
    path_stat(build_cache_dir, &exists, &lmt, &is_dir);
    if (!exists) {
        fatal_error("Cache directory %s does not exist.\n", build_cache_dir);
    }
    if (!is_dir) {
        fatal_error("Cache directory %s is not a directory.\n", build_cache_dir);
    }

    test_run_init(test_run);

    struct path build_cache_dir_path;
    char* realpath_build_cache_dir = realpath(build_cache_dir, NULL);
    path_new(&build_cache_dir_path, realpath_build_cache_dir);
    path_append(&build_cache_dir_path, PATH_SEP_STR);  // Ensure this ends in a PATH_SEP

    struct path test_path;
    path_new(&test_path, test_dir);
    test_run_scan_dir(test_run, &test_path, &build_cache_dir_path);

    free_traced(build_cache_dir_path.data, build_cache_dir_path.capacity);
    free_traced(test_path.data, test_path.capacity);

    double duration_millis = chronometer_ms_elapsed(timer);
    printf("\nFound %zu test files in %.3lfms\n", test_run->num_tests, duration_millis);
}

bool find_header_dep_with_lmt_gt(struct test_run* test_run, struct timespec lmt, const char* dep_file_path) {
    FILE* dep_file = fopen(dep_file_path, "r");
    if (dep_file == NULL) {
        fatal_error("Failed to fopen() dependencies file %s: error: %d %s", dep_file_path, errno, strerror(errno));
    }
    if (ferror(dep_file)) {
        fatal_error("Failed to read test header dependencies from file %s: fopen failed error: %d %s\n",
                    dep_file_path, ferror(dep_file), strerror(ferror(dep_file)));
    }
    char* cursor = test_run->scratch_space;
    *cursor = '\0';
    while (!feof(dep_file)) {
        char* result = fgets(cursor, (int)(test_run->scratch_space_cap - (size_t)(cursor - test_run->scratch_space) - 1), dep_file);
        if (result == NULL || ferror(dep_file)) {
            if (feof(dep_file)) {
                fclose(dep_file);
                return false;
            }
            fatal_error("Failed to read expectations from test file %s: fgets failed error: %d %s\n",
                        dep_file_path, ferror(dep_file), strerror(ferror(dep_file)));
        }
        cursor = cursor + strlen(cursor);
        if (cursor == test_run->scratch_space + test_run->scratch_space_cap - 1) {
            print_warning("reading dependencies from file %s: line too long!\n"
                          "  increase STR_BUF_INITIAL_CAPACITY in test_runner.c.\n",
                          dep_file_path);
            test_run->scratch_space = realloc_traced(test_run->scratch_space, test_run->scratch_space_cap, test_run->scratch_space_cap * 2);
            cursor = test_run->scratch_space + test_run->scratch_space_cap - 1;
            test_run->scratch_space_cap *= 2;
            continue;  // Didn't finish reading the line, continue reading.
        }
        // Tokenize the line to scan header dependencies
        while (cursor != test_run->scratch_space && (*(cursor - 1) == ' ' || *(cursor - 1) == '\\' || *(cursor - 1) == '\n')) {
            *(--cursor) = '\0';
        }
        *cursor = ' ';
        cursor++;
        *cursor = '\0';
        char* start = strchr(test_run->scratch_space, ':');
        char* p = strtok(start == NULL ? test_run->scratch_space : start + 1, " ");
        for (; p != NULL; p = strtok(NULL, " ")) {
            if (*p != '\0') {  // non-empty tokens only
                bool exists, is_dir;
                struct timespec header_lmt;
                path_stat(p, &exists, &header_lmt, &is_dir);  // TODO: cache map of header files lmt-s!
                if (!exists || is_dir) {
                    fatal_error("Header %s not found.\n"
                                "Required for dependency file %s",
                                p, dep_file_path);
                }
                if (timespec_before(lmt, header_lmt)) {
                    fclose(dep_file);
                    return true;
                }
                while (*p == ' ') {
                    p++;
                }
            }
        }
        cursor = test_run->scratch_space;
    }
    fclose(dep_file);
    return false;
}

bool check_test_requires_re_compile(struct test_run* test_run, struct test* test) {
    if (*test->expect_no_compile != '\0') {
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
    return find_header_dep_with_lmt_gt(test_run, test->obj_file_lmt, test->dep_file_path);
}

bool check_test_requires_re_link(struct test* test, struct timespec libs_lmt) {
    if (*test->expect_no_compile != '\0') {
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

void add_base_compiler_flags(struct cmd_line* cmd) {
    cmd_line_append(cmd, COMPILER);
#if OPT_IS_DEBUG
    cmd_line_append(cmd, "-g");
#endif
#if OPT_IS_RELEASE
    cmd_line_append(cmd, "-O3");
#endif
}

void add_compiler_include_flags(struct cmd_line* cmd) {
    cmd_line_append(cmd, "-std=c++20");
    cmd_line_append(cmd, "-nostdinc++");
    cmd_line_append(cmd, "-I" SOURCE_DIR PATH_SEP_STR "include");
    cmd_line_append(cmd, "-I" SOURCE_DIR PATH_SEP_STR "testing");
#if PLATFORM_IS_APPLE
    cmd_line_append(cmd, "-isysroot");
    cmd_line_append(cmd, APPLE_ISYSROOT);
#elif PLATFORM_IS_LINUX
    // Nothing to do.
#else
#    error "Platform not supported! Only Apple and Linux systems are currently supported."
#endif
}

void cmd_line_build_compile_command(struct cmd_line* compile_command) {
    cmd_line_init(compile_command);
    add_base_compiler_flags(compile_command);
    add_compiler_include_flags(compile_command);
    // Emit object file
    cmd_line_append(compile_command, "-c");
    // Emit dependencies file
    cmd_line_append(compile_command, "-MMD");
    // Add warning flags for positive-compile tests.
    cmd_line_append(compile_command, "-Werror");
    cmd_line_append(compile_command, "-Wall");
    cmd_line_append(compile_command, "-Wextra");
    cmd_line_append(compile_command, "-Wunused");
    cmd_line_append(compile_command, "-Wpedantic");
    cmd_line_append(compile_command, "-Wconversion");
    cmd_line_append(compile_command, "-Wsign-conversion");
    cmd_line_append(compile_command, "-Wsign-compare");
    cmd_line_append(compile_command, "-Wnull-dereference");
    cmd_line_append(compile_command, "-Wformat=2");
    cmd_line_append(compile_command, "-Wimplicit-fallthrough");
    cmd_line_append(compile_command, "-Wnon-virtual-dtor");
    cmd_line_append(compile_command, "-Wold-style-cast");
    cmd_line_append(compile_command, "-Wcast-align");
    cmd_line_append(compile_command, "-Woverloaded-virtual");
#if COMPILER_IS_CLANG
    cmd_line_append(compile_command, "-Wno-unknown-warning-option");  // TODO: fix this flag.
    cmd_line_append(compile_command, "-Wno-deprecated-volatile");     // TODO: fix this flag.
#elif COMPILER_IS_GCC
    cmd_line_append(compile_command, "-Wmisleading-indentation");
    cmd_line_append(compile_command, "-Wduplicated-cond");
    cmd_line_append(compile_command, "-Wduplicated-branches");
    cmd_line_append(compile_command, "-Wlogical-op");
    cmd_line_append(compile_command, "-Wno-unknown-pragmas");     // TODO: fix this flag.
    cmd_line_append(compile_command, "-Wno-attributes");          // TODO: fix this flag.
    cmd_line_append(compile_command, "-Wno-ignored-qualifiers");  // TODO: fix this flag.
#else
#    error "Compiler not supported! Only Clang and GCC are currently supported."
#endif

    // Last 5 arguments will change from compilation to compilation.
    cmd_line_append(compile_command, "-o");
    cmd_line_append(compile_command, NULL);
    cmd_line_append(compile_command, "-MF");
    cmd_line_append(compile_command, NULL);
    cmd_line_append(compile_command, NULL);
}

void cmd_line_build_negative_compile_command(struct cmd_line* compile_command) {
    cmd_line_init(compile_command);
    add_base_compiler_flags(compile_command);
    add_compiler_include_flags(compile_command);
    cmd_line_append(compile_command, "-c");
    cmd_line_append(compile_command, "-o");
    cmd_line_append(compile_command, "/dev/null");
    cmd_line_append(compile_command, "-DNEGATIVE_COMPILE_ITERATION=" MAX_NEGATIVE_COMPILE_RUNS_STR);
    cmd_line_append(compile_command, NULL);  // For file name
}

void cmd_line_build_link_command(struct cmd_line* link_command) {
    cmd_line_init(link_command);
    add_base_compiler_flags(link_command);
#if COMPILER_IS_GCC
    cmd_line_append(link_command, "-nodefaultlibs");
#else
    cmd_line_append(link_command, "-nostdlib++");
#endif
    cmd_line_append(link_command, NULL);
    cmd_line_append(link_command, "-o");
    cmd_line_append(link_command, NULL);
    cmd_line_append(link_command, LIB_DIR PATH_SEP_STR "liblightcxx_static.a");
    cmd_line_append(link_command, LIB_DIR PATH_SEP_STR "libtesting.a");
#if COMPILER_IS_GCC
#    if PLATFORM_IS_LINUX
    cmd_line_append(link_command, "-lgcc");
    cmd_line_append(link_command, "-lgcc_eh");
#    endif
#endif
#if PLATFORM_IS_LINUX
    cmd_line_append(link_command, "-lc");
    cmd_line_append(link_command, "-lpthread");
    cmd_line_append(link_command, "-ldl");
#endif
}

void test_run_prepare(struct test_run* test_run) {
    chronometer_t test_run_prepare_timer = chronometer_start();

    cmd_line_build_compile_command(&test_run->compile_command);
    cmd_line_build_negative_compile_command(&test_run->negative_compile_command);
    cmd_line_build_link_command(&test_run->link_command);

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
            fatal_error("library %s does not exist. Hint: run the cmake build before running the test_run.\n", libs[i]);
        }
        if (is_dir) {
            fatal_error("expected to find library %s, but is a directory!\n", libs[i]);
        }
        if (timespec_before(libs_lmt, lib_lmt)) {
            libs_lmt = lib_lmt;
        }
    }

    test_run->num_tests_to_compile = 0;
    test_run->num_tests_to_link = 0;
    for (size_t i = 0; i < test_run->num_tests; i++) {
        test_run->tests[i].requires_re_compile = check_test_requires_re_compile(test_run, test_run->tests + i);
        test_run->num_tests_to_compile += test_run->tests[i].requires_re_compile;

        test_run->tests[i].requires_re_link = check_test_requires_re_link(test_run->tests + i, libs_lmt);
        test_run->num_tests_to_link += test_run->tests[i].requires_re_link;
    }

    double duration = chronometer_ms_elapsed(test_run_prepare_timer);
    printf("Prepared test run in %.3lfms:\n"
           "  %zu tests to re-compile\n"
           "  %zu tests to re-link\n"
           "  %zu tests to run\n"
           "\n",
           duration, test_run->num_tests_to_compile, test_run->num_tests_to_link, test_run->num_tests);
}

struct subprocess {
    pid_t pid;
    int child_stdout_fd;
    int child_stderr_fd;
    bool is_done;
    int exit_status;
    char* output_buf;
    size_t output_buf_size;
    size_t output_buf_capacity;
    char pipe_buf[4096];
};

void subprocess_init(struct subprocess* result) {
    result->pid = 0;
    result->child_stdout_fd = 0;
    result->child_stderr_fd = 0;
    result->is_done = false;
    result->exit_status = 0;
    result->output_buf_size = 0;
    result->output_buf_capacity = STR_BUF_INITIAL_CAPACITY;
    result->output_buf = malloc_traced(result->output_buf_capacity);
}

enum subprocess_fail_exit {
    fail_exit_abort,
    fail_exit_code_0,
    fail_exit_code_1,
};

void subprocess_start(struct subprocess* result, struct cmd_line* cmd, enum subprocess_fail_exit exit_strategy) {
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
                exit(exit_strategy == fail_exit_code_0 ? 0 : 1);
            }
        }
        close(stdout_pipe_fd[1]);  // close pipe write end after dup

        if (dup2(stderr_pipe_fd[1], STDERR_FILENO) < 0) {  // pipe stderr to parent
            fprintf(stderr, "[CHILD]: dup2 failed: error: %d %s\n", errno, strerror(errno));
            if (exit_strategy == fail_exit_abort) {
                abort();
            } else {
                exit(exit_strategy == fail_exit_code_0 ? 0 : 1);
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
    result->output_buf_size = 0;
}

void subprocess_poll_output(struct subprocess* result, int fd, bool to_eof) {
    while (1) {
        errno = 0;
        ssize_t num_bytes = read(fd, result->pipe_buf, 4096);
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
        if (result->output_buf_size + (size_t)num_bytes >= result->output_buf_capacity) {
            size_t prev = result->output_buf_capacity;
            while (result->output_buf_size + (size_t)num_bytes >= result->output_buf_capacity) {
                result->output_buf_capacity *= 2;
            }
            result->output_buf = realloc_traced(result->output_buf, prev, result->output_buf_capacity);
        }
        memcpy(result->output_buf + result->output_buf_size, result->pipe_buf, (size_t)num_bytes);
        result->output_buf_size += (size_t)num_bytes;
    }
}

bool subprocess_poll(struct subprocess* result, bool blocking) {
    if (result->is_done) {
        return true;
    }
    pid_t status = waitpid(result->pid, &result->exit_status, blocking ? 0 : (WNOHANG));
    if (status < 0) {
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
    result->output_buf[result->output_buf_size] = '\0';
    close(result->child_stdout_fd);
    close(result->child_stderr_fd);
    return true;
}

__attribute__((format(printf, 2, 3))) bool test_fail(struct test* test, const char* fmt, ...) {
    printf("%sfailed%s.\n", color_error_begin(), color_reset());
    printf("  Test file: %s\n", test->file_path);
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    if (flag_die_on_fail) {
        printf("\nAborting early...\n");
        abort();
    }
    return false;
}

void print_test_success(void) {
    if (flag_print_on_success) {
        printf("%ssuccess%s.\n", color_success_begin(), color_reset());
    } else {
        printf("\r\033[K");
    }
    fflush(stdout);
}

bool compile_test(struct test_run* test_run, struct test* test, struct subprocess* result_buf) {
    // Last 4 arguments of compile command are always:
    // -o obj_file -MF dep_file source_file
    test_run->compile_command.argv[test_run->compile_command.argc - 4] = test->obj_file_path;
    test_run->compile_command.argv[test_run->compile_command.argc - 2] = test->dep_file_path;
    test_run->compile_command.argv[test_run->compile_command.argc - 1] = test->file_path;
    subprocess_start(result_buf, &test_run->compile_command, fail_exit_abort);
    subprocess_poll(result_buf, true);
    if (WIFEXITED(result_buf->exit_status) == 0 || WEXITSTATUS(result_buf->exit_status) != 0) {
        return test_fail(test, "Compile command: %s\n" COMPILER_OUTPUT_FORMAT,
                         cmd_line_to_str(&test_run->compile_command, &test_run->scratch_space, &test_run->scratch_space_cap),
                         result_buf->output_buf);
    }
    return true;
}

bool link_test(struct test_run* test_run, struct test* test, struct subprocess* result_buf) {
    // Last 3 arguments of link command are always:
    // -o exe_file obj_file
    test_run->link_command.argv[3] = test->obj_file_path;
    test_run->link_command.argv[5] = test->exe_file_path;
    subprocess_start(result_buf, &test_run->link_command, fail_exit_abort);
    subprocess_poll(result_buf, true);
    if (WIFEXITED(result_buf->exit_status) == 0 || WEXITSTATUS(result_buf->exit_status) != 0) {
        return test_fail(test, "Link command: %s\n" COMPILER_OUTPUT_FORMAT,
                         cmd_line_to_str(&test_run->link_command, &test_run->scratch_space, &test_run->scratch_space_cap),
                         result_buf->output_buf);
    }
    return true;
}

bool run_test(struct test_run* test_run, struct test* test, struct subprocess* result_buf) {
    const char* const expected_exit_wrong_error_msg = "Invalid EXPECTED:EXIT request. Must be one of:\n"
                                                      "// EXPECTED:EXIT CODE = n\n"
                                                      "// EXPECTED:EXIT KILLED BY SIGNAL n\n"
                                                      "// EXPECTED:EXIT KILLED BY SIGNAL SIGABRT\n";
    const char* expect_exit = test->expect_exit;
    int expected_exit_code = 0;
    int expected_exit_signal = 0;
    if (strncmp(expect_exit, "CODE = ", 7) == 0) {
        const char* cursor = expect_exit + 7;
        while (*cursor) {
            if ('0' <= *cursor && *cursor <= '9') {
                expected_exit_code = expected_exit_code * 10 + *cursor - '0';
                cursor++;
            } else {
                return test_fail(test, "%s\nInstead found: '// EXPECTED:EXIT %s'",
                                 expected_exit_wrong_error_msg, expect_exit);
            }
        }
    } else if (strncmp(expect_exit, "KILLED BY SIGNAL ", 17) == 0) {
        if (strcmp(expect_exit + 17, "SIGABRT") == 0) {
            expected_exit_signal = SIGABRT;
        } else {
            const char* cursor = expect_exit + 17;
            while (*cursor) {
                if ('0' <= *cursor && *cursor <= '9') {
                    expected_exit_signal = expected_exit_signal * 10 + *cursor;
                    cursor++;
                } else {
                    return test_fail(test, "%s\nInstead found: '// EXPECTED:EXIT %s'",
                                     expected_exit_wrong_error_msg, expect_exit);
                }
            }
        }
    } else if (expect_exit[0] == '\0') {
        expect_exit = "CODE = 0";
    } else {
        return test_fail(test, "%s\nInstead found: '// EXPECTED:EXIT %s'",
                         expected_exit_wrong_error_msg, expect_exit);
    }

    char* argv[2];
    argv[0] = test->exe_file_path;
    argv[1] = NULL;
    struct cmd_line test_cmd_line;
    test_cmd_line.argc_capacity = 2;
    test_cmd_line.argc = 1;
    test_cmd_line.argv = argv;
    subprocess_start(result_buf, &test_cmd_line, expected_exit_signal ? fail_exit_code_0 : fail_exit_abort);
    subprocess_poll(result_buf, true);

    if (strstr(result_buf->output_buf, "EXPECTATION FAILED") != NULL) {
        return test_fail(test, "Found 'EXPECTATION FAILED' in output, test failed regardless of child exit code / signal.\n" TEST_OUTPUT_FORMAT,
                         result_buf->output_buf);
    }
    if (WIFSIGNALED(result_buf->exit_status)) {
        if (expected_exit_code != 0 || expected_exit_signal != (int)(WTERMSIG(result_buf->exit_status))) {
            return test_fail(test, "Test process killed by signal %d (expected EXIT %s)\n", (int)(WTERMSIG(result_buf->exit_status)), expect_exit);
        }
    }
    if (WIFEXITED(result_buf->exit_status)) {
        if (expected_exit_signal != 0 || expected_exit_code != (int)(WEXITSTATUS(result_buf->exit_status))) {
            return test_fail(test, "Test process exited with code %d (expected EXIT %s)\n", WEXITSTATUS(result_buf->exit_status), expect_exit);
        }
    }

    char* output_steps = test_run->scratch_space;
    size_t output_steps_size = 0;
    const char* output_cursor = result_buf->output_buf;
    while (1) {
        char* next = strstr(output_cursor, "STEP: ");
        if (next == NULL) {
            break;
        }
        char* step_end = strchr(next, '\n');
        if (step_end == NULL) {
            return test_fail(test, "Found unfinished step line in output!\n" TEST_OUTPUT_FORMAT, result_buf->output_buf);
        }
        if (output_steps_size > 0) {
            if (output_steps_size + 1 >= test_run->scratch_space_cap) {
                test->file_path = realloc_traced(test->file_path, test_run->scratch_space_cap, test_run->scratch_space_cap * 2);
                test_run->scratch_space_cap *= 2;
            }
            output_steps[output_steps_size++] = ',';
        }
        size_t step_size = (size_t)(step_end - (next + 6));
        while (output_steps_size + step_size >= test_run->scratch_space_cap) {
            test->file_path = realloc_traced(test->file_path, test_run->scratch_space_cap, test_run->scratch_space_cap * 2);
            test_run->scratch_space_cap *= 2;
        }
        memcpy(output_steps + output_steps_size, next + 6, step_size);
        output_steps_size += step_size;
        output_cursor = step_end;
    }
    output_steps[output_steps_size] = '\0';
    if (test->expect_steps[0] != '\0') {
        if (strcmp(test->expect_steps, output_steps) != 0) {
            return test_fail(test, "Steps checking failed!\n"
                                   "Expected steps: %s\n"
                                   "Actual   steps: %s\n" TEST_OUTPUT_FORMAT,
                             test->expect_steps, output_steps, result_buf->output_buf);
        }
    } else {
        if (output_steps_size > 0) {
            return test_fail(test, "Output includes unexpected steps: %s\n"
                                   "Did you forget to add // EXPECT:STEPS comment to the test?" TEST_OUTPUT_FORMAT,
                             output_steps, result_buf->output_buf);
        }
    }

    return true;
}

bool run_negative_compile_test(struct test_run* test_run, struct test* test, struct subprocess* result_buf) {
    const char* pattern = "";
    int num_runs = atoi(test->expect_no_compile);
    if (num_runs == 0) {
        num_runs = 1;
        size_t pattern_len = strlen(test->expect_no_compile);
        if (pattern_len < 2 || test->expect_no_compile[0] != '"' || test->expect_no_compile[pattern_len - 1] != '"') {
            return test_fail(test, "Invalid non-compile expectation: %s\n", test->expect_no_compile);
        }
        test->expect_no_compile[pattern_len - 1] = '\0';
        pattern = test->expect_no_compile + 1;
    } else if (num_runs < 1 || num_runs > MAX_NEGATIVE_COMPILE_RUNS) {
        return test_fail(test, "Invalid non-compile test num runs: %d. Supported 1 to %d\n", num_runs, MAX_NEGATIVE_COMPILE_RUNS);
    }
    bool has_msg_pattern = (pattern[0] != '\0') && (pattern[0] != '.' || pattern[1] != '*' || pattern[2] != '\0');
    regex_t msg_pattern;
    if (has_msg_pattern) {
        int regcomp_status = regcomp(&msg_pattern, pattern, REG_EXTENDED | REG_NOSUB);
        if (regcomp_status != 0) {
            char regerror_msg[256];
            regerror(regcomp_status, &msg_pattern, regerror_msg, 256);
            return test_fail(test, "Invalid message pattern '%s': %s\n", pattern, regerror_msg);
        }
    }

    test_run->negative_compile_command.argv[test_run->negative_compile_command.argc - 1] = test->file_path;
    for (int test_id = 0; test_id < num_runs; test_id++) {
        sprintf(test_run->negative_compile_command.argv[test_run->negative_compile_command.argc - 2], "-DNEGATIVE_COMPILE_ITERATION=%d", test_id);
        if (num_runs > 1) {
            printf("#%d... ", test_id + 1);
            fflush(stdout);
        }
        subprocess_start(result_buf, &test_run->negative_compile_command, fail_exit_code_0);
        subprocess_poll(result_buf, true);

        if (WIFSIGNALED(result_buf->exit_status)) {
            return test_fail(test, "Compiler killed by signal %d.\n"
                                   "Compiler command: %s\n" COMPILER_OUTPUT_FORMAT,
                             (int)(WTERMSIG(result_buf->exit_status)),
                             cmd_line_to_str(&test_run->negative_compile_command, &test_run->scratch_space, &test_run->scratch_space_cap),
                             result_buf->output_buf);
            return false;
        }
        if (WEXITSTATUS(result_buf->exit_status) == 0) {
            return test_fail(test, "Compiler exited with code 0.\n"
                                   "Compiler command: %s\n" COMPILER_OUTPUT_FORMAT,
                             cmd_line_to_str(&test_run->negative_compile_command, &test_run->scratch_space, &test_run->scratch_space_cap),
                             result_buf->output_buf);
        }

        if (has_msg_pattern) {
            int regexec_status = regexec(&msg_pattern, result_buf->output_buf, 0, NULL, 0);
            if (regexec_status == REG_NOMATCH) {
                return test_fail(test, "Pattern '%s' not found in compiler output.\n" COMPILER_OUTPUT_FORMAT,
                                 pattern, result_buf->output_buf);
            }
        }
    }
    return true;
}

size_t test_run_execute(struct test_run* test_run) {
    struct subprocess subprocess_result;
    subprocess_init(&subprocess_result);
    size_t num_tests_succeeded = 0;
    for (size_t i = 0; i < test_run->num_tests; i++) {
        struct test* test = test_run->tests + i;
        bool success = true;
        printf("(%zu/%zu) %s ", i + 1, test_run->num_tests, test->test_name);
        fflush(stdout);
        if (test->requires_re_compile) {
            printf("compiling... ");
            fflush(stdout);
            success = compile_test(test_run, test, &subprocess_result);
        }
        if (test->requires_re_link && success) {
            printf("linking... ");
            fflush(stdout);
            success = link_test(test_run, test, &subprocess_result);
        }
        if (success) {
            printf("running... ");
            fflush(stdout);
            if (*test->expect_no_compile != '\0') {
                success = run_negative_compile_test(test_run, test, &subprocess_result);
            } else {
                success = run_test(test_run, test, &subprocess_result);
            }
        }
        if (success) {
            num_tests_succeeded += 1;
            print_test_success();
        }
    }
    return num_tests_succeeded;
}

int main(int argc, char** argv) {
    if (argc > 2) {
        printf("Usage: %s [<tests-directory/test-file>]\n"
               "  Default tests directory: %s\n",
               argv[0], DEFAULT_TEST_DIR);
        return 1;
    }

    const char* test_dir = DEFAULT_TEST_DIR;
    if (argc == 2) {
        test_dir = argv[1];
    }
    // Take absolute path of the test directory. This is required to maintain the integrity of the cache.
    char* realpath_test_dir = realpath(test_dir, NULL);
    printf("Testing %s\n", realpath_test_dir);

    if (!isatty(STDOUT_FILENO)) {
        flag_no_colors = true;
        flag_print_on_success = true;
    }

    char* env_die_on_fail = getenv("TEST_DIE_ON_FAIL");
    if (env_die_on_fail != NULL && *env_die_on_fail != '\0' && *env_die_on_fail != '0') {
        flag_die_on_fail = true;
    }

    char* env_print_on_success = getenv("TEST_PRINT_ON_SUCCESS");
    if (env_print_on_success != NULL && *env_print_on_success != '\0' && *env_print_on_success != '0') {
        flag_print_on_success = true;
    }

    char* env_no_colors = getenv("TEST_NO_COLORS");
    if (env_no_colors != NULL && *env_no_colors != '\0' && *env_no_colors != '0') {
        flag_no_colors = true;
    }

    char* env_cache_dir = getenv("TEST_CACHE_DIR");
    const char* cache_dir = (env_cache_dir != NULL && *env_cache_dir != '\0') ? env_cache_dir : DEFAULT_BUILD_CACHE_DIR;

    struct test_run test_run;
    test_run_scan(&test_run, test_dir, cache_dir);
    test_run_prepare(&test_run);
    size_t num_tests_succeeded = test_run_execute(&test_run);

    if (num_tests_succeeded == test_run.num_tests) {
        printf("All %zu tests succeeded.\n", num_tests_succeeded);
    } else {
        printf("%zu test%s of %zu failed.\n",
               test_run.num_tests - num_tests_succeeded,
               test_run.num_tests - num_tests_succeeded == 1 ? "" : "s",
               test_run.num_tests);
    }

    printf("Test runner peak malloc size: %.2lfkB\n", (double)peak_memory_allocated / 1024);
    return num_tests_succeeded == test_run.num_tests ? EXIT_SUCCESS : EXIT_FAILURE;
}
