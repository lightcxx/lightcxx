// EXPECT:NO_COMPILE "std::is_union is not supported on this compiler."

#define _LIGHTCXX_DONT_USE_BUILTINS

#include <type_traits>

static_assert(!std::is_union<int>::value);
