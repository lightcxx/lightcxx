#include <initializer_list>

#include "testing.h"
#include <cstddef>
#include <string.h>

TEST(int_) {
    auto i = {1, 2, 3, 4};
    expect_type(std::initializer_list<int>&, i);
    expect_ct_and_rt(std::is_same_v<decltype(i)::value_type, int>);
    expect_ct_and_rt(std::is_same_v<decltype(i)::reference, const int&>);
    expect_ct_and_rt(std::is_same_v<decltype(i)::const_reference, const int&>);
    expect_ct_and_rt(std::is_same_v<decltype(i)::size_type, std::size_t>);
    expect_ct_and_rt(std::is_same_v<decltype(i)::iterator, const int*>);
    expect_ct_and_rt(std::is_same_v<decltype(i)::const_iterator, const int*>);

    std::initializer_list<int> default_ctor;

    expect(i.size() == 4);

    expect(i.begin() != nullptr);
    expect(*i.begin() == 1);

    expect(i.end() == i.begin() + i.size());

    expect(std::begin(i) == i.begin());
    expect(begin(i) == i.begin());

    expect(std::end(i) == i.end());
    expect(end(i) == i.end());
}

TEST(const_char_ptr) {
    auto i = {"1", "2", "3", "4", "123"};
    expect_type(std::initializer_list<const char*>&, i);
    expect_ct_and_rt(std::is_same_v<decltype(i)::value_type, const char*>);
    expect_ct_and_rt(std::is_same_v<decltype(i)::reference, const char* const&>);
    expect_ct_and_rt(std::is_same_v<decltype(i)::const_reference, const char* const&>);
    expect_ct_and_rt(std::is_same_v<decltype(i)::size_type, std::size_t>);
    expect_ct_and_rt(std::is_same_v<decltype(i)::iterator, const char* const*>);
    expect_ct_and_rt(std::is_same_v<decltype(i)::const_iterator, const char* const*>);

    constexpr std::initializer_list<const char*> default_ctor;

    expect(i.size() == 5);

    expect(i.begin() != nullptr);
    expect(strcmp(*i.begin(), "1") == 0);

    expect(i.end() == i.begin() + i.size());

    expect(std::begin(i) == i.begin());
    expect(begin(i) == i.begin());

    expect(std::end(i) == i.end());
    expect(end(i) == i.end());
}
