#include <utility>

#include "testing.h"

struct Incomplete;

TEST() {
    ASSERT_TYPE(int&&, std::declval<int>());
    ASSERT_TYPE(int&, std::declval<int&>());
    ASSERT_TYPE(int&&, std::declval<int&&>());
    ASSERT_NOEXCEPT(std::declval<int>());
    ASSERT_TYPE(Incomplete&&, std::declval<Incomplete&&>());
    ASSERT_TYPE(Incomplete&, std::declval<Incomplete&>());
    ASSERT_TYPE(Incomplete&&, std::declval<Incomplete>());
    ASSERT_NOEXCEPT(std::declval<Incomplete>());
}

// Example from standard.
template<class To, class From>
[[maybe_unused]] decltype(static_cast<To>(std::declval<From>())) convert(From&&);
