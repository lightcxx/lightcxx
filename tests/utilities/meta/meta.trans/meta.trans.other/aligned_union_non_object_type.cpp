// EXPECT:NO_COMPILE "All types must be complete object types for std::aligned_union."

#include <type_traits>

using T = std::aligned_union_t<12, int, int&, long>;
