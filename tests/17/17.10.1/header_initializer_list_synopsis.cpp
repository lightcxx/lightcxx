#include <initializer_list>

#include "testing/test.h"
#include <cstddef>
#include <string.h>

TEST(int_) {
    auto i = {1, 2, 3, 4};
    expectType<std::initializer_list<int>&>(i);
    STATIC_EXPECT(std::is_same_v<decltype(i)::value_type, int>);
    STATIC_EXPECT(std::is_same_v<decltype(i)::reference, const int&>);
    STATIC_EXPECT(std::is_same_v<decltype(i)::const_reference, const int&>);
    STATIC_EXPECT(std::is_same_v<decltype(i)::size_type, std::size_t>);
    STATIC_EXPECT(std::is_same_v<decltype(i)::iterator, const int*>);
    STATIC_EXPECT(std::is_same_v<decltype(i)::const_iterator, const int*>);

    [[maybe_unused]] std::initializer_list<int> default_ctor;

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
    expectType<std::initializer_list<const char*>&>(i);
    STATIC_EXPECT(std::is_same_v<decltype(i)::value_type, const char*>);
    STATIC_EXPECT(std::is_same_v<decltype(i)::reference, const char* const&>);
    STATIC_EXPECT(std::is_same_v<decltype(i)::const_reference, const char* const&>);
    STATIC_EXPECT(std::is_same_v<decltype(i)::size_type, std::size_t>);
    STATIC_EXPECT(std::is_same_v<decltype(i)::iterator, const char* const*>);
    STATIC_EXPECT(std::is_same_v<decltype(i)::const_iterator, const char* const*>);

    [[maybe_unused]] constexpr std::initializer_list<const char*> default_ctor;

    expect(i.size() == 5);

    expect(i.begin() != nullptr);
    expect(strcmp(*i.begin(), "1") == 0);

    expect(i.end() == i.begin() + i.size());

    expect(std::begin(i) == i.begin());
    expect(begin(i) == i.begin());

    expect(std::end(i) == i.end());
    expect(end(i) == i.end());
}
