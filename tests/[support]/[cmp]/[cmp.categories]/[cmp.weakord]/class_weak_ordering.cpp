#include <compare>

#include "testing.h"

constexpr bool implicit_conversion_to_partial_ordering(std::partial_ordering) noexcept {
    return true;
}

TEST(less) {
    expect_type(const std::weak_ordering&, std::weak_ordering::less);
    expect_ct_and_rt(implicit_conversion_to_partial_ordering(std::weak_ordering::less));
    expect_ct_and_rt(std::weak_ordering::less == std::partial_ordering::less);
    expect_ct_and_rt((std::partial_ordering)std::weak_ordering::less
                     == std::partial_ordering::less);
    expect_is_noexcept((std::partial_ordering)std::weak_ordering::less);
    expect_ct_and_rt(std::weak_ordering::less == std::weak_ordering::less);
    expect_is_noexcept(std::weak_ordering::less == std::weak_ordering::less);
    expect_ct_and_rt(!(std::weak_ordering::less == std::weak_ordering::equivalent));
    expect_is_noexcept(std::weak_ordering::less == std::weak_ordering::equivalent);
    expect_ct_and_rt(!(std::weak_ordering::less == std::weak_ordering::greater));
    expect_is_noexcept(std::weak_ordering::less == std::weak_ordering::greater);
    expect_ct_and_rt(!(std::weak_ordering::less != std::weak_ordering::less));
    expect_is_noexcept(std::weak_ordering::less != std::weak_ordering::less);
    expect_ct_and_rt(std::weak_ordering::less != std::weak_ordering::equivalent);
    expect_is_noexcept(std::weak_ordering::less != std::weak_ordering::equivalent);
    expect_ct_and_rt(std::weak_ordering::less != std::weak_ordering::greater);
    expect_is_noexcept(std::weak_ordering::less != std::weak_ordering::greater);
    expect_ct_and_rt(!(std::weak_ordering::equivalent == std::weak_ordering::less));
    expect_is_noexcept(std::weak_ordering::equivalent == std::weak_ordering::less);
    expect_ct_and_rt(!(std::weak_ordering::greater == std::weak_ordering::less));
    expect_is_noexcept(std::weak_ordering::greater == std::weak_ordering::less);
    expect_ct_and_rt(std::weak_ordering::equivalent != std::weak_ordering::less);
    expect_is_noexcept(std::weak_ordering::equivalent != std::weak_ordering::less);
    expect_ct_and_rt(std::weak_ordering::greater != std::weak_ordering::less);
    expect_is_noexcept(std::weak_ordering::greater != std::weak_ordering::less);
    expect_ct_and_rt(!(std::weak_ordering::less == 0));
    expect_is_noexcept(std::weak_ordering::less == 0);
    expect_ct_and_rt(std::weak_ordering::less != 0);
    expect_is_noexcept(std::weak_ordering::less != 0);
    expect_ct_and_rt(std::weak_ordering::less < 0);
    expect_is_noexcept(std::weak_ordering::less < 0);
    expect_ct_and_rt(!(std::weak_ordering::less > 0));
    expect_is_noexcept(std::weak_ordering::less > 0);
    expect_ct_and_rt(std::weak_ordering::less <= 0);
    expect_is_noexcept(std::weak_ordering::less <= 0);
    expect_ct_and_rt(!(std::weak_ordering::less >= 0));
    expect_is_noexcept(std::weak_ordering::less >= 0);
    expect_ct_and_rt(!(0 == std::weak_ordering::less));
    expect_is_noexcept(0 == std::weak_ordering::less);
    expect_ct_and_rt(0 != std::weak_ordering::less);
    expect_is_noexcept(0 != std::weak_ordering::less);
    expect_ct_and_rt(!(0 < std::weak_ordering::less));
    expect_is_noexcept(0 < std::weak_ordering::less);
    expect_ct_and_rt(0 > std::weak_ordering::less);
    expect_is_noexcept(0 > std::weak_ordering::less);
    expect_ct_and_rt(!(0 <= std::weak_ordering::less));
    expect_is_noexcept(0 <= std::weak_ordering::less);
    expect_ct_and_rt(0 >= std::weak_ordering::less);
    expect_is_noexcept(0 >= std::weak_ordering::less);
    expect_ct_and_rt((std::weak_ordering::less <=> 0) == std::weak_ordering::less);
    expect_is_noexcept(std::weak_ordering::less <=> 0);
    expect_ct_and_rt((0 <=> std::weak_ordering::less) == std::weak_ordering::greater);
    expect_is_noexcept(0 <=> std::weak_ordering::less);
}

