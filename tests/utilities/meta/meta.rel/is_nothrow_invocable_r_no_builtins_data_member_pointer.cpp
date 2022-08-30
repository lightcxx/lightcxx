// EXPECT:NO_COMPILE "std::is_(class|enum|union) is not supported on this compiler."

#define _LIGHTCXX_BUILTINS_DONT_USE_ANY

#include <type_traits>

struct S {
    int f;
};

static_assert(std::is_nothrow_invocable_r<int, decltype(&S::f), S>::value);
