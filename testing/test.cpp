#include "testing/test.h"

#include <stdarg.h>
#include <stdio.h>

namespace {

int exit_code = 0;

}

namespace Testing {

void fail(const char* message, ...) noexcept {
    fprintf(stderr, "EXPECTATION FAILED");
    if (message[0] != '\0') {
        fprintf(stderr, ": ");
        va_list args;
        va_start(args, message);
        vfprintf(stderr, message, args);
        va_end(args);
    }
    fprintf(stderr, "\n");
    exit_code = 1;
}

void expect(bool condition, const char* message, ...) noexcept {
    if (!condition) {
        fprintf(stderr, "EXPECTATION FAILED");
        if (message[0] != '\0') {
            fprintf(stderr, ": ");
            va_list args;
            va_start(args, message);
            vfprintf(stderr, message, args);
            va_end(args);
        }
        fprintf(stderr, "\n");
        ::_Exit(1);
    }
}

void step(const char* message, ...) noexcept {
    fprintf(stderr, "STEP: ");
    va_list args;
    va_start(args, message);
    vfprintf(stderr, message, args);
    va_end(args);
    fprintf(stderr, "\n");
}

__attribute__((__weak__)) void run() {}

__attribute__((__weak__)) void runWithArgs(int argc, char** argv) {
    run();
}

}  // namespace Testing

int main(int argc, char** argv) {
    Testing::runWithArgs(argc, argv);
    return exit_code;
}
