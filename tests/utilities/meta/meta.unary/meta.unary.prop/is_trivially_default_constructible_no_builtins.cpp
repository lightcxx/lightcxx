// EXPECT:NO_COMPILE "std::is_trivially_default_constructible is not supported on this compiler."

#define _LIGHTCXX_DONT_USE_BUILTINS

#include <type_traits>

static_assert(!std::is_trivially_default_constructible<int>::value);
