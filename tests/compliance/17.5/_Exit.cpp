//EXPECT:EXIT_CODE 4
//EXPECT:OUTPUT_NOT_CONTAINS "fail"

#include <cstdlib>

#include <stdio.h>

#include "testing/test.h"

struct FailPrinter {
    const char* name = "local";

    ~FailPrinter() { fprintf(stderr, "fail: destructor of %s\n", name); }
};

[[maybe_unused]] FailPrinter global{.name = "global"};
[[maybe_unused]] thread_local FailPrinter t_local{.name = "thread_local"};

void Testing::run() {
    [[maybe_unused]] static FailPrinter inline_static{.name = "inline_static"};
    [[maybe_unused]] thread_local FailPrinter inline_t_local{.name = "inline_thread_local"};
    [[maybe_unused]] FailPrinter local;

    ::std::atexit([] { fprintf(stderr, "fail: atexit\n"); });

    ::std::at_quick_exit([] { fprintf(stderr, "fail: at_quick_exit\n"); });

    ::std::_Exit(4);
}
