// EXPECT:NO_COMPILE "std::is_final is not supported on this compiler."

#define _LIGHTCXX_BUILTINS_DONT_USE_ANY

#include <type_traits>

struct Final final {};

static_assert(std::is_final<Final>::value);
