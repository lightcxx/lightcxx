// EXPECT:NO_COMPILE 5

#include "test_integer_sequence.h"

#if NEGATIVE_COMPILE_ITERATION == 0
constexpr auto size = std::integer_sequence<void>::size();
#elif NEGATIVE_COMPILE_ITERATION == 1
constexpr auto size = std::integer_sequence<double, 1.0, 2.0>::size();
#elif NEGATIVE_COMPILE_ITERATION == 2
constexpr auto size = std::integer_sequence<int*, nullptr>::size();
#elif NEGATIVE_COMPILE_ITERATION == 3
constexpr auto size = std::integer_sequence<int&>::size();
#elif NEGATIVE_COMPILE_ITERATION == 4
constexpr auto size = std::integer_sequence<int[10]>::size();
#endif
