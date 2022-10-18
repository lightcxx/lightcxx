#include <limits>

#include "testing.h"

TEST() {
    constexpr auto indeterminate_1 = ::std::float_denorm_style::denorm_indeterminate;
    constexpr auto indeterminate_2 = ::std::denorm_indeterminate;
    ASSERT_TYPE_AND_VALUE(indeterminate_1, const ::std::float_denorm_style&, -1);
    ASSERT_TYPE_AND_VALUE(indeterminate_2, const ::std::float_denorm_style&, -1);

    constexpr auto absent_1 = ::std::float_denorm_style::denorm_absent;
    constexpr auto absent_2 = ::std::denorm_absent;
    ASSERT_TYPE_AND_VALUE(absent_1, const ::std::float_denorm_style&, 0);
    ASSERT_TYPE_AND_VALUE(absent_2, const ::std::float_denorm_style&, 0);

    constexpr auto present_1 = ::std::float_denorm_style::denorm_present;
    constexpr auto present_2 = ::std::denorm_present;
    ASSERT_TYPE_AND_VALUE(present_1, const ::std::float_denorm_style&, 1);
    ASSERT_TYPE_AND_VALUE(present_2, const ::std::float_denorm_style&, 1);
}
