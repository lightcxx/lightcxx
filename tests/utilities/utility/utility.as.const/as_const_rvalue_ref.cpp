// EXPECT:NO_COMPILE 2

#include <utility>

#include "testing.h"

struct Struct {};

TEST() {
#if NEGATIVE_COMPILE_ITERATION == 0
    std::as_const(Struct{});
#elif NEGATIVE_COMPILE_ITERATION == 1
    std::as_const(3);
#endif
}
