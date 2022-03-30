// EXPECT:NO_COMPILE 3

#include <utility>

#include "testing.h"

struct NoMoveCtor {
    NoMoveCtor() = default;
    NoMoveCtor(const NoMoveCtor&) = delete;
    NoMoveCtor(NoMoveCtor&&) = delete;
    NoMoveCtor& operator=(const NoMoveCtor&);
    NoMoveCtor& operator=(NoMoveCtor&&);
};

struct NoMoveAssign {
    NoMoveAssign() = default;
    NoMoveAssign(const NoMoveAssign&);
    NoMoveAssign(NoMoveAssign&&);
    NoMoveAssign& operator=(const NoMoveAssign&) = delete;
    NoMoveAssign& operator=(NoMoveAssign&&) = delete;
};

TEST() {
    NoMoveCtor a, b, arr_a[3], arr_b[3];
    NoMoveAssign c, d, arr_c[3], arr_d[3];

#if NC_TEST_ID == 0
    std::swap(a, b);
#elif NC_TEST_ID == 1
    std::swap(arr_a, arr_b);
#elif NC_TEST_ID == 2
    std::swap(c, d);
#elif NC_TEST_ID == 3
    std::swap(arr_c, arr_d);
#endif
}
