// EXPECT:EXIT KILLED BY SIGNAL SIGABRT

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

    ::std::at_quick_exit([] { FAIL(); });

    ::std::abort();
}
