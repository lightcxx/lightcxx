#include <limits>

#include "testing.h"

TEST() {
    constexpr auto indeterminate_1 = ::std::float_denorm_style::denorm_indeterminate;
    constexpr auto indeterminate_2 = ::std::denorm_indeterminate;
    expect_type_and_value(indeterminate_1, const ::std::float_denorm_style&, -1);
    expect_type_and_value(indeterminate_2, const ::std::float_denorm_style&, -1);

    constexpr auto absent_1 = ::std::float_denorm_style::denorm_absent;
    constexpr auto absent_2 = ::std::denorm_absent;
    expect_type_and_value(absent_1, const ::std::float_denorm_style&, 0);
    expect_type_and_value(absent_2, const ::std::float_denorm_style&, 0);

    constexpr auto present_1 = ::std::float_denorm_style::denorm_present;
    constexpr auto present_2 = ::std::denorm_present;
    expect_type_and_value(present_1, const ::std::float_denorm_style&, 1);
    expect_type_and_value(present_2, const ::std::float_denorm_style&, 1);
}
