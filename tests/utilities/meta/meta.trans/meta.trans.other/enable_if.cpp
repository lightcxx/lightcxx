#include <type_traits>

#include "testing.h"

TEST() {
    static_assert(std::is_same_v<void, std::enable_if<true>::type>);
    static_assert(std::is_same_v<void, std::enable_if_t<true>>);

    static_assert(std::is_same_v<void, std::enable_if<true, void>::type>);
    static_assert(std::is_same_v<void, std::enable_if_t<true, void>>);

    static_assert(std::is_same_v<int, std::enable_if<true, int>::type>);
    static_assert(std::is_same_v<int, std::enable_if_t<true, int>>);
}
