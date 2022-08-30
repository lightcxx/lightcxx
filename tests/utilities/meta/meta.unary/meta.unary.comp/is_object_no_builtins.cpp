// EXPECT:NO_COMPILE "std::is_(class|enum|union) is not supported on this compiler."

#define _LIGHTCXX_BUILTINS_DONT_USE_ANY

#include <type_traits>

static_assert(std::is_object<int>::value);
