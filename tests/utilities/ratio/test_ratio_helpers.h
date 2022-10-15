#ifndef TESTS_UTILITIES_RATIO_RATIO_RATIO_CHECK_RATIO_H
#define TESTS_UTILITIES_RATIO_RATIO_RATIO_CHECK_RATIO_H

#include <ratio>

template<class R>
inline constexpr bool is_ratio = false;

template<std::intmax_t N, std::intmax_t D>
inline constexpr bool is_ratio<std::ratio<N, D>> = true;

template<class R, std::intmax_t A, std::intmax_t B>
constexpr bool check_ratio() {
    static_assert(is_ratio<R>);
    static_assert(R::num == A);
    static_assert(R::den == B);
    static_assert(std::is_same_v<typename R::type, std::ratio<A, B>>);
    return true;
}

template<class R, bool get_num>
inline constexpr std::intmax_t ratio_template_param = INTMAX_MIN;

template<std::intmax_t A, std::intmax_t B, bool get_num>
inline constexpr std::intmax_t ratio_template_param<std::ratio<A, B>, get_num> = (get_num ? A : B);

template<class R, std::intmax_t A, std::intmax_t B>
constexpr bool check_ratio_strict() {
    static_assert(ratio_template_param<R, true> == A);
    static_assert(ratio_template_param<R, false> == B);
    return check_ratio<R, A, B>();
}

#endif
