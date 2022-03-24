#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static const char* testing_current_test_name;
static int testing_stored_argc;
static char** testing_stored_argv;

void testing_fail_impl(const char* func, const char* file, int line) {
    fprintf(stderr, "EXPECTATION FAILED in test %s: in function %s (%s:%d)\n",
            testing_current_test_name, func, file, line);
    _Exit(1);
}

void testing_expect_impl(int cnd, const char* func, const char* file, int line) {
    if (!cnd) {
        testing_fail_impl(func, file, line);
    }
}

void testing_step_impl(const char* msg, ...) {
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

typedef struct Test {
    void (*test)();
    const char* name;
} Test;

static Test tests[1000];
static int num_tests = 0;

void testing_register_test(void (*test)(), const char* name) {
    if (num_tests == 1000) {
        fprintf(stderr, "EXPECTATION FAILED: Too many registered tests.\n");
        abort();
    }
    tests[num_tests].test = test;
    tests[num_tests].name = name;
    num_tests++;
}

int main(int argc, char** argv) {
    testing_stored_argc = argc;
    testing_stored_argv = argv;
    for (int i = 0; i < num_tests; i++) {
        testing_current_test_name = tests[i].name;
        tests[i].test();
    }
    return 0;
}
