#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" using test_func = const char * (*)(int) noexcept;

struct test_case {
    const char* name;
    test_func light;
    test_func reference;
};

static int run_test_case(test_case t_case, int index) {
    int test_index;
    int result = EXIT_SUCCESS;
    for (test_index = 0;; test_index++) {
        auto a = t_case.light(test_index);
        auto b = t_case.reference(test_index);
        if (a == nullptr && b == nullptr) {
            break;
        }
        if (a == nullptr) {
            printf("systest case %d %s: test %d failed:\n"
                   "  light     stream line: <STREAM DONE>\n"
                   "  reference stream line: %s\n",
                   index, t_case.name, test_index, b);
            return EXIT_FAILURE;
        }
        if (b == nullptr) {
            printf("systest case %d %s: test %d failed:\n"
                   "  light     stream line: %s\n"
                   "  reference stream line: <STREAM DONE>\n",
                   index, t_case.name, test_index, a);
            return EXIT_FAILURE;
        }
        if (strcmp(a, b) != 0) {
            printf("systest case %d %s: test %d failed:\n"
                   "  light     stream line: %s\n"
                   "  reference stream line: %s\n",
                   index, t_case.name, test_index, a, b);
            result = EXIT_FAILURE;
        } else {
            printf("systest case %d %s: test %d succeeded: %s\n",
                   index,  t_case.name, test_index, a);
        }
    }
    return result;
}

template<size_t N>
static int run_test_cases(const test_case (&test_cases)[N]) {
    int exit_code = EXIT_SUCCESS;
    for (size_t i = 0; i < N; i++) {
        if (run_test_case(test_cases[i], i + 1) == EXIT_FAILURE) {
            exit_code = EXIT_FAILURE;
        }
    }
    return exit_code;
}

extern "C" const char* stdint_light(int test_index) noexcept;
extern "C" const char* stdint_libc(int test_index) noexcept;
extern "C" const char* errno_light(int test_index) noexcept;
extern "C" const char* errno_libc(int test_index) noexcept;

int main() {
    return run_test_cases({
      {"stdint", stdint_light, stdint_libc},
      {"errno", errno_light, errno_libc},
    });
}
