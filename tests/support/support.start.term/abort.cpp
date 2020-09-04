// EXPECT:EXIT KILLED BY SIGNAL SIGABRT

#include <cstdlib>

#include "testing.h"

struct FailPrinter {
    ~FailPrinter() {
        Testing::fail();
    }
};

[[maybe_unused]] FailPrinter global{};
[[maybe_unused]] thread_local FailPrinter t_local{};

TEST() {
    [[maybe_unused]] static FailPrinter inline_static{};
    [[maybe_unused]] thread_local FailPrinter inline_t_local{};
    [[maybe_unused]] FailPrinter local;

    ::std::atexit([] { fail(); });

    ::std::at_quick_exit([] { fail(); });

    ::std::abort();
}
