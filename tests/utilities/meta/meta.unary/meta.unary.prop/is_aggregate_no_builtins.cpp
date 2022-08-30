// EXPECT:NO_COMPILE "std::is_aggregate is not supported on this compiler."

#define _LIGHTCXX_BUILTINS_DONT_USE_ANY

#include <type_traits>

struct Aggregate {
    int x;
    int y;
};

static_assert(std::is_aggregate<Aggregate>::value);
