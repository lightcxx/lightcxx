#include "testing.h"

#include <type_traits>

template<class T, T val>
constexpr void test_integral_constant() {
    static_assert(std::integral_constant<T, val>::value == val);
    static_assert(std::is_same_v<T, typename std::integral_constant<T, val>::value_type>);
    static_assert(std::is_same_v<std::integral_constant<T, val>, typename std::integral_constant<T, val>::type>);
    static_assert(std::integral_constant<T, val>{} == val);
    static_assert((T)std::integral_constant<T, val>{} == val);
    static_assert(noexcept((T)std::integral_constant<T, val>{}));
    static_assert(std::integral_constant<T, val>{}() == val);
    static_assert(noexcept(std::integral_constant<T, val>{}()));
    static_assert(std::is_same_v<T, decltype(std::integral_constant<T, val>{}())>);
}

template<class T, bool val>
constexpr void test_bool_constant() {
    static_assert(T::value == val);
    static_assert(std::is_same_v<bool, typename T::value_type>);
    static_assert(std::is_same_v<T, typename T::type>);
    static_assert(T{} == val);
    static_assert((bool)T{} == val);
    static_assert(noexcept((bool)T{}));
    static_assert(T{}() == val);
    static_assert(noexcept(T{}()));
    static_assert(std::is_same_v<bool, decltype(T{}())>);
}

TEST() {
    test_integral_constant<bool, true>();
    test_integral_constant<bool, false>();
    test_integral_constant<char, 0>();
    test_integral_constant<char, 100>();
    test_integral_constant<signed char, -100>();
    test_integral_constant<signed char, 0>();
    test_integral_constant<signed char, 100>();
    test_integral_constant<short, -100>();
    test_integral_constant<short, 0>();
    test_integral_constant<short, 100>();
    test_integral_constant<int, -100>();
    test_integral_constant<int, 0>();
    test_integral_constant<int, 100>();
    test_integral_constant<long, -100>();
    test_integral_constant<long, 0>();
    test_integral_constant<long, 100>();
    test_integral_constant<long long, -100>();
    test_integral_constant<long long, 0>();
    test_integral_constant<long long, 100>();
    test_integral_constant<unsigned char, 0>();
    test_integral_constant<unsigned char, 100>();
    test_integral_constant<unsigned short, 0>();
    test_integral_constant<unsigned short, 100>();
    test_integral_constant<unsigned int, 0>();
    test_integral_constant<unsigned int, 100>();
    test_integral_constant<unsigned long, 0>();
    test_integral_constant<unsigned long, 100>();
    test_integral_constant<unsigned long long, 0>();
    test_integral_constant<unsigned long long, 100>();

    static_assert(std::is_same_v<std::bool_constant<true>, std::integral_constant<bool, true>>);
    static_assert(std::is_same_v<std::bool_constant<false>, std::integral_constant<bool, false>>);
    test_bool_constant<std::bool_constant<true>, true>();
    test_bool_constant<std::bool_constant<false>, false>();

    static_assert(std::is_same_v<std::true_type, std::bool_constant<true>>);
    test_bool_constant<std::true_type, true>();

    static_assert(std::is_same_v<std::false_type, std::bool_constant<false>>);
    test_bool_constant<std::false_type, false>();
}
