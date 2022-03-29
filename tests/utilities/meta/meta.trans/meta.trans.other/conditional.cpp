#include <type_traits>

#include "testing.h"

template<bool B, class T, class U, class E>
constexpr void test_conditional() {
    static_assert(std::is_same_v<typename std::conditional<B, T, U>::type, E>);
    static_assert(std::is_same_v<std::conditional_t<B, T, U>, E>);
}

TEST() {
    test_conditional<true, int, int, int>();
    test_conditional<false, int, int, int>();

    test_conditional<true, int, long, int>();
    test_conditional<false, int, long, long>();
}
