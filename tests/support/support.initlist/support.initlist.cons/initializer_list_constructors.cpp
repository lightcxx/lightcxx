#include <initializer_list>

#include "testing.h"

TEST(default_constructor) {
    constexpr std::initializer_list<int> i;
    ASSERT_CT_RT(i.begin() == nullptr);
    ASSERT_CT_RT(i.end() == nullptr);
    ASSERT_CT_RT(i.size() == 0);
    ASSERT_CT_RT(begin(i) == nullptr);
    ASSERT_CT_RT(std::begin(i) == nullptr);
    ASSERT_CT_RT(end(i) == nullptr);
    ASSERT_CT_RT(std::end(i) == nullptr);
}

TEST(compiler_constructed) {
    std::initializer_list<int> i{1, 2, 3, 4, 5, 6};
    ASSERT(i.size() == 6);
    ASSERT(*(i.begin() + 0) == 1);
    ASSERT(*(i.begin() + 1) == 2);
    ASSERT(*(i.begin() + 2) == 3);
    ASSERT(*(i.begin() + 3) == 4);
    ASSERT(*(i.begin() + 4) == 5);
    ASSERT(*(i.begin() + 5) == 6);
}

int V_init_list_ctor_num_calls = 0;
struct V {
    V(std::initializer_list<int>) {
        ++V_init_list_ctor_num_calls;
    }
    V(int, int, int, int) {}
};

TEST(construct_structure_via_initializer_list) {
    V_init_list_ctor_num_calls = 0;

    [[maybe_unused]] const V v = {1, 2, 3, 4};
    ASSERT(V_init_list_ctor_num_calls == 1);

    [[maybe_unused]] const V v2{1, 2, 3, 4};
    ASSERT(V_init_list_ctor_num_calls == 2);

    [[maybe_unused]] const V v3({1, 2, 3, 4});
    ASSERT(V_init_list_ctor_num_calls == 3);

    [[maybe_unused]] const V v4{{1, 2, 3, 4}};
    ASSERT(V_init_list_ctor_num_calls == 4);
}
