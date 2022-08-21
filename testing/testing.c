#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

typedef void (*test_t)();
static test_t tests[1000];
static const char* test_names[1000];
static int num_tests = 0;
static int is_inside_testing_process = 0;
static const char* testing_current_test_name;
static int testing_stored_argc;
static char** testing_stored_argv;

struct testing_global_var {
    void* obj;
    void (*ctor)(void*);
    void (*dtor)(void*);
};
typedef struct testing_global_var testing_global_var_t;
static testing_global_var_t globals[1000];
static int num_globals = 0;

void testing_fail_impl(const char* func, const char* file, int line) {
    if (!is_inside_testing_process) {
        return;
    }
    fprintf(stderr, "EXPECTATION FAILED in test %s: in function %s (%s:%d)\n", testing_current_test_name, func, file, line);
    _Exit(1);
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
    fprintf(stderr, "STEP: ");
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    fprintf(stderr, "\n");
}

int testing_get_argc() {
    return testing_stored_argc;
}

char** testing_get_argv() {
    return testing_stored_argv;
}

void testing_register_test(void (*test)(), const char* name) {
    if (num_tests == 1000) {
        fprintf(stderr, "EXPECTATION FAILED: Too many registered tests.\n");
        abort();
    }
    tests[num_tests] = test;
    test_names[num_tests] = name;
    num_tests++;
}

void testing_register_global(void* obj, void (*ctor)(void*), void (*dtor)(void*)) {
    if (num_globals == 1000) {
        fprintf(stderr, "EXPECTATION FAILED: Too many registered globals.\n");
        abort();
    }
    globals[num_globals].obj = obj;
    globals[num_globals].ctor = ctor;
    globals[num_globals].dtor = dtor;
    num_globals++;
}

int run_tests() {
    for (int i = 0; i < num_globals; i++) {
        globals[i].ctor(globals[i].obj);
    }
    for (int i = 0; i < num_tests; i++) {
        testing_current_test_name = test_names[i];
        tests[i]();
    }
    for (int i = 0; i < num_globals; i++) {
        globals[i].dtor(globals[i].obj);
    }
    return 0;
}

int main(int argc, char** argv) {
    testing_stored_argc = argc;
    testing_stored_argv = argv;

    char* needs_fork = getenv("LIGHTCXX_NEEDS_FORK");
    if (needs_fork == 0 || *needs_fork == '\0' || *needs_fork == '0') {
        is_inside_testing_process = 1;
        return run_tests();
    }

    pid_t pid = fork();
    if (pid == -1) {
        printf("EXPECTATION FAILED: FORK FAILED. return=%d, errno=%d, message=%s\n", pid, errno, strerror(errno));
        return 1;
    }
    if (pid == 0) {
        is_inside_testing_process = 1;
        return run_tests();
    }
    int status = 0;
    int wait_ret = wait(&status);
    if (wait_ret != pid) {
        printf("EXPECTATION FAILED: WAIT FAILED. return=%d, errno=%d, message=%s\n", wait_ret, errno, strerror(errno));
        return 1;
    }
    printf("\n----\n");
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGABRT) {
            printf("PROCESS EXIT KILLED BY SIGNAL SIGABRT\n");
        } else {
            printf("PROCESS EXIT KILLED BY SIGNAL %d\n", WTERMSIG(status));
        }
    } else if (WIFEXITED(status)) {
        printf("PROCESS EXIT CODE = %d\n", WEXITSTATUS(status));
    } else {
        printf("EXPECTATION FAILED: PROCESS EXITED BY UNKNOWN MEANS. status=%d\n", status);
    }
    return 0;
}
