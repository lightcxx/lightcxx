#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// Default implementations for hooks, for tests that don't include testing.h and for multi-test binaries.
__attribute__((__weak__)) const char* testing_get_expected_steps() {
    return "";
}

__attribute__((__weak__)) const char* testing_get_expected_exit() {
    return "";
}

struct test_def {
    void (*test_func)();
    const char* name;
};
typedef struct test_def test_def_t;

enum {
    MAX_NUM_TESTS = 1024,
    MAX_NUM_GLOBALS = 1024,
    PIPE_BUF_SZ = 1024,
    CHILD_OUTPUT_MAX_SIZE = 1 << 16,
};

static test_def_t tests[MAX_NUM_TESTS];
static size_t num_tests = 0;
static int is_inside_testing_process = 0;

struct testing_global_var {
    void* obj;
    void (*ctor)(void*);
    void (*dtor)(void*);
};
typedef struct testing_global_var testing_global_var_t;
static testing_global_var_t globals[MAX_NUM_GLOBALS];
static size_t num_globals = 0;

void testing_fail_impl(const char* func, const char* file, int line) {
    if (!is_inside_testing_process) {
        return;
    }
    printf("EXPECTATION FAILED: IN FUNCTION %s (%s:%d)\n", func, file, line);
    fflush(stdout);
    abort();
}

void testing_expect_impl(int cnd, const char* func, const char* file, int line) {
    if (!cnd) {
        testing_fail_impl(func, file, line);
    }
}

void testing_step_impl(const char* msg, ...) {
    if (!is_inside_testing_process) {
        return;
    }
    printf("STEP: ");
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);
    printf("\n");
    fflush(stdout);
}

void testing_register_test(void (*test)(), const char* name) {
    if (num_tests >= MAX_NUM_TESTS) {
        num_tests++;
        return;
    }
    tests[num_tests].test_func = test;
    tests[num_tests].name = name;
    num_tests++;
}

void testing_register_global(void* obj, void (*ctor)(void*), void (*dtor)(void*)) {
    if (num_globals == MAX_NUM_GLOBALS) {
        printf("EXPECTATION FAILED: Too many registered globals.\n");
        abort();
    }
    globals[num_globals].obj = obj;
    globals[num_globals].ctor = ctor;
    globals[num_globals].dtor = dtor;
    num_globals++;
}

int run_tests() {
    if (num_tests == 0) {
        return 0;
    }
    if (num_tests >= MAX_NUM_TESTS) {
        printf("EXPECTATION FAILED: Too many tests registered: %zu, max supported is %d.\n", num_tests, MAX_NUM_TESTS);
        return 1;
    }
    if (num_globals >= MAX_NUM_GLOBALS) {
        printf("EXPECTATION FAILED: Too many global variables registered: %zu, max supported is %d.\n", num_globals, MAX_NUM_GLOBALS);
        return 1;
    }
    for (size_t i = 0; i < num_globals; i++) {
        globals[i].ctor(globals[i].obj);
    }
    for (size_t i = 0; i < num_tests; i++) {
        tests[i].test_func();
    }
    for (size_t i = 0; i < num_globals; i++) {
        globals[i].dtor(globals[i].obj);
    }
    return 0;
}

static void read_child_output_pipe(int pipe_fd, char* buf, char* output, size_t* output_size) {
    while (1) {
        ssize_t bytes_read = read(pipe_fd, buf, PIPE_BUF_SZ - 1);
        if (bytes_read < 0) {
            if (errno == EAGAIN) {
                continue;
            }
            printf("read failed: errno=%d message=%s\n", errno, strerror(errno));
            _Exit(1);
        }
        if (bytes_read > 0) {
            buf[bytes_read] = '\0';
            if (*output_size + bytes_read >= CHILD_OUTPUT_MAX_SIZE) {
                printf("Steps output size too large. Please increase capacity (currently %d)\n", CHILD_OUTPUT_MAX_SIZE);
                _Exit(1);
            }
            memcpy(output + *output_size, buf, bytes_read);
            *output_size += bytes_read;
        }
        break;  // Pipe is done.
    }
}

