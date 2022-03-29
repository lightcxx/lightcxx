// EXPECT:NO_COMPILE "Length of std::aligned_storage must be non-zero."

#include <type_traits>

using T = std::aligned_storage_t<0>;
