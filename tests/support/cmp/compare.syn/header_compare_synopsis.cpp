#include <compare>

#include "testing.h"

TEST() {
    (void)std::partial_ordering::less;
    (void)std::partial_ordering::equivalent;
    (void)std::partial_ordering::greater;
    (void)std::partial_ordering::unordered;
    (void)std::weak_ordering::less;
    (void)std::weak_ordering::equivalent;
    (void)std::weak_ordering::greater;
    (void)std::strong_ordering::less;
    (void)std::strong_ordering::equal;
    (void)std::strong_ordering::equivalent;
    (void)std::strong_ordering::greater;
    ASSERT(is_eq(std::strong_ordering::equivalent));
    ASSERT(is_neq(std::partial_ordering::greater));
    ASSERT(is_lt(std::weak_ordering::less));
    ASSERT(is_lteq(std::strong_ordering::equal));
    ASSERT(is_gt(std::partial_ordering::greater));
    ASSERT(is_gteq(std::partial_ordering::equivalent));
    static_assert(same_type<std::partial_ordering, std::common_comparison_category<std::weak_ordering, std::partial_ordering>::type>);
    static_assert(same_type<std::weak_ordering, std::common_comparison_category_t<std::weak_ordering, std::strong_ordering>>);

    // TODO: Test that [cmp.concept] is available once implemented.

    static_assert(same_type<std::compare_three_way_result<float>::type, std::partial_ordering>);
    static_assert(same_type<std::compare_three_way_result<long, long>::type, std::strong_ordering>);
    static_assert(same_type<std::compare_three_way_result_t<void*>, std::strong_ordering>);
    static_assert(same_type<std::compare_three_way_result_t<int, int>, std::strong_ordering>);

    // TODO: Test that [comparisons.three.way] is available once implemented.

    // TODO: Test that [cmp.alg] is available once implemented.
}
