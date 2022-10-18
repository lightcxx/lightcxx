#include <compare>

#include "testing.h"

struct A {
    int x;
    int y;

    auto operator<=>(const A& a) const noexcept {
        return x <=> a.x;
    }
};

struct B {
    int x;
    int y;

    std::weak_ordering operator<=>(const A& a) const {
        return x <=> a.x;
    }
};

#define expect_compare_three_way_result(type_1, type_2, result)                                       \
    static_assert(::Testing::same_type<std::compare_three_way_result<type_1, type_2>::type, result>); \
    static_assert(::Testing::same_type<std::compare_three_way_result_t<type_1, type_2>, result>)

#define expect_compare_three_way_result_single(T, result)                                \
    static_assert(::Testing::same_type<std::compare_three_way_result<T>::type, result>); \
    static_assert(::Testing::same_type<std::compare_three_way_result_t<T>, result>)

TEST(A_spaceship_A) {
    expect_compare_three_way_result_single(A, std::strong_ordering);
    expect_compare_three_way_result(A, A, std::strong_ordering);
    expect_compare_three_way_result(A, A&, std::strong_ordering);
    expect_compare_three_way_result(A, A&&, std::strong_ordering);
    expect_compare_three_way_result(A, const A, std::strong_ordering);
    expect_compare_three_way_result(A, const A&, std::strong_ordering);
    expect_compare_three_way_result(A, const A&&, std::strong_ordering);

    expect_compare_three_way_result_single(A&, std::strong_ordering);
    expect_compare_three_way_result(A&, A, std::strong_ordering);
    expect_compare_three_way_result(A&, A&, std::strong_ordering);
    expect_compare_three_way_result(A&, A&&, std::strong_ordering);
    expect_compare_three_way_result(A&, const A, std::strong_ordering);
    expect_compare_three_way_result(A&, const A&, std::strong_ordering);
    expect_compare_three_way_result(A&, const A&&, std::strong_ordering);

    expect_compare_three_way_result_single(A&&, std::strong_ordering);
    expect_compare_three_way_result(A&&, A, std::strong_ordering);
    expect_compare_three_way_result(A&&, A&, std::strong_ordering);
    expect_compare_three_way_result(A&&, A&&, std::strong_ordering);
    expect_compare_three_way_result(A&&, const A, std::strong_ordering);
    expect_compare_three_way_result(A&&, const A&, std::strong_ordering);
    expect_compare_three_way_result(A&&, const A&&, std::strong_ordering);

    expect_compare_three_way_result_single(const A, std::strong_ordering);
    expect_compare_three_way_result(const A, A, std::strong_ordering);
    expect_compare_three_way_result(const A, A&, std::strong_ordering);
    expect_compare_three_way_result(const A, A&&, std::strong_ordering);
    expect_compare_three_way_result(const A, const A, std::strong_ordering);
    expect_compare_three_way_result(const A, const A&, std::strong_ordering);
    expect_compare_three_way_result(const A, const A&&, std::strong_ordering);

    expect_compare_three_way_result_single(const A&, std::strong_ordering);
    expect_compare_three_way_result(const A&, A, std::strong_ordering);
    expect_compare_three_way_result(const A&, A&, std::strong_ordering);
    expect_compare_three_way_result(const A&, A&&, std::strong_ordering);
    expect_compare_three_way_result(const A&, const A, std::strong_ordering);
    expect_compare_three_way_result(const A&, const A&, std::strong_ordering);
    expect_compare_three_way_result(const A&, const A&&, std::strong_ordering);

    expect_compare_three_way_result_single(const A&&, std::strong_ordering);
    expect_compare_three_way_result(const A&&, A, std::strong_ordering);
    expect_compare_three_way_result(const A&&, A&, std::strong_ordering);
    expect_compare_three_way_result(const A&&, A&&, std::strong_ordering);
    expect_compare_three_way_result(const A&&, const A, std::strong_ordering);
    expect_compare_three_way_result(const A&&, const A&, std::strong_ordering);
    expect_compare_three_way_result(const A&&, const A&&, std::strong_ordering);
}

