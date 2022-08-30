// EXPECT:NO_COMPILE "std::is_class is not supported on this compiler."

#define _LIGHTCXX_BUILTINS_DONT_USE_ANY

#include <type_traits>

static_assert(!std::is_class<int>::value);
