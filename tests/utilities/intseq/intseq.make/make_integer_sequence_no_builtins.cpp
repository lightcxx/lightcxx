// EXPECT:NO_COMPILE "std::make_integer_sequence is not supported on this compiler."

#define _LIGHTCXX_BUILTINS_DONT_USE_ANY

#include <utility>

constexpr auto size = std::make_integer_sequence<std::size_t, 3>::size();