TEST(equivalent) {
    expect_type(const std::weak_ordering&, std::weak_ordering::equivalent);
    expect_ct_and_rt(implicit_conversion_to_partial_ordering(std::weak_ordering::equivalent));
    expect_ct_and_rt(std::weak_ordering::equivalent == std::partial_ordering::equivalent);
    expect_ct_and_rt((std::partial_ordering)std::weak_ordering::equivalent
                     == std::partial_ordering::equivalent);
    expect_is_noexcept((std::partial_ordering)std::weak_ordering::equivalent);
    expect_ct_and_rt(!(std::weak_ordering::equivalent == std::weak_ordering::less));
    expect_is_noexcept(std::weak_ordering::equivalent == std::weak_ordering::less);
    expect_ct_and_rt(std::weak_ordering::equivalent == std::weak_ordering::equivalent);
    expect_is_noexcept(std::weak_ordering::equivalent == std::weak_ordering::equivalent);
    expect_ct_and_rt(!(std::weak_ordering::equivalent == std::weak_ordering::greater));
    expect_is_noexcept(std::weak_ordering::equivalent == std::weak_ordering::greater);
    expect_ct_and_rt(std::weak_ordering::equivalent != std::weak_ordering::less);
    expect_is_noexcept(std::weak_ordering::equivalent != std::weak_ordering::less);
    expect_ct_and_rt(!(std::weak_ordering::equivalent != std::weak_ordering::equivalent));
    expect_is_noexcept(std::weak_ordering::equivalent != std::weak_ordering::equivalent);
    expect_ct_and_rt(std::weak_ordering::equivalent != std::weak_ordering::greater);
    expect_is_noexcept(std::weak_ordering::equivalent != std::weak_ordering::greater);
    expect_ct_and_rt(!(std::weak_ordering::less == std::weak_ordering::equivalent));
    expect_is_noexcept(std::weak_ordering::less == std::weak_ordering::equivalent);
    expect_ct_and_rt(!(std::weak_ordering::greater == std::weak_ordering::equivalent));
    expect_is_noexcept(std::weak_ordering::greater == std::weak_ordering::equivalent);
    expect_ct_and_rt(std::weak_ordering::less != std::weak_ordering::equivalent);
    expect_is_noexcept(std::weak_ordering::less != std::weak_ordering::equivalent);
    expect_ct_and_rt(std::weak_ordering::greater != std::weak_ordering::equivalent);
    expect_is_noexcept(std::weak_ordering::greater != std::weak_ordering::equivalent);
    expect_ct_and_rt(std::weak_ordering::equivalent == 0);
    expect_is_noexcept(std::weak_ordering::equivalent == 0);
    expect_ct_and_rt(!(std::weak_ordering::equivalent != 0));
    expect_is_noexcept(std::weak_ordering::equivalent != 0);
    expect_ct_and_rt(!(std::weak_ordering::equivalent < 0));
    expect_is_noexcept(std::weak_ordering::equivalent < 0);
    expect_ct_and_rt(!(std::weak_ordering::equivalent > 0));
    expect_is_noexcept(std::weak_ordering::equivalent > 0);
    expect_ct_and_rt(std::weak_ordering::equivalent <= 0);
    expect_is_noexcept(std::weak_ordering::equivalent <= 0);
    expect_ct_and_rt(std::weak_ordering::equivalent >= 0);
    expect_is_noexcept(std::weak_ordering::equivalent >= 0);
    expect_ct_and_rt(0 == std::weak_ordering::equivalent);
    expect_is_noexcept(0 == std::weak_ordering::equivalent);
    expect_ct_and_rt(!(0 != std::weak_ordering::equivalent));
    expect_is_noexcept(0 != std::weak_ordering::equivalent);
    expect_ct_and_rt(!(0 < std::weak_ordering::equivalent));
    expect_is_noexcept(0 < std::weak_ordering::equivalent);
    expect_ct_and_rt(!(0 > std::weak_ordering::equivalent));
    expect_is_noexcept(0 > std::weak_ordering::equivalent);
    expect_ct_and_rt(0 <= std::weak_ordering::equivalent);
    expect_is_noexcept(0 <= std::weak_ordering::equivalent);
    expect_ct_and_rt(0 >= std::weak_ordering::equivalent);
    expect_is_noexcept(0 >= std::weak_ordering::equivalent);
    expect_ct_and_rt((std::weak_ordering::equivalent <=> 0) == std::weak_ordering::equivalent);
    expect_is_noexcept(std::weak_ordering::equivalent <=> 0);
    expect_ct_and_rt((0 <=> std::weak_ordering::equivalent) == std::weak_ordering::equivalent);
    expect_is_noexcept(0 <=> std::weak_ordering::equivalent);
}

