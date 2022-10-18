#include <compare>

#include "testing.h"

TEST(is_eq) {
    ASSERT_CT_RT(!std::is_eq(std::partial_ordering::less));
    ASSERT_NOEXCEPT(std::is_eq(std::partial_ordering::less));
    ASSERT_CT_RT(std::is_eq(std::partial_ordering::equivalent));
    ASSERT_NOEXCEPT(std::is_eq(std::partial_ordering::equivalent));
    ASSERT_CT_RT(!std::is_eq(std::partial_ordering::greater));
    ASSERT_NOEXCEPT(std::is_eq(std::partial_ordering::greater));
    ASSERT_CT_RT(!std::is_eq(std::partial_ordering::unordered));
    ASSERT_NOEXCEPT(std::is_eq(std::partial_ordering::unordered));
}

TEST(is_neq) {
    ASSERT_CT_RT(std::is_neq(std::partial_ordering::less));
    ASSERT_NOEXCEPT(std::is_neq(std::partial_ordering::less));
    ASSERT_CT_RT(!std::is_neq(std::partial_ordering::equivalent));
    ASSERT_NOEXCEPT(std::is_neq(std::partial_ordering::equivalent));
    ASSERT_CT_RT(std::is_neq(std::partial_ordering::greater));
    ASSERT_NOEXCEPT(std::is_neq(std::partial_ordering::greater));
    ASSERT_CT_RT(std::is_neq(std::partial_ordering::unordered));
    ASSERT_NOEXCEPT(std::is_neq(std::partial_ordering::unordered));
}

TEST(is_lt) {
    ASSERT_CT_RT(std::is_lt(std::partial_ordering::less));
    ASSERT_NOEXCEPT(std::is_lt(std::partial_ordering::less));
    ASSERT_CT_RT(!std::is_lt(std::partial_ordering::equivalent));
    ASSERT_NOEXCEPT(std::is_lt(std::partial_ordering::equivalent));
    ASSERT_CT_RT(!std::is_lt(std::partial_ordering::greater));
    ASSERT_NOEXCEPT(std::is_lt(std::partial_ordering::greater));
    ASSERT_CT_RT(!std::is_lt(std::partial_ordering::unordered));
    ASSERT_NOEXCEPT(std::is_lt(std::partial_ordering::unordered));
}

TEST(is_lteq) {
    ASSERT_CT_RT(std::is_lteq(std::partial_ordering::less));
    ASSERT_NOEXCEPT(std::is_lteq(std::partial_ordering::less));
    ASSERT_CT_RT(std::is_lteq(std::partial_ordering::equivalent));
    ASSERT_NOEXCEPT(std::is_lteq(std::partial_ordering::equivalent));
    ASSERT_CT_RT(!std::is_lteq(std::partial_ordering::greater));
    ASSERT_NOEXCEPT(std::is_lteq(std::partial_ordering::greater));
    ASSERT_CT_RT(!std::is_lteq(std::partial_ordering::unordered));
    ASSERT_NOEXCEPT(std::is_lteq(std::partial_ordering::unordered));
}

TEST(is_gt) {
    ASSERT_CT_RT(!std::is_gt(std::partial_ordering::less));
    ASSERT_NOEXCEPT(std::is_gt(std::partial_ordering::less));
    ASSERT_CT_RT(!std::is_gt(std::partial_ordering::equivalent));
    ASSERT_NOEXCEPT(std::is_gt(std::partial_ordering::equivalent));
    ASSERT_CT_RT(std::is_gt(std::partial_ordering::greater));
    ASSERT_NOEXCEPT(std::is_gt(std::partial_ordering::greater));
    ASSERT_CT_RT(!std::is_gt(std::partial_ordering::unordered));
    ASSERT_NOEXCEPT(std::is_gt(std::partial_ordering::unordered));
}

TEST(is_gteq) {
    ASSERT_CT_RT(!std::is_gteq(std::partial_ordering::less));
    ASSERT_NOEXCEPT(std::is_gteq(std::partial_ordering::less));
    ASSERT_CT_RT(std::is_gteq(std::partial_ordering::equivalent));
    ASSERT_NOEXCEPT(std::is_gteq(std::partial_ordering::equivalent));
    ASSERT_CT_RT(std::is_gteq(std::partial_ordering::greater));
    ASSERT_NOEXCEPT(std::is_gteq(std::partial_ordering::greater));
    ASSERT_CT_RT(!std::is_gteq(std::partial_ordering::unordered));
    ASSERT_NOEXCEPT(std::is_gteq(std::partial_ordering::unordered));
}
