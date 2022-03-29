#include <type_traits>

#include "testing.h"

template<std::size_t Len, std::size_t Align>
constexpr void test_aligned_storage() {
    using T = typename std::aligned_storage<Len, Align>::type;
    static_assert(std::is_same_v<T, std::aligned_storage_t<Len, Align>>);
    static_assert(sizeof(T) == (Len + Align - 1) / Align * Align);
    static_assert(alignof(T) == Align);
    static_assert(std::is_trivial_v<T>);
    static_assert(std::is_standard_layout_v<T>);
}

template<std::size_t Len, std::size_t ExpectedAlign>
constexpr void test_default_aligned_storage() {
    using T = typename std::aligned_storage<Len>::type;
    static_assert(std::is_same_v<T, std::aligned_storage_t<Len>>);
    static_assert(sizeof(T) == (Len + ExpectedAlign - 1) / ExpectedAlign * ExpectedAlign);
    static_assert(alignof(T) == ExpectedAlign);
    static_assert(std::is_trivial_v<T>);
    static_assert(std::is_standard_layout_v<T>);
}

TEST() {
    test_default_aligned_storage<1, 1>();
    test_aligned_storage<1, 1>();
    test_aligned_storage<1, 2>();
    test_aligned_storage<1, 4>();
    test_aligned_storage<1, 8>();
    test_aligned_storage<1, 16>();
    test_aligned_storage<1, 32>();
    test_aligned_storage<1, 64>();
    test_aligned_storage<1, 128>();
    test_aligned_storage<1, 256>();
    test_aligned_storage<1, 512>();
    test_aligned_storage<1, 1024>();
    test_aligned_storage<1, 2048>();
    test_aligned_storage<1, 4096>();

    test_default_aligned_storage<2, 2>();
    test_aligned_storage<2, 1>();
    test_aligned_storage<2, 2>();

    test_default_aligned_storage<4, 4>();
    test_aligned_storage<4, 1>();
    test_aligned_storage<4, 2>();
    test_aligned_storage<4, 4>();

    test_default_aligned_storage<6, 4>();
    test_aligned_storage<6, 1>();
    test_aligned_storage<6, 2>();
    test_aligned_storage<6, 4>();
    test_aligned_storage<6, 8>();

    test_default_aligned_storage<7, 4>();
    test_aligned_storage<7, 1>();
    test_aligned_storage<7, 2>();
    test_aligned_storage<7, 4>();
    test_aligned_storage<7, 8>();

    test_default_aligned_storage<2022, alignof(std::max_align_t)>();
    test_aligned_storage<2022, 1>();
    test_aligned_storage<2022, 2>();
    test_aligned_storage<2022, 4>();
    test_aligned_storage<2022, 8>();
    test_aligned_storage<2022, 16>();
    test_aligned_storage<2022, 32>();
    test_aligned_storage<2022, 64>();
    test_aligned_storage<2022, 128>();
    test_aligned_storage<2022, 256>();
    test_aligned_storage<2022, 512>();
    test_aligned_storage<2022, 1024>();
    test_aligned_storage<2022, 2048>();
    test_aligned_storage<2022, 4096>();
}
