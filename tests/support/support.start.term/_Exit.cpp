// EXPECT:EXIT CODE = 4

#include <cstdlib>

#include "testing.h"

struct FailPrinter {
    ~FailPrinter() {
        fail();
    }
};

FailPrinter global{};
thread_local FailPrinter t_local{};

TEST() {
    static FailPrinter inline_static{};
    thread_local FailPrinter inline_t_local{};
    FailPrinter local;

    ::std::atexit([] { fail(); });

    ::std::at_quick_exit([] { fail(); });

    ::std::_Exit(4);
}
