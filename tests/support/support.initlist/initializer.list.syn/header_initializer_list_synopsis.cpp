#include <initializer_list>

#include "testing.h"
#include <cstddef>
#include <string.h>

TEST(int_) {
    auto i = {1, 2, 3, 4};
    ASSERT_TYPE(std::initializer_list<int>&, i);
    ASSERT_CT_RT((std::is_same_v<decltype(i)::value_type, int>));
    ASSERT_CT_RT((std::is_same_v<decltype(i)::reference, const int&>));
    ASSERT_CT_RT((std::is_same_v<decltype(i)::const_reference, const int&>));
    ASSERT_CT_RT((std::is_same_v<decltype(i)::size_type, std::size_t>));
    ASSERT_CT_RT((std::is_same_v<decltype(i)::iterator, const int*>));
    ASSERT_CT_RT((std::is_same_v<decltype(i)::const_iterator, const int*>));

    [[maybe_unused]] std::initializer_list<int> default_ctor;

    ASSERT(i.size() == 4);

    ASSERT(i.begin() != nullptr);
    ASSERT(*i.begin() == 1);

    ASSERT(i.end() == i.begin() + i.size());

    ASSERT(std::begin(i) == i.begin());
    ASSERT(begin(i) == i.begin());

    ASSERT(std::end(i) == i.end());
    ASSERT(end(i) == i.end());
}

TEST(const_char_ptr) {
    auto i = {"1", "2", "3", "4", "123"};
    ASSERT_TYPE(std::initializer_list<const char*>&, i);
    ASSERT_CT_RT((std::is_same_v<decltype(i)::value_type, const char*>));
    ASSERT_CT_RT((std::is_same_v<decltype(i)::reference, const char* const&>));
    ASSERT_CT_RT((std::is_same_v<decltype(i)::const_reference, const char* const&>));
    ASSERT_CT_RT((std::is_same_v<decltype(i)::size_type, std::size_t>));
    ASSERT_CT_RT((std::is_same_v<decltype(i)::iterator, const char* const*>));
    ASSERT_CT_RT((std::is_same_v<decltype(i)::const_iterator, const char* const*>));

    [[maybe_unused]] constexpr std::initializer_list<const char*> default_ctor;

    ASSERT(i.size() == 5);

    ASSERT(i.begin() != nullptr);
    ASSERT(strcmp(*i.begin(), "1") == 0);

    ASSERT(i.end() == i.begin() + i.size());

    ASSERT(std::begin(i) == i.begin());
    ASSERT(begin(i) == i.begin());

    ASSERT(std::end(i) == i.end());
    ASSERT(end(i) == i.end());
}
