// EXPECT:NO_COMPILE "std::is_aggregate is not supported on this compiler."

#define _LIGHTCXX_DONT_USE_BUILTINS

#include <type_traits>

struct Aggregate {
    [[maybe_unused]] int x;
    [[maybe_unused]] int y;
};

static_assert(std::is_aggregate<Aggregate>::value);
