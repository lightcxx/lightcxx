// EXPECT:NO_COMPILE 3

#include <type_traits>

#if NC_TEST_ID == 0
using T = typename std::enable_if<false>::type;
#elif NC_TEST_ID == 1
using T = typename std::enable_if<false, int>::type;
#elif NC_TEST_ID == 2
using T = std::enable_if_t<false>;
#elif NC_TEST_ID == 3
using T = std::enable_if_t<false, int>;
#endif
