#include <type_traits>

#include "meta/test_unary_trait.h"

template<class T, unsigned I, std::size_t e>
constexpr bool test_extent() {
    static_assert(std::extent<T, I>::value == e);
    static_assert(std::is_base_of_v<std::integral_constant<std::size_t, e>, std::extent<T, I>>);
    static_assert(std::is_same_v<typename std::extent<T, I>::value_type, std::size_t>);
    static_assert(std::extent<T, I>{} == e);
    static_assert((std::size_t)std::extent<T, I>{} == e);
    static_assert(noexcept((std::size_t)std::extent<T, I>{}));
    static_assert(std::extent<T, I>{}() == e);
    static_assert(noexcept(std::extent<T, I>{}()));
    static_assert(std::is_same_v<std::size_t, decltype(std::extent<T, I>{}())>);
    static_assert(std::is_same_v<typename std::extent<T, I>::type, std::integral_constant<std::size_t, e>>);
    static_assert(std::is_same_v<decltype(std::extent_v<T, I>), const std::size_t>);
    static_assert(std::extent_v<T, I> == e);
    return true;
}

template<std::size_t ext0, std::size_t ext1, std::size_t ext2, std::size_t ext3, std::size_t ext4, class... T>
constexpr bool test_extents() {
    (test_extent<T, 0, ext0>() && ...);
    (test_extent<T, 1, ext1>() && ...);
    (test_extent<T, 2, ext2>() && ...);
    (test_extent<T, 3, ext3>() && ...);
    (test_extent<T, 4, ext4>() && ...);
    return true;
}

static_assert(test_extents<0, 0, 0, 0, 0, void, std::nullptr_t, void*, int, unsigned long long, float, double, int (*)(), int(int), int (&)(int)>());

static_assert(test_extents<0, 0, 0, 0, 0, int[], int*[], void*[]>());

static_assert(test_extents<3, 141, 5, 0, 0, int[3][141][5], int* [3][141][5], void* [3][141][5]>());

static_assert(test_extents<0, 141, 5, 0, 0, int[][141][5], int*[][141][5], void*[][141][5]>());
