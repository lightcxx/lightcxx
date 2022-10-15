#include <compare>
#include <ratio>

template<class R1, class R2, int expected>
constexpr bool check_ratio_cmp() {
    constexpr bool is_less = (expected == -1);
    constexpr bool is_equal = (expected == 0);
    constexpr bool is_greater = (expected == 1);
    constexpr bool is_less_equal = (is_less || is_equal);
    constexpr bool is_greater_equal = (is_greater || is_equal);

    static_assert(std::is_base_of_v<std::bool_constant<is_equal>, std::ratio_equal<R1, R2>>);
    static_assert(std::is_base_of_v<std::bool_constant<is_equal>, std::ratio_equal<R2, R1>>);
    static_assert(std::ratio_equal_v<R1, R2> == is_equal);
    static_assert(std::ratio_equal_v<R2, R1> == is_equal);

    static_assert(std::is_base_of_v<std::bool_constant<!is_equal>, std::ratio_not_equal<R1, R2>>);
    static_assert(std::is_base_of_v<std::bool_constant<!is_equal>, std::ratio_not_equal<R2, R1>>);
    static_assert(std::ratio_not_equal_v<R1, R2> != is_equal);
    static_assert(std::ratio_not_equal_v<R2, R1> != is_equal);

    static_assert(std::is_base_of_v<std::bool_constant<is_less>, std::ratio_less<R1, R2>>);
    static_assert(std::ratio_less_v<R1, R2> == is_less);
    static_assert(std::is_base_of_v<std::bool_constant<is_greater>, std::ratio_less<R2, R1>>);
    static_assert(std::ratio_less_v<R2, R1> == is_greater);

    static_assert(std::is_base_of_v<std::bool_constant<is_less_equal>, std::ratio_less_equal<R1, R2>>);
    static_assert(std::ratio_less_equal_v<R1, R2> == is_less_equal);
    static_assert(std::is_base_of_v<std::bool_constant<is_greater_equal>, std::ratio_less_equal<R2, R1>>);
    static_assert(std::ratio_less_equal_v<R2, R1> == is_greater_equal);

    static_assert(std::is_base_of_v<std::bool_constant<is_greater>, std::ratio_greater<R1, R2>>);
    static_assert(std::ratio_greater_v<R1, R2> == is_greater);
    static_assert(std::is_base_of_v<std::bool_constant<is_less>, std::ratio_greater<R2, R1>>);
    static_assert(std::ratio_greater_v<R2, R1> == is_less);

    static_assert(std::is_base_of_v<std::bool_constant<is_greater_equal>, std::ratio_greater_equal<R1, R2>>);
    static_assert(std::ratio_greater_equal_v<R1, R2> == is_greater_equal);
    static_assert(std::is_base_of_v<std::bool_constant<is_less_equal>, std::ratio_greater_equal<R2, R1>>);
    static_assert(std::ratio_greater_equal_v<R2, R1> == is_less_equal);
    return true;
}

// Basic
static_assert(check_ratio_cmp<std::ratio<0, 1>, std::ratio<1, 2>, -1>());
static_assert(check_ratio_cmp<std::ratio<0, 1>, std::ratio<0, 7>, 0>());
static_assert(check_ratio_cmp<std::ratio<1, 4>, std::ratio<3, 12>, 0>());
static_assert(check_ratio_cmp<std::ratio<0, 1>, std::ratio<2, 1>, -1>());
static_assert(check_ratio_cmp<std::ratio<0, 1>, std::ratio<2, 1>, -1>());

// Close to overflow
static constexpr std::intmax_t N = (INTMAX_MAX - 1) / 2;
static_assert(check_ratio_cmp<std::ratio<N, 2 * N + 1>, std::ratio<N, 2 * N - 1>, -1>());
static_assert(check_ratio_cmp<std::ratio<2 * N + 1, N>, std::ratio<2 * N + 1, N + 1>, 1>());

// Signs
static_assert(check_ratio_cmp<std::ratio<0, 1>, std::ratio<-2, 1>, 1>());
static_assert(check_ratio_cmp<std::ratio<2, 7>, std::ratio<-2, 3>, 1>());
static_assert(check_ratio_cmp<std::ratio<-2, 7>, std::ratio<-2, 3>, 1>());
static_assert(check_ratio_cmp<std::ratio<-2, 7>, std::ratio<-4, 14>, 0>());
static_assert(check_ratio_cmp<std::ratio<2, 7>, std::ratio<-4, -14>, 0>());
static_assert(check_ratio_cmp<std::ratio<2, 3>, std::ratio<-4, -14>, 1>());
static_assert(check_ratio_cmp<std::ratio<2, -3>, std::ratio<4, -14>, -1>());
