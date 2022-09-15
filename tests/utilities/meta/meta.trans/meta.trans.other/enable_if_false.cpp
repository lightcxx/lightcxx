// EXPECT:NO_COMPILE 4

#include <type_traits>

#if NEGATIVE_COMPILE_ITERATION == 0
using T = typename std::enable_if<false>::type;
#elif NEGATIVE_COMPILE_ITERATION == 1
using T = typename std::enable_if<false, int>::type;
#elif NEGATIVE_COMPILE_ITERATION == 2
using T = std::enable_if_t<false>;
#elif NEGATIVE_COMPILE_ITERATION == 3
using T = std::enable_if_t<false, int>;
#endif
