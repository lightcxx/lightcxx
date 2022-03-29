#include <type_traits>

#include "testing.h"

#pragma clang diagnostic ignored "-Wconstant-evaluated"

constexpr int f() {
    if (std::is_constant_evaluated()) {
        return 1;
    } else {
        return 2;
    }
}

TEST() {
    expect(!std::is_constant_evaluated());
    static_assert(std::is_constant_evaluated());
    static_assert(
      std::is_same_v<std::bool_constant<std::is_constant_evaluated()>, std::bool_constant<true>>);

    expect(f() == 2);
    static_assert(f() == 1);

    expect_is_noexcept(std::is_constant_evaluated());
    expect_type(bool, std::is_constant_evaluated());
}
