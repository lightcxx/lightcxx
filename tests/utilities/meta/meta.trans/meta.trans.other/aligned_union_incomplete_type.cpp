// EXPECT:NO_COMPILE "Incomplete"

#include <type_traits>

struct Incomplete;

using T = std::aligned_union_t<12, int, Incomplete, long>;
