#include "testing.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

namespace {

int stored_argc;
char** stored_argv;
const char* current_test_name = nullptr;

}  // namespace

namespace Testing {

void fail(std::source_location loc) noexcept {
    fprintf(stderr, "EXPECTATION FAILED in test %s: in function %s (%s:%d)\n", current_test_name,
            loc.function_name(), loc.file_name(), loc.line());
    _Exit(1);
}

void expect(bool cnd, std::source_location loc) noexcept {
    if (!cnd) {
        fail(loc);
    }
}

void step(const char* msg, ...) noexcept {
    fprintf(stderr, "STEP: ");
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    fprintf(stderr, "\n");
}

int get_argc() {
    return stored_argc;
}

char** get_argv() {
    return stored_argv;
}

Test* Test::head = nullptr;
Test* Test::tail = nullptr;

Test::Test(void (*test)(), const char* name) noexcept: test(test), name(name) {
    if (head == nullptr) {
        head = this;
    }
    if (tail != nullptr) {
        tail->next = this;
    }
    tail = this;
}

}  // namespace Testing

int main(int argc, char** argv) {
    stored_argc = argc;
    stored_argv = argv;
    Testing::Test* t = Testing::Test::head;
    while (t != nullptr) {
        current_test_name = t->name;
        t->test();
        t = t->next;
    }
    current_test_name = nullptr;
    return 0;
}
