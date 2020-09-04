//EXPECT:NO_COMPILE 1

#include <compare>

#include "testing.h"

struct A {
    int x;
    [[maybe_unused]] int y;

    auto operator<=>(const A& a) const noexcept {
        return x <=> a.x;
    }
};

struct B {
    int x;
    [[maybe_unused]] int y;

    std::weak_ordering operator<=>(const A& a) const {
        return x <=> a.x;
    }
};

TEST() {
#if NC_TEST_ID == 0
    std::compare_three_way_result<B, B>::type;
#elif NC_TEST_ID == 1
    std::compare_three_way_result_t<B, B>;
#endif
}