int main(int argc, char** argv) {
    const char* test_filename = argv[0];
    const char* cursor = strstr(test_filename, "/tests/");
    if (cursor != NULL) {
        test_filename = cursor + 7;
    }
    printf("Running test %s\n", test_filename);

    const char* expected_exit = testing_get_expected_exit();
    const char* const expected_exit_wrong_error_msg = "Invalid EXPECTED:EXIT request. Must be one of:\n"
                                                      "// EXPECTED:EXIT CODE = n\n"
                                                      "// EXPECTED:EXIT KILLED BY SIGNAL n\n"
                                                      "// EXPECTED:EXIT KILLED BY SIGNAL SIGABRT\n"
                                                      "\n"
                                                      "Instead found: '// EXPECTED:EXIT %s'";
    int expected_exit_code = 0;
    int expected_exit_signal = 0;
    if (strncmp(expected_exit, "CODE = ", 7) == 0) {
        const char* cursor = expected_exit + 7;
        while (*cursor) {
            if ('0' <= *cursor && *cursor <= '9') {
                expected_exit_code = expected_exit_code * 10 + *cursor - '0';
                cursor++;
            } else {
                printf(expected_exit_wrong_error_msg, expected_exit);
                return 1;
            }
        }
    } else if (strncmp(expected_exit, "KILLED BY SIGNAL ", 17) == 0) {
        if (strcmp(expected_exit + 17, "SIGABRT") == 0) {
            expected_exit_signal = SIGABRT;
        } else {
            const char* cursor = expected_exit + 17;
            while (*cursor) {
                if ('0' <= *cursor && *cursor <= '9') {
                    expected_exit_signal = expected_exit_signal * 10 + *cursor;
                    cursor++;
                } else {
                    printf(expected_exit_wrong_error_msg, expected_exit);
                    return 1;
                }
            }
        }
    } else if (expected_exit[0] == '\0') {
        // Do nothing.
    } else {
        printf(expected_exit_wrong_error_msg, expected_exit);
        return 1;
    }

    const char* expected_steps = testing_get_expected_steps();
#define PRINT_EXPECTATIONS()                                             \
    do {                                                                 \
        if (expected_steps[0] != '\0') {                                 \
            printf("Expecting steps: %s\n", expected_steps);             \
        }                                                                \
        if (expected_exit_code != 0) {                                   \
            printf("Expecting exit code: %d\n", expected_exit_code);     \
        }                                                                \
        if (expected_exit_signal != 0) {                                 \
            printf("Expecting exit signal: %d\n", expected_exit_signal); \
        }                                                                \
    } while (0)

    if (expected_exit_code != 0 && expected_exit_signal != 0) {
        PRINT_EXPECTATIONS();
        printf("Expecting both exit code and exit signal is not supported!\n");
        return 1;
    }

    int needs_fork = (expected_exit_signal != 0) || (expected_exit_code != 0) || (expected_steps[0] != '\0');
    if (!needs_fork) {
        is_inside_testing_process = 1;
        return run_tests();
    }

    int pipe_fd[2];
    if (pipe(pipe_fd) < 0) {
        printf("pipe failed: errno=%d message=%s\n", errno, strerror(errno));
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        printf("fork failed: return=%d, errno=%d, message=%s\n", pid, errno, strerror(errno));
        return 1;
    }
    if (pid == 0) {
        close(pipe_fd[0]);                          // close pipe read end in child
        if (dup2(pipe_fd[1], STDOUT_FILENO) < 0) {  // pipe stdout to parent
            printf("dup2 failed: errno=%d message=%s\n", errno, strerror(errno));
            // Still inform the parent we failed.
            const char* msg = "EXPECTATION FAILED: dup2 didn't work, check stdout for details.\n";
            write(pipe_fd[1], msg, strlen(msg));  // If this fails, tough luck, nothing to do.
            return 1;
        }
        close(pipe_fd[1]);  // close pipe write end after dup
        is_inside_testing_process = 1;
        return run_tests();
    }

    close(pipe_fd[1]);  // close write end in parent

    int status = 0;
    char buf[PIPE_BUF_SZ];
    char child_output[CHILD_OUTPUT_MAX_SIZE];
    size_t child_output_size = 0;
    while (1) {
        read_child_output_pipe(pipe_fd[0], buf, child_output, &child_output_size);
        int wait_result = waitpid(pid, &status, WNOHANG);
        if (wait_result < 0) {
            printf("waitpid failed: return=%d, errno=%d, message=%s\n", wait_result, errno, strerror(errno));
            return 1;
        }
        if (wait_result != 0) {
            if (wait_result != pid) {
                printf("waitpid returned different child! wait_result=%d child_pid=%d\n", wait_result, pid);
                return 1;
            }
            break;
        }
    }
    read_child_output_pipe(pipe_fd[0], buf, child_output, &child_output_size);
    child_output[child_output_size] = '\0';

#define PRINT_CHILD_OUTPUT()                         \
    do {                                             \
        printf("------ BEGIN CHILD OUTPUT ------\n"  \
               "%s\n"                                \
               "------  END  CHILD OUTPUT ------\n", \
               child_output);                        \
    } while (0)

    if (strstr(child_output, "EXPECTATION FAILED") != NULL) {
        PRINT_CHILD_OUTPUT();
        printf("Found 'EXPECTATION FAILED' in output, test failed regardless of child exit code / signal.\n");
        return 1;
    }

    char output_steps[CHILD_OUTPUT_MAX_SIZE];
    size_t output_steps_size = 0;
    cursor = child_output;
    while (1) {
        char* next = strstr(cursor, "STEP: ");
        if (next == NULL) {
            break;
        }
        char* step_end = strchr(next, '\n');
        if (step_end == NULL) {
            PRINT_CHILD_OUTPUT();
            printf("Unfinished step!\n");
            return 1;
        }
        if (output_steps_size > 0) {
            output_steps[output_steps_size++] = ',';
        }
        memcpy(output_steps + output_steps_size, next + 6, step_end - (next + 6));
        output_steps_size += (step_end - (next + 6));
        cursor = step_end;
    }
    output_steps[output_steps_size] = '\0';
    if (expected_steps[0] != '\0') {
        if (strcmp(expected_steps, output_steps) != 0) {
            PRINT_CHILD_OUTPUT();
            printf("Steps checking failed!\nExpected steps: %s\nActual   steps: %s\n", expected_steps, output_steps);
            return 1;
        }
    } else {
        if (output_steps_size > 0) {
            PRINT_CHILD_OUTPUT();
            printf("Output includes unexpected steps: %s\nDid you forget to add // EXPECT:STEPS comment to the test?", output_steps);
            return 1;
        }
    }

    if (WIFSIGNALED(status)) {
        if (expected_exit_code == 0 && expected_exit_signal == (int)(WTERMSIG(status))) {
            return 0;
        }
        PRINT_EXPECTATIONS();
        printf("Test process killed by signal %d\n", (int)(WTERMSIG(status)));
        return 1;
    }

    if (WIFEXITED(status)) {
        if (expected_exit_signal == 0 && expected_exit_code == (int)(WEXITSTATUS(status))) {
            return 0;
        }
        PRINT_EXPECTATIONS();
        printf("Test process exited with code %d\n", WEXITSTATUS(status));
        return 1;
    }

    PRINT_EXPECTATIONS();
    printf("I don't know how this can happen: process terminated without exit code or signal? status=%d\n", status);
    return 1;
}
