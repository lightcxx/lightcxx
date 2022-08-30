// EXPECT:NO_COMPILE "std::has_unique_object_representations is not supported on this compiler."

#define _LIGHTCXX_BUILTINS_DONT_USE_ANY

#include <type_traits>

static_assert(std::has_unique_object_representations<int>::value);
