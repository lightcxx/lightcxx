#define _LIGHTCXX_BUILTINS_DONT_USE_ANY

// This test checks that simply including the header still compiles (there is no hard error) even
// when a compiler does not support builtins that are required (__is_enum, __is_class etc.).
#include <type_traits>
