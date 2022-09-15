// EXPECT:NO_COMPILE 2

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

TEST() {
#if NEGATIVE_COMPILE_ITERATION == 0
    std::compare_three_way_result<B, B>::type;
#elif NEGATIVE_COMPILE_ITERATION == 1
    std::compare_three_way_result_t<B, B>;
#endif
}
