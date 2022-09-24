#ifdef NDEBUG
#    undef NDEBUG
#endif
#define NDEBUG
#include <cassert>

#include "testing.h"

TEST() {
    bool value_true = true;
    compiler_forget(value_true);
    assert(value_true);

    bool value_false = false;
    compiler_forget(value_false);
    assert(value_false);  // will not abort, because NDEBUG

    constexpr auto f = [](bool value) {
        (void)value;
        assert(value);
        return true;
    };
    static_assert(f(true));   // Inside constant expression
    static_assert(f(false));  // Inside constant expression
}
