// REQUEST:NO_TEST_LIB "The testing library depends on <type_traits>."
// EXPECT:NO_COMPILE "std::is_trivially_destructible is not supported on this compiler."

#define _LIGHTCXX_DONT_USE_BUILTINS

#include <type_traits>

#include "meta/test_unary_trait.h"

int main() {
    static_assert(std::is_trivially_destructible<Class>::value);
    return 0;
}