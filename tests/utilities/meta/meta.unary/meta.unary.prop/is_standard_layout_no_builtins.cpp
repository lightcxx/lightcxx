// EXPECT:NO_COMPILE "std::is_standard_layout is not supported on this compiler."

#define _LIGHTCXX_DONT_USE_BUILTINS

#include <type_traits>

static_assert(std::is_standard_layout<int>::value);
