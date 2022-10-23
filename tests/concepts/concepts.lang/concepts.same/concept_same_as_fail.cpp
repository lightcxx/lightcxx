// EXPECT:NO_COMPILE "std::same_as"

#include <concepts>

template<std::same_as<int> T>
constexpr T copy_of(T value) {
    return value;
}

static_assert(copy_of(3L) == 3L);
