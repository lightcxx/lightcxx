// EXPECT:NO_COMPILE 5

#include <ratio>

#if NEGATIVE_COMPILE_ITERATION == 0  // Addition
static_assert(std::is_object_v<std::ratio_add<std::ratio<1, 3>, std::ratio<INTMAX_MAX, 3>>>);
#elif NEGATIVE_COMPILE_ITERATION == 1  // Subtraction
static_assert(std::is_object_v<std::ratio_subtract<std::ratio<-5, 3>, std::ratio<INTMAX_MAX, 3>>>);
#elif NEGATIVE_COMPILE_ITERATION == 2  // Multiplication
static_assert(std::is_object_v<std::ratio_multiply<std::ratio<INTMAX_MAX / 7>, std::ratio<15>>>);
#elif NEGATIVE_COMPILE_ITERATION == 3  // Division
static_assert(std::is_object_v<std::ratio_divide<std::ratio<INTMAX_MAX / 7>, std::ratio<-1, 15>>>);
#elif NEGATIVE_COMPILE_ITERATION == 4  // Division by 0.
static_assert(std::is_object_v<std::ratio_divide<std::ratio<1>, std::ratio<0, 7>>>);
#endif
