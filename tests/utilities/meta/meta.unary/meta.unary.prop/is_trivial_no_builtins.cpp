// EXPECT:NO_COMPILE "std::is_trivial is not supported on this compiler."

#define _LIGHTCXX_BUILTINS_DONT_USE_ANY

#include <type_traits>

struct Trivial {};

static_assert(std::is_trivial<Trivial>::value);
