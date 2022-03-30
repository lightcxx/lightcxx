#include <utility>

#include "testing.h"

TEST(ints) {
    int a = 3;
    int b = 5;
    expect_is_noexcept(std::swap(a, b));

    std::swap(a, b);
    expect(a == 5);
    expect(b == 3);

    int arr_a[3] = {1, 2, 3};
    int arr_b[3] = {4, 5, 6};
    expect_is_noexcept(std::swap(arr_a, arr_b));

    std::swap(arr_a, arr_b);
    expect(arr_a[0] == 4 && arr_a[1] == 5 && arr_a[2] == 6);
    expect(arr_b[0] == 1 && arr_b[1] == 2 && arr_b[2] == 3);
}

struct Trivial {
    int x;
    int y;
};

TEST(Trivial) {
    Trivial a{1, 2};
    Trivial b{3, 4};
    expect_is_noexcept(std::swap(a, b));

    std::swap(a, b);
    expect(a.x == 3 && a.y == 4);
    expect(b.x == 1 && b.y == 2);

    Trivial arr_a[3] = {{1, 2}, {3, 4}, {5, 6}};
    Trivial arr_b[3] = {{7, 8}, {9, 10}, {11, 12}};
    expect_is_noexcept(std::swap(arr_a, arr_b));

    std::swap(arr_a, arr_b);
    expect(arr_a[0].x == 7 && arr_a[0].y == 8 && arr_a[1].x == 9 && arr_a[1].y == 10
           && arr_a[2].x == 11 && arr_a[2].y == 12);
    expect(arr_b[0].x == 1 && arr_b[0].y == 2 && arr_b[1].x == 3 && arr_b[1].y == 4
           && arr_b[2].x == 5 && arr_b[2].y == 6);
}

struct NonTrivialNoexcept {
    static inline int num_move_ops = 0;

    int x;
    int y;

    NonTrivialNoexcept(int x, int y): x(x), y(y) {}
    NonTrivialNoexcept(NonTrivialNoexcept&& other) noexcept: x(other.x), y(other.y) {
        num_move_ops += 1;
    }
    NonTrivialNoexcept& operator=(NonTrivialNoexcept&& other) noexcept {
        x = other.x;
        y = other.y;
        num_move_ops += 1;
        return *this;
    }
};

TEST(NonTrivialNoexcept) {
    NonTrivialNoexcept::num_move_ops = 0;

    NonTrivialNoexcept a{1, 2};
    NonTrivialNoexcept b{3, 4};
    expect_is_noexcept(std::swap(a, b));

    std::swap(a, b);
    expect(a.x == 3 && a.y == 4);
    expect(b.x == 1 && b.y == 2);
    expect(NonTrivialNoexcept::num_move_ops == 3);

    NonTrivialNoexcept::num_move_ops = 0;
    NonTrivialNoexcept arr_a[3] = {{1, 2}, {3, 4}, {5, 6}};
    NonTrivialNoexcept arr_b[3] = {{7, 8}, {9, 10}, {11, 12}};
    expect_is_noexcept(std::swap(arr_a, arr_b));

    std::swap(arr_a, arr_b);
    expect(arr_a[0].x == 7 && arr_a[0].y == 8 && arr_a[1].x == 9 && arr_a[1].y == 10
           && arr_a[2].x == 11 && arr_a[2].y == 12);
    expect(arr_b[0].x == 1 && arr_b[0].y == 2 && arr_b[1].x == 3 && arr_b[1].y == 4
           && arr_b[2].x == 5 && arr_b[2].y == 6);
    expect(NonTrivialNoexcept::num_move_ops == 3 * 3);
}

struct NonTrivialThrowMoveCtor {
    NonTrivialThrowMoveCtor() = default;
    NonTrivialThrowMoveCtor(NonTrivialThrowMoveCtor&&);
    NonTrivialThrowMoveCtor& operator=(NonTrivialThrowMoveCtor&&) noexcept;
};

struct NonTrivialThrowMoveAssign {
    NonTrivialThrowMoveAssign() = default;
    NonTrivialThrowMoveAssign(NonTrivialThrowMoveAssign&&) noexcept;
    NonTrivialThrowMoveAssign& operator=(NonTrivialThrowMoveAssign&&);
};

struct NonTrivialThrowMoveOps {
    NonTrivialThrowMoveOps() = default;
    NonTrivialThrowMoveOps(NonTrivialThrowMoveOps&&);
    NonTrivialThrowMoveOps& operator=(NonTrivialThrowMoveOps&&);
};

TEST(NonTrivialThrowMoveCtor_NonTrivialThrowMoveAssign_NonTrivialThrowMoveOps) {
    NonTrivialThrowMoveCtor a, b, arr_a[3], arr_b[3];
    expect_is_not_noexcept(std::swap(a, b));
    expect_is_not_noexcept(std::swap(arr_a, arr_b));

    NonTrivialThrowMoveAssign c, d, arr_c[3], arr_d[3];
    expect_is_not_noexcept(std::swap(c, d));
    expect_is_not_noexcept(std::swap(arr_c, arr_d));

    NonTrivialThrowMoveOps e, f, arr_e[3], arr_f[3];
    expect_is_not_noexcept(std::swap(e, f));
    expect_is_not_noexcept(std::swap(arr_e, arr_f));
}

struct CopyOnly {
    static inline int num_copy_ops = 0;

    int x;
    int y;

    CopyOnly(int x, int y): x(x), y(y) {}
    CopyOnly(const CopyOnly& other) noexcept : x(other.x), y(other.y) {
        num_copy_ops += 1;
    }

    CopyOnly& operator=(const CopyOnly& other) noexcept {
        x = other.x;
        y = other.y;
        num_copy_ops += 1;
        return *this;
    }
};

TEST(CopyOnly) {
    CopyOnly::num_copy_ops = 0;

    CopyOnly a{1, 2};
    CopyOnly b{3, 4};
    expect_is_noexcept(std::swap(a, b));

    std::swap(a, b);
    expect(a.x == 3 && a.y == 4);
    expect(b.x == 1 && b.y == 2);
    expect(CopyOnly::num_copy_ops == 3);

    CopyOnly::num_copy_ops = 0;
    CopyOnly arr_a[3] = {{1, 2}, {3, 4}, {5, 6}};
    CopyOnly arr_b[3] = {{7, 8}, {9, 10}, {11, 12}};
    expect_is_noexcept(std::swap(arr_a, arr_b));

    std::swap(arr_a, arr_b);
    expect(arr_a[0].x == 7 && arr_a[0].y == 8 && arr_a[1].x == 9 && arr_a[1].y == 10
           && arr_a[2].x == 11 && arr_a[2].y == 12);
    expect(arr_b[0].x == 1 && arr_b[0].y == 2 && arr_b[1].x == 3 && arr_b[1].y == 4
           && arr_b[2].x == 5 && arr_b[2].y == 6);
    expect(CopyOnly::num_copy_ops == 3 * 3);
}
