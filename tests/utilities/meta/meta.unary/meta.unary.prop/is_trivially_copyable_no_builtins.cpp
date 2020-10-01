// EXPECT:NO_COMPILE "std::is_trivially_copyable is not supported on this compiler."

#define _LIGHTCXX_DONT_USE_BUILTINS

#include <type_traits>

#include "meta/test_unary_trait.h"

static_assert(std::is_trivially_copyable<Class>::value);
