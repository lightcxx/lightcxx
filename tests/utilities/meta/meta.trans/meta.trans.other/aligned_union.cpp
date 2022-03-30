#include <type_traits>

#include "testing.h"

template<std::size_t ExpectedSize, std::size_t ExpectedAlign, std::size_t Len, class... Types>
constexpr void test_aligned_union() {
    using T = typename std::aligned_union<Len, Types...>::type;
    static_assert(std::is_same_v<T, std::aligned_union_t<Len, Types...>>);
    static_assert(sizeof(T) == ExpectedSize);
    static_assert(alignof(T) == ExpectedAlign);
    static_assert(std::is_trivial_v<T>);
    static_assert(std::is_standard_layout_v<T>);
}

TEST() {
    test_aligned_union<sizeof(long), alignof(long), 0, long, char[2], int>();
    test_aligned_union<sizeof(long), alignof(long), 0, char[2], long, int>();
    test_aligned_union<sizeof(long), alignof(long), 0, char[2], int, long>();

    test_aligned_union<14 * alignof(long), alignof(long), 14 * alignof(long), long, char[2], int>();
    test_aligned_union<14 * alignof(long), alignof(long), 14 * alignof(long), char[2], long, int>();
    test_aligned_union<14 * alignof(long), alignof(long), 14 * alignof(long), char[2], int, long>();

    test_aligned_union<8 * sizeof(char), alignof(char), 0, char[8], char[3]>();
    test_aligned_union<3 * sizeof(float), alignof(float), 0, float[3], float>();
    test_aligned_union<15 * sizeof(float), alignof(float), 15 * sizeof(float), float[3], float>();

    constexpr auto size = (33 * sizeof(char) + alignof(long long) - 1) / alignof(long long) * alignof(long long);
    test_aligned_union<size, alignof(long long), 0, char[33], long long>();
}
