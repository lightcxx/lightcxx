#include <limits>

#include "testing.h"

TEST() {
    constexpr auto indeterminate_1 = ::std::float_round_style::round_indeterminate;
    constexpr auto indeterminate_2 = ::std::round_indeterminate;
    expect_type_and_value<const ::std::float_round_style&>(indeterminate_1, -1);
    expect_type_and_value<const ::std::float_round_style&>(indeterminate_2, -1);

    constexpr auto to_zero_1 = ::std::float_round_style::round_toward_zero;
    constexpr auto to_zero_2 = ::std::round_toward_zero;
    expect_type_and_value<const ::std::float_round_style&>(to_zero_1, 0);
    expect_type_and_value<const ::std::float_round_style&>(to_zero_2, 0);

    constexpr auto to_nearest_1 = ::std::float_round_style::round_to_nearest;
    constexpr auto to_nearest_2 = ::std::round_to_nearest;
    expect_type_and_value<const ::std::float_round_style&>(to_nearest_1, 1);
    expect_type_and_value<const ::std::float_round_style&>(to_nearest_2, 1);

    constexpr auto to_infinity_1 = ::std::float_round_style::round_toward_infinity;
    constexpr auto to_infinity_2 = ::std::round_toward_infinity;
    expect_type_and_value<const ::std::float_round_style&>(to_infinity_1, 2);
    expect_type_and_value<const ::std::float_round_style&>(to_infinity_2, 2);

    constexpr auto to_neg_infinity_1 = ::std::float_round_style::round_toward_neg_infinity;
    constexpr auto to_neg_infinity_2 = ::std::round_toward_neg_infinity;
    expect_type_and_value<const ::std::float_round_style&>(to_neg_infinity_1, 3);
    expect_type_and_value<const ::std::float_round_style&>(to_neg_infinity_2, 3);
}
