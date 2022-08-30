// EXPECT:NO_COMPILE "std::is_empty is not supported on this compiler."

#define _LIGHTCXX_BUILTINS_DONT_USE_ANY

#include <type_traits>

struct Empty {};

static_assert(std::is_empty<Empty>::value);
