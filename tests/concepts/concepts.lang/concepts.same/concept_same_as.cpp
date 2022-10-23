#include <concepts>

template<std::same_as<int> T>
constexpr T copy_of(T value) {
    return value;
}

static_assert(copy_of(3) == 3);
static_assert(copy_of(-1) == -1);

static_assert(std::same_as<int, int>);
static_assert(std::same_as<const int, const int>);
static_assert(std::same_as<volatile int, volatile int>);
static_assert(std::same_as<volatile const int, const volatile int>);
static_assert(!std::same_as<int, const int>);
static_assert(!std::same_as<int, long>);
