// EXPECT:EXIT CODE = 4

#include <cstdlib>

#include "testing/test.h"

struct FailPrinter {
    const char* name = "local";

    ~FailPrinter() {
        Testing::fail("destructor of %s", name);
    }
};

[[maybe_unused]] FailPrinter global{.name = "global"};
[[maybe_unused]] thread_local FailPrinter t_local{.name = "thread_local"};

void Testing::run() {
    [[maybe_unused]] static FailPrinter inline_static{.name = "inline_static"};
    [[maybe_unused]] thread_local FailPrinter inline_t_local{.name = "inline_thread_local"};
    [[maybe_unused]] FailPrinter local;

    ::std::atexit([] { fail("atexit"); });

    ::std::at_quick_exit([] { fail("at_quick_exit"); });

    ::std::_Exit(4);
}
