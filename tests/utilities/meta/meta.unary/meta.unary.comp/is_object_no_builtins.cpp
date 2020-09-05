// REQUEST:NO_TEST_LIB "The testing library depends on <type_traits>."
// REQUEST:EXTRA_DEFINITIONS _LIGHTCXX_DONT_USE_BUILTINS
// EXPECT:NO_COMPILE "is_(class|enum|union) is not supported on this compiler."

#include <type_traits>

int main() {
    static_assert(std::is_object<int>::value);
    return 0;
}
