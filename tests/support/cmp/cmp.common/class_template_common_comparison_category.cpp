#include <compare>

#include "testing.h"

using P = std::partial_ordering;
using W = std::weak_ordering;
using S = std::strong_ordering;

#define expect_common_comparison_category(expected, ...)                                    \
    static_assert(::Testing::same_type<expected, std::common_comparison_category<__VA_ARGS__>::type>); \
    static_assert(::Testing::same_type<expected, std::common_comparison_category_t<__VA_ARGS__>>)

TEST(empty_type_list) {
    expect_common_comparison_category(S, );
}

TEST(type_list_with_single_type) {
    expect_common_comparison_category(S, S);
    expect_common_comparison_category(W, W);
    expect_common_comparison_category(P, P);
}

TEST(type_list_with_two_types) {
    expect_common_comparison_category(P, P, P);
    expect_common_comparison_category(P, P, W);
    expect_common_comparison_category(P, P, S);

    expect_common_comparison_category(P, W, P);
    expect_common_comparison_category(W, W, W);
    expect_common_comparison_category(W, W, S);

    expect_common_comparison_category(P, S, P);
    expect_common_comparison_category(W, S, W);
    expect_common_comparison_category(S, S, S);
}

TEST(type_list_with_three_types) {
    expect_common_comparison_category(P, P, P, P);
    expect_common_comparison_category(P, P, P, W);
    expect_common_comparison_category(P, P, P, S);
    expect_common_comparison_category(P, P, W, P);
    expect_common_comparison_category(P, P, W, W);
    expect_common_comparison_category(P, P, W, S);
    expect_common_comparison_category(P, P, S, P);
    expect_common_comparison_category(P, P, S, W);
    expect_common_comparison_category(P, P, S, S);

    expect_common_comparison_category(P, W, P, P);
    expect_common_comparison_category(P, W, P, W);
    expect_common_comparison_category(P, W, P, S);
    expect_common_comparison_category(P, W, W, P);
    expect_common_comparison_category(W, W, W, W);
    expect_common_comparison_category(W, W, W, S);
    expect_common_comparison_category(P, W, S, P);
    expect_common_comparison_category(W, W, S, W);
    expect_common_comparison_category(W, W, S, S);

    expect_common_comparison_category(P, S, P, P);
    expect_common_comparison_category(P, S, P, W);
    expect_common_comparison_category(P, S, P, S);
    expect_common_comparison_category(P, S, W, P);
    expect_common_comparison_category(W, S, W, W);
    expect_common_comparison_category(W, S, W, S);
    expect_common_comparison_category(P, S, S, P);
    expect_common_comparison_category(W, S, S, W);
    expect_common_comparison_category(S, S, S, S);
}

