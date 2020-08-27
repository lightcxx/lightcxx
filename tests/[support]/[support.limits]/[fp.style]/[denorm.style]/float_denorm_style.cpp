#include <limits>

#include "testing.h"

TEST() {
    constexpr auto indeterminate_1 = ::std::float_denorm_style::denorm_indeterminate;
    constexpr auto indeterminate_2 = ::std::denorm_indeterminate;
    expect_type_and_value<const ::std::float_denorm_style&>(indeterminate_1, -1);
    expect_type_and_value<const ::std::float_denorm_style&>(indeterminate_2, -1);

    constexpr auto absent_1 = ::std::float_denorm_style::denorm_absent;
    constexpr auto absent_2 = ::std::denorm_absent;
    expect_type_and_value<const ::std::float_denorm_style&>(absent_1, 0);
    expect_type_and_value<const ::std::float_denorm_style&>(absent_2, 0);

    constexpr auto present_1 = ::std::float_denorm_style::denorm_present;
    constexpr auto present_2 = ::std::denorm_present;
    expect_type_and_value<const ::std::float_denorm_style&>(present_1, 1);
    expect_type_and_value<const ::std::float_denorm_style&>(present_2, 1);
}
