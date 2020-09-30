// EXPECT:EXIT CODE = 4
// EXPECT:STEPS "at_quick_exit"

#include <cstdlib>

#include "testing.h"

struct FailPrinter {
    ~FailPrinter() {
        fail();
    }
};

[[maybe_unused]] FailPrinter global{};
[[maybe_unused]] thread_local FailPrinter t_local{};

TEST() {
    [[maybe_unused]] static FailPrinter inline_static{};
    [[maybe_unused]] thread_local FailPrinter inline_t_local{};
    [[maybe_unused]] FailPrinter local;

    ::std::atexit([] { fail(); });

    ::std::at_quick_exit([] { step("at_quick_exit"); });

    ::std::quick_exit(4);
}