TEST(B_spaceship_A) {
    expect_compare_three_way_result(B, A, std::weak_ordering);
    expect_compare_three_way_result(B, A&, std::weak_ordering);
    expect_compare_three_way_result(B, A&&, std::weak_ordering);
    expect_compare_three_way_result(B, const A, std::weak_ordering);
    expect_compare_three_way_result(B, const A&, std::weak_ordering);
    expect_compare_three_way_result(B, const A&&, std::weak_ordering);

    expect_compare_three_way_result(B&, A, std::weak_ordering);
    expect_compare_three_way_result(B&, A&, std::weak_ordering);
    expect_compare_three_way_result(B&, A&&, std::weak_ordering);
    expect_compare_three_way_result(B&, const A, std::weak_ordering);
    expect_compare_three_way_result(B&, const A&, std::weak_ordering);
    expect_compare_three_way_result(B&, const A&&, std::weak_ordering);

    expect_compare_three_way_result(B&&, A, std::weak_ordering);
    expect_compare_three_way_result(B&&, A&, std::weak_ordering);
    expect_compare_three_way_result(B&&, A&&, std::weak_ordering);
    expect_compare_three_way_result(B&&, const A, std::weak_ordering);
    expect_compare_three_way_result(B&&, const A&, std::weak_ordering);
    expect_compare_three_way_result(B&&, const A&&, std::weak_ordering);

    expect_compare_three_way_result(const B, A, std::weak_ordering);
    expect_compare_three_way_result(const B, A&, std::weak_ordering);
    expect_compare_three_way_result(const B, A&&, std::weak_ordering);
    expect_compare_three_way_result(const B, const A, std::weak_ordering);
    expect_compare_three_way_result(const B, const A&, std::weak_ordering);
    expect_compare_three_way_result(const B, const A&&, std::weak_ordering);

    expect_compare_three_way_result(const B&, A, std::weak_ordering);
    expect_compare_three_way_result(const B&, A&, std::weak_ordering);
    expect_compare_three_way_result(const B&, A&&, std::weak_ordering);
    expect_compare_three_way_result(const B&, const A, std::weak_ordering);
    expect_compare_three_way_result(const B&, const A&, std::weak_ordering);
    expect_compare_three_way_result(const B&, const A&&, std::weak_ordering);

    expect_compare_three_way_result(const B&&, A, std::weak_ordering);
    expect_compare_three_way_result(const B&&, A&, std::weak_ordering);
    expect_compare_three_way_result(const B&&, A&&, std::weak_ordering);
    expect_compare_three_way_result(const B&&, const A, std::weak_ordering);
    expect_compare_three_way_result(const B&&, const A&, std::weak_ordering);
    expect_compare_three_way_result(const B&&, const A&&, std::weak_ordering);
}

TEST(A_spaceship_B) {
    expect_compare_three_way_result(A, B, std::weak_ordering);
    expect_compare_three_way_result(A, B&, std::weak_ordering);
    expect_compare_three_way_result(A, B&&, std::weak_ordering);
    expect_compare_three_way_result(A, const B, std::weak_ordering);
    expect_compare_three_way_result(A, const B&, std::weak_ordering);
    expect_compare_three_way_result(A, const B&&, std::weak_ordering);

    expect_compare_three_way_result(A&, B, std::weak_ordering);
    expect_compare_three_way_result(A&, B&, std::weak_ordering);
    expect_compare_three_way_result(A&, B&&, std::weak_ordering);
    expect_compare_three_way_result(A&, const B, std::weak_ordering);
    expect_compare_three_way_result(A&, const B&, std::weak_ordering);
    expect_compare_three_way_result(A&, const B&&, std::weak_ordering);

    expect_compare_three_way_result(A&&, B, std::weak_ordering);
    expect_compare_three_way_result(A&&, B&, std::weak_ordering);
    expect_compare_three_way_result(A&&, B&&, std::weak_ordering);
    expect_compare_three_way_result(A&&, const B, std::weak_ordering);
    expect_compare_three_way_result(A&&, const B&, std::weak_ordering);
    expect_compare_three_way_result(A&&, const B&&, std::weak_ordering);

    expect_compare_three_way_result(const A, B, std::weak_ordering);
    expect_compare_three_way_result(const A, B&, std::weak_ordering);
    expect_compare_three_way_result(const A, B&&, std::weak_ordering);
    expect_compare_three_way_result(const A, const B, std::weak_ordering);
    expect_compare_three_way_result(const A, const B&, std::weak_ordering);
    expect_compare_three_way_result(const A, const B&&, std::weak_ordering);

    expect_compare_three_way_result(const A&, B, std::weak_ordering);
    expect_compare_three_way_result(const A&, B&, std::weak_ordering);
    expect_compare_three_way_result(const A&, B&&, std::weak_ordering);
    expect_compare_three_way_result(const A&, const B, std::weak_ordering);
    expect_compare_three_way_result(const A&, const B&, std::weak_ordering);
    expect_compare_three_way_result(const A&, const B&&, std::weak_ordering);

    expect_compare_three_way_result(const A&&, B, std::weak_ordering);
    expect_compare_three_way_result(const A&&, B&, std::weak_ordering);
    expect_compare_three_way_result(const A&&, B&&, std::weak_ordering);
    expect_compare_three_way_result(const A&&, const B, std::weak_ordering);
    expect_compare_three_way_result(const A&&, const B&, std::weak_ordering);
    expect_compare_three_way_result(const A&&, const B&&, std::weak_ordering);
}
