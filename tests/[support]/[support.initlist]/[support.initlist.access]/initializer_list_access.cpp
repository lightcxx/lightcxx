#include <initializer_list>

#include "testing.h"

TEST(empty) {
    std::initializer_list<int> i{};
    expect(i.size() == 0);
    expect(i.begin() == i.end());
    expect(i.begin() == nullptr);
    expect(i.end() == nullptr);
}

TEST(non_empty) {
    std::initializer_list<int> i{1, 2, 3, 4, 5, 6};
    expect(i.size() == 6);
    expect(i.begin() != nullptr);
    expect(i.end() != nullptr);
    expect(i.begin() + i.size() == i.end());
    expect(*(i.begin() + 0) == 1);
    expect(*(i.begin() + 1) == 2);
    expect(*(i.begin() + 2) == 3);
    expect(*(i.begin() + 3) == 4);
    expect(*(i.begin() + 4) == 5);
    expect(*(i.begin() + 5) == 6);
}