TEST(type_list_with_four_types) {
    expect_common_comparison_category(P, P, P, P, P);
    expect_common_comparison_category(P, P, P, P, W);
    expect_common_comparison_category(P, P, P, P, S);
    expect_common_comparison_category(P, P, P, W, P);
    expect_common_comparison_category(P, P, P, W, W);
    expect_common_comparison_category(P, P, P, W, S);
    expect_common_comparison_category(P, P, P, S, P);
    expect_common_comparison_category(P, P, P, S, W);
    expect_common_comparison_category(P, P, P, S, S);
    expect_common_comparison_category(P, P, W, P, P);
    expect_common_comparison_category(P, P, W, P, W);
    expect_common_comparison_category(P, P, W, P, S);
    expect_common_comparison_category(P, P, W, W, P);
    expect_common_comparison_category(P, P, W, W, W);
    expect_common_comparison_category(P, P, W, W, S);
    expect_common_comparison_category(P, P, W, S, P);
    expect_common_comparison_category(P, P, W, S, W);
    expect_common_comparison_category(P, P, W, S, S);
    expect_common_comparison_category(P, P, S, P, P);
    expect_common_comparison_category(P, P, S, P, W);
    expect_common_comparison_category(P, P, S, P, S);
    expect_common_comparison_category(P, P, S, W, P);
    expect_common_comparison_category(P, P, S, W, W);
    expect_common_comparison_category(P, P, S, W, S);
    expect_common_comparison_category(P, P, S, S, P);
    expect_common_comparison_category(P, P, S, S, W);
    expect_common_comparison_category(P, P, S, S, S);

    expect_common_comparison_category(P, W, P, P, P);
    expect_common_comparison_category(P, W, P, P, W);
    expect_common_comparison_category(P, W, P, P, S);
    expect_common_comparison_category(P, W, P, W, P);
    expect_common_comparison_category(P, W, P, W, W);
    expect_common_comparison_category(P, W, P, W, S);
    expect_common_comparison_category(P, W, P, S, P);
    expect_common_comparison_category(P, W, P, S, W);
    expect_common_comparison_category(P, W, P, S, S);
    expect_common_comparison_category(P, W, W, P, P);
    expect_common_comparison_category(P, W, W, P, W);
    expect_common_comparison_category(P, W, W, P, S);
    expect_common_comparison_category(P, W, W, W, P);
    expect_common_comparison_category(W, W, W, W, W);
    expect_common_comparison_category(W, W, W, W, S);
    expect_common_comparison_category(P, W, W, S, P);
    expect_common_comparison_category(W, W, W, S, W);
    expect_common_comparison_category(W, W, W, S, S);
    expect_common_comparison_category(P, W, S, P, P);
    expect_common_comparison_category(P, W, S, P, W);
    expect_common_comparison_category(P, W, S, P, S);
    expect_common_comparison_category(P, W, S, W, P);
    expect_common_comparison_category(W, W, S, W, W);
    expect_common_comparison_category(W, W, S, W, S);
    expect_common_comparison_category(P, W, S, S, P);
    expect_common_comparison_category(W, W, S, S, W);
    expect_common_comparison_category(W, W, S, S, S);

    expect_common_comparison_category(P, S, P, P, P);
    expect_common_comparison_category(P, S, P, P, W);
    expect_common_comparison_category(P, S, P, P, S);
    expect_common_comparison_category(P, S, P, W, P);
    expect_common_comparison_category(P, S, P, W, W);
    expect_common_comparison_category(P, S, P, W, S);
    expect_common_comparison_category(P, S, P, S, P);
    expect_common_comparison_category(P, S, P, S, W);
    expect_common_comparison_category(P, S, P, S, S);
    expect_common_comparison_category(P, S, W, P, P);
    expect_common_comparison_category(P, S, W, P, W);
    expect_common_comparison_category(P, S, W, P, S);
    expect_common_comparison_category(P, S, W, W, P);
    expect_common_comparison_category(W, S, W, W, W);
    expect_common_comparison_category(W, S, W, W, S);
    expect_common_comparison_category(P, S, W, S, P);
    expect_common_comparison_category(W, S, W, S, W);
    expect_common_comparison_category(W, S, W, S, S);
    expect_common_comparison_category(P, S, S, P, P);
    expect_common_comparison_category(P, S, S, P, W);
    expect_common_comparison_category(P, S, S, P, S);
    expect_common_comparison_category(P, S, S, W, P);
    expect_common_comparison_category(W, S, S, W, W);
    expect_common_comparison_category(W, S, S, W, S);
    expect_common_comparison_category(P, S, S, S, P);
    expect_common_comparison_category(W, S, S, S, W);
    expect_common_comparison_category(S, S, S, S, S);
}

TEST(void) {
    expect_common_comparison_category(void, void);
    expect_common_comparison_category(void, int);
    expect_common_comparison_category(void, S, W, S, W, int, W);
    expect_common_comparison_category(void, P&);
    expect_common_comparison_category(void, const P);
    expect_common_comparison_category(void, const P&);
    expect_common_comparison_category(void, S&);
    expect_common_comparison_category(void, const S);
    expect_common_comparison_category(void, const S&);
    expect_common_comparison_category(void, W&);
    expect_common_comparison_category(void, const W);
    expect_common_comparison_category(void, const W&);
    expect_common_comparison_category(void, W, const W);
    expect_common_comparison_category(void, W, const W, S);
}
