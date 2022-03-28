// EXPECT:NO_COMPILE "std::is_(class|enum|union) is not supported on this compiler."

#define _LIGHTCXX_DONT_USE_BUILTINS

#include <type_traits>

struct S {
    int f;
};

static_assert(std::is_invocable<decltype(&S::f), S>::value);
