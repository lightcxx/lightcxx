// EXPECT:NO_COMPILE 10

#include <cstddef>

#include "testing.h"

struct Aggregate {
    int x;
};

TEST() {
    ::std::byte b{3};
    const char* str;
    Aggregate ag;
#if NEGATIVE_COMPILE_ITERATION == 0
    b << str;
#elif NEGATIVE_COMPILE_ITERATION == 1
    b <<= str;
#elif NEGATIVE_COMPILE_ITERATION == 2
    b >> str;
#elif NEGATIVE_COMPILE_ITERATION == 3
    b >>= str;
#elif NEGATIVE_COMPILE_ITERATION == 4
    ::std::to_integer<const char*>(b);
#elif NEGATIVE_COMPILE_ITERATION == 5
    b << ag;
#elif NEGATIVE_COMPILE_ITERATION == 6
    b <<= ag;
#elif NEGATIVE_COMPILE_ITERATION == 7
    b >> ag;
#elif NEGATIVE_COMPILE_ITERATION == 8
    b >>= ag;
#elif NEGATIVE_COMPILE_ITERATION == 9
    ::std::to_integer<Aggregate>(b);
#endif
}
