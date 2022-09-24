#ifdef NDEBUG
#    undef NDEBUG
#endif
#include <cassert>

#include "testing.h"

TEST() {
    bool value_true = true;
    compiler_forget(value_true);
    assert(value_true);

    assert(true);

    constexpr auto f = [](bool value) {
        assert(value);
        return true;
    };
    static_assert(f(true));   // Inside constant expression
}
