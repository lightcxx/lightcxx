// EXPECT:NO_COMPILE "std::is_trivially_copy_constructible is not supported on this compiler."

#define _LIGHTCXX_DONT_USE_BUILTINS

#include <type_traits>

struct Trivial {};

static_assert(std::is_trivially_copy_constructible<Trivial>::value);
