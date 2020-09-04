#include <compare>

#include "testing.h"

TEST(is_eq) {
    expect_ct_and_rt(!std::is_eq(std::partial_ordering::less));
    expect_is_noexcept(std::is_eq(std::partial_ordering::less));
    expect_ct_and_rt(std::is_eq(std::partial_ordering::equivalent));
    expect_is_noexcept(std::is_eq(std::partial_ordering::equivalent));
    expect_ct_and_rt(!std::is_eq(std::partial_ordering::greater));
    expect_is_noexcept(std::is_eq(std::partial_ordering::greater));
    expect_ct_and_rt(!std::is_eq(std::partial_ordering::unordered));
    expect_is_noexcept(std::is_eq(std::partial_ordering::unordered));
}

TEST(is_neq) {
    expect_ct_and_rt(std::is_neq(std::partial_ordering::less));
    expect_is_noexcept(std::is_neq(std::partial_ordering::less));
    expect_ct_and_rt(!std::is_neq(std::partial_ordering::equivalent));
    expect_is_noexcept(std::is_neq(std::partial_ordering::equivalent));
    expect_ct_and_rt(std::is_neq(std::partial_ordering::greater));
    expect_is_noexcept(std::is_neq(std::partial_ordering::greater));
    expect_ct_and_rt(std::is_neq(std::partial_ordering::unordered));
    expect_is_noexcept(std::is_neq(std::partial_ordering::unordered));
}

TEST(is_lt) {
    expect_ct_and_rt(std::is_lt(std::partial_ordering::less));
    expect_is_noexcept(std::is_lt(std::partial_ordering::less));
    expect_ct_and_rt(!std::is_lt(std::partial_ordering::equivalent));
    expect_is_noexcept(std::is_lt(std::partial_ordering::equivalent));
    expect_ct_and_rt(!std::is_lt(std::partial_ordering::greater));
    expect_is_noexcept(std::is_lt(std::partial_ordering::greater));
    expect_ct_and_rt(!std::is_lt(std::partial_ordering::unordered));
    expect_is_noexcept(std::is_lt(std::partial_ordering::unordered));
}

TEST(is_lteq) {
    expect_ct_and_rt(std::is_lteq(std::partial_ordering::less));
    expect_is_noexcept(std::is_lteq(std::partial_ordering::less));
    expect_ct_and_rt(std::is_lteq(std::partial_ordering::equivalent));
    expect_is_noexcept(std::is_lteq(std::partial_ordering::equivalent));
    expect_ct_and_rt(!std::is_lteq(std::partial_ordering::greater));
    expect_is_noexcept(std::is_lteq(std::partial_ordering::greater));
    expect_ct_and_rt(!std::is_lteq(std::partial_ordering::unordered));
    expect_is_noexcept(std::is_lteq(std::partial_ordering::unordered));
}

TEST(is_gt) {
    expect_ct_and_rt(!std::is_gt(std::partial_ordering::less));
    expect_is_noexcept(std::is_gt(std::partial_ordering::less));
    expect_ct_and_rt(!std::is_gt(std::partial_ordering::equivalent));
    expect_is_noexcept(std::is_gt(std::partial_ordering::equivalent));
    expect_ct_and_rt(std::is_gt(std::partial_ordering::greater));
    expect_is_noexcept(std::is_gt(std::partial_ordering::greater));
    expect_ct_and_rt(!std::is_gt(std::partial_ordering::unordered));
    expect_is_noexcept(std::is_gt(std::partial_ordering::unordered));
}

TEST(is_gteq) {
    expect_ct_and_rt(!std::is_gteq(std::partial_ordering::less));
    expect_is_noexcept(std::is_gteq(std::partial_ordering::less));
    expect_ct_and_rt(std::is_gteq(std::partial_ordering::equivalent));
    expect_is_noexcept(std::is_gteq(std::partial_ordering::equivalent));
    expect_ct_and_rt(std::is_gteq(std::partial_ordering::greater));
    expect_is_noexcept(std::is_gteq(std::partial_ordering::greater));
    expect_ct_and_rt(!std::is_gteq(std::partial_ordering::unordered));
    expect_is_noexcept(std::is_gteq(std::partial_ordering::unordered));
}
