// REQUEST:NO_TEST_LIB "The testing library depends on <type_traits>."
// REQUEST:EXTRA_DEFINITIONS _LIGHTCXX_DONT_USE_BUILTINS
// EXPECT:NO_COMPILE "is_enum is not supported on this compiler."

#include <type_traits>

int main() {
    static_assert(std::is_scalar<int>::value);
    return 0;
}
