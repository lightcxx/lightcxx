// EXPECT:NO_COMPILE "At least one type is required for std::aligned_union."

#include <type_traits>

using T = std::aligned_union_t<12>;
