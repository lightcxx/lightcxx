// EXPECT:NO_COMPILE 3

#include <ratio>

#if NEGATIVE_COMPILE_ITERATION == 0
static_assert(std::ratio<14, 0>::den == 0);
#elif NEGATIVE_COMPILE_ITERATION == 1
static_assert(std::ratio<14, -9223372036854775808>::num == 14);
#elif NEGATIVE_COMPILE_ITERATION == 2
static_assert(std::ratio<-9223372036854775808, 14>::den == 14);
#endif
