#include <utility>

#include "testing.h"

struct Incomplete;

TEST() {
    expect_type(int&&, std::declval<int>());
    expect_type(int&, std::declval<int&>());
    expect_type(int&&, std::declval<int&&>());
    expect_is_noexcept(std::declval<int>());
    expect_type(Incomplete&&, std::declval<Incomplete&&>());
    expect_type(Incomplete&, std::declval<Incomplete&>());
    expect_type(Incomplete&&, std::declval<Incomplete>());
    expect_is_noexcept(std::declval<Incomplete>());
}

// Example from standard.
template<class To, class From>
[[maybe_unused]] decltype(static_cast<To>(std::declval<From>())) convert(From&&);
