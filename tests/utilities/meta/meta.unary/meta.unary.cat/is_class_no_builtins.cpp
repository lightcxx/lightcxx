// REQUEST:NO_TEST_LIB "The testing library depends on <type_traits>."
// EXPECT:NO_COMPILE "std::is_class is not supported on this compiler."

#define _LIGHTCXX_DONT_USE_BUILTINS

#include <type_traits>

int main() {
    static_assert(!std::is_class<int>::value);
    return 0;
}
