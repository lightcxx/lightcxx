#include <initializer_list>

#include "testing.h"

TEST(empty) {
    std::initializer_list<int> i{};
    ASSERT(i.size() == 0);
    ASSERT(begin(i) == i.end());
    ASSERT(begin(i) == nullptr);
    ASSERT(end(i) == nullptr);
}

TEST(non_empty) {
    std::initializer_list<int> i{1, 2, 3, 4, 5, 6};
    ASSERT(i.size() == 6);
    ASSERT(begin(i) != nullptr);
    ASSERT(end(i) != nullptr);
    ASSERT(begin(i) + i.size() == i.end());
    ASSERT(*(begin(i) + 0) == 1);
    ASSERT(*(begin(i) + 1) == 2);
    ASSERT(*(begin(i) + 2) == 3);
    ASSERT(*(begin(i) + 3) == 4);
    ASSERT(*(begin(i) + 4) == 5);
    ASSERT(*(begin(i) + 5) == 6);
}
