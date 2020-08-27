#include <initializer_list>

#include "testing/test.h"

TEST(default_constructor) {
    constexpr std::initializer_list<int> i;
    STATIC_EXPECT(i.begin() == nullptr);
    STATIC_EXPECT(i.end() == nullptr);
    STATIC_EXPECT(i.size() == 0);
    STATIC_EXPECT(begin(i) == nullptr);
    STATIC_EXPECT(std::begin(i) == nullptr);
    STATIC_EXPECT(end(i) == nullptr);
    STATIC_EXPECT(std::end(i) == nullptr);
}

TEST(compiler_constructed) {
    std::initializer_list<int> i{1, 2, 3, 4, 5, 6};
    expect(i.size() == 6);
    expect(*(i.begin() + 0) == 1);
    expect(*(i.begin() + 1) == 2);
    expect(*(i.begin() + 2) == 3);
    expect(*(i.begin() + 3) == 4);
    expect(*(i.begin() + 4) == 5);
    expect(*(i.begin() + 5) == 6);
}

int V_init_list_ctor_num_calls = 0;
struct V {
    V(std::initializer_list<int>) {
        ++V_init_list_ctor_num_calls;
    }
    [[maybe_unused]] V(int, int, int, int) {}
};

TEST(construct_structure_via_initializer_list) {
    V_init_list_ctor_num_calls = 0;

    [[maybe_unused]] const V v = {1, 2, 3, 4};
    expect(V_init_list_ctor_num_calls == 1);

    [[maybe_unused]] const V v2{1, 2, 3, 4};
    expect(V_init_list_ctor_num_calls == 2);

    [[maybe_unused]] const V v3({1, 2, 3, 4});
    expect(V_init_list_ctor_num_calls == 3);

    [[maybe_unused]] const V v4{{1, 2, 3, 4}};
    expect(V_init_list_ctor_num_calls == 4);
}
