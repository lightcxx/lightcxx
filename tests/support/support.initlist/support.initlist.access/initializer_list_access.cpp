#include <initializer_list>

#include "testing.h"

TEST(empty) {
    std::initializer_list<int> i{};
    ASSERT(i.size() == 0);
    ASSERT(i.begin() == i.end());
    ASSERT(i.begin() == nullptr);
    ASSERT(i.end() == nullptr);
}

TEST(non_empty) {
    std::initializer_list<int> i{1, 2, 3, 4, 5, 6};
    ASSERT(i.size() == 6);
    ASSERT(i.begin() != nullptr);
    ASSERT(i.end() != nullptr);
    ASSERT(i.begin() + i.size() == i.end());
    ASSERT(*(i.begin() + 0) == 1);
    ASSERT(*(i.begin() + 1) == 2);
    ASSERT(*(i.begin() + 2) == 3);
    ASSERT(*(i.begin() + 3) == 4);
    ASSERT(*(i.begin() + 4) == 5);
    ASSERT(*(i.begin() + 5) == 6);
}