TEST(greater) {
    expect_type(const std::weak_ordering&, std::weak_ordering::greater);
    expect_ct_and_rt(implicit_conversion_to_partial_ordering(std::weak_ordering::greater));
    expect_ct_and_rt(std::weak_ordering::greater == std::partial_ordering::greater);
    expect_ct_and_rt((std::partial_ordering)std::weak_ordering::greater
                     == std::partial_ordering::greater);
    expect_is_noexcept((std::partial_ordering)std::weak_ordering::greater);
    expect_ct_and_rt(!(std::weak_ordering::greater == std::weak_ordering::less));
    expect_is_noexcept(std::weak_ordering::greater == std::weak_ordering::less);
    expect_ct_and_rt(!(std::weak_ordering::greater == std::weak_ordering::equivalent));
    expect_is_noexcept(std::weak_ordering::greater == std::weak_ordering::equivalent);
    expect_ct_and_rt(std::weak_ordering::greater == std::weak_ordering::greater);
    expect_is_noexcept(std::weak_ordering::greater == std::weak_ordering::greater);
    expect_ct_and_rt(std::weak_ordering::greater != std::weak_ordering::less);
    expect_is_noexcept(std::weak_ordering::greater != std::weak_ordering::less);
    expect_ct_and_rt(std::weak_ordering::greater != std::weak_ordering::equivalent);
    expect_is_noexcept(std::weak_ordering::greater != std::weak_ordering::equivalent);
    expect_ct_and_rt(!(std::weak_ordering::greater != std::weak_ordering::greater));
    expect_is_noexcept(std::weak_ordering::greater != std::weak_ordering::greater);
    expect_ct_and_rt(!(std::weak_ordering::less == std::weak_ordering::greater));
    expect_is_noexcept(std::weak_ordering::less == std::weak_ordering::greater);
    expect_ct_and_rt(!(std::weak_ordering::equivalent == std::weak_ordering::greater));
    expect_is_noexcept(std::weak_ordering::equivalent == std::weak_ordering::greater);
    expect_ct_and_rt(std::weak_ordering::less != std::weak_ordering::greater);
    expect_is_noexcept(std::weak_ordering::less != std::weak_ordering::greater);
    expect_ct_and_rt(std::weak_ordering::equivalent != std::weak_ordering::greater);
    expect_is_noexcept(std::weak_ordering::equivalent != std::weak_ordering::greater);
    expect_ct_and_rt(!(std::weak_ordering::greater == 0));
    expect_is_noexcept(std::weak_ordering::greater == 0);
    expect_ct_and_rt(std::weak_ordering::greater != 0);
    expect_is_noexcept(std::weak_ordering::greater != 0);
    expect_ct_and_rt(!(std::weak_ordering::greater < 0));
    expect_is_noexcept(std::weak_ordering::greater < 0);
    expect_ct_and_rt(std::weak_ordering::greater > 0);
    expect_is_noexcept(std::weak_ordering::greater > 0);
    expect_ct_and_rt(!(std::weak_ordering::greater <= 0));
    expect_is_noexcept(std::weak_ordering::greater <= 0);
    expect_ct_and_rt(std::weak_ordering::greater >= 0);
    expect_is_noexcept(std::weak_ordering::greater >= 0);
    expect_ct_and_rt(!(0 == std::weak_ordering::greater));
    expect_is_noexcept(0 == std::weak_ordering::greater);
    expect_ct_and_rt(0 != std::weak_ordering::greater);
    expect_is_noexcept(0 != std::weak_ordering::greater);
    expect_ct_and_rt(0 < std::weak_ordering::greater);
    expect_is_noexcept(0 < std::weak_ordering::greater);
    expect_ct_and_rt(!(0 > std::weak_ordering::greater));
    expect_is_noexcept(0 > std::weak_ordering::greater);
    expect_ct_and_rt(0 <= std::weak_ordering::greater);
    expect_is_noexcept(0 <= std::weak_ordering::greater);
    expect_ct_and_rt(!(0 >= std::weak_ordering::greater));
    expect_is_noexcept(0 >= std::weak_ordering::greater);
    expect_ct_and_rt((std::weak_ordering::greater <=> 0) == std::weak_ordering::greater);
    expect_is_noexcept(std::weak_ordering::greater <=> 0);
    expect_ct_and_rt((0 <=> std::weak_ordering::greater) == std::weak_ordering::less);
    expect_is_noexcept(0 <=> std::weak_ordering::greater);
}
