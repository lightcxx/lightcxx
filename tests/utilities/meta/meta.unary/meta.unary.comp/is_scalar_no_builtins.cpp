// EXPECT:NO_COMPILE "std::is_enum is not supported on this compiler."

#define _LIGHTCXX_BUILTINS_DONT_USE_ANY

#include <type_traits>

static_assert(std::is_scalar<int>::value);
