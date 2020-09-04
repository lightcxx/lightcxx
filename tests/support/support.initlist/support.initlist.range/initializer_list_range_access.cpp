#include <initializer_list>

#include "testing.h"

TEST(empty) {
    std::initializer_list<int> i{};
    expect(i.size() == 0);
    expect(begin(i) == i.end());
    expect(begin(i) == nullptr);
    expect(end(i) == nullptr);
}

TEST(non_empty) {
    std::initializer_list<int> i{1, 2, 3, 4, 5, 6};
    expect(i.size() == 6);
    expect(begin(i) != nullptr);
    expect(end(i) != nullptr);
    expect(begin(i) + i.size() == i.end());
    expect(*(begin(i) + 0) == 1);
    expect(*(begin(i) + 1) == 2);
    expect(*(begin(i) + 2) == 3);
    expect(*(begin(i) + 3) == 4);
    expect(*(begin(i) + 4) == 5);
    expect(*(begin(i) + 5) == 6);
}
