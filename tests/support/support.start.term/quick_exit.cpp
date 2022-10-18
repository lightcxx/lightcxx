// EXPECT:EXIT CODE = 4
// EXPECT:STEPS at_quick_exit

#include <cstdlib>

#include "testing.h"

struct FailPrinter {
    ~FailPrinter() {
        FAIL();
    }
};

FailPrinter global{};
thread_local FailPrinter t_local{};

TEST() {
    static FailPrinter inline_static{};
    thread_local FailPrinter inline_t_local{};
    FailPrinter local;

    ::std::atexit([] { FAIL(); });

    ::std::at_quick_exit([] { step("at_quick_exit"); });

    ::std::quick_exit(4);
}
