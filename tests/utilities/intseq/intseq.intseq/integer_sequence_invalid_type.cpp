// EXPECT:NO_COMPILE 4

#include "test_integer_sequence.h"

#if NC_TEST_ID == 0
constexpr auto size = std::integer_sequence<void>::size();
#elif NC_TEST_ID == 1
constexpr auto size = std::integer_sequence<double, 1.0, 2.0>::size();
#elif NC_TEST_ID == 2
constexpr auto size = std::integer_sequence<int*, nullptr>::size();
#elif NC_TEST_ID == 3
constexpr auto size = std::integer_sequence<int&>::size();
#elif NC_TEST_ID == 4
constexpr auto size = std::integer_sequence<int[10]>::size();
#endif
