#include <type_traits>

#include "testing.h"
#include "warnings.h"

constexpr int f() {
    if (std::is_constant_evaluated()) {
        return 1;
    } else {
        return 2;
    }
}

CLANG_DIAGNOSTIC_PUSH("clang diagnostic ignored \"-Wconstant-evaluated\"")
TEST() {
    ASSERT(!std::is_constant_evaluated());
    static_assert(std::is_constant_evaluated());
    static_assert(std::is_same_v<std::bool_constant<std::is_constant_evaluated()>, std::bool_constant<true>>);

    ASSERT(f() == 2);
    static_assert(f() == 1);

    ASSERT_NOEXCEPT(std::is_constant_evaluated());
    ASSERT_TYPE(bool, std::is_constant_evaluated());
}
CLANG_DIAGNOSTIC_POP()
