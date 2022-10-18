#include <cstddef>

#include "testing.h"

TEST() {
    constexpr void* null = NULL;
    ASSERT_CT_RT(null == nullptr);

    auto n = nullptr;
    ASSERT_TYPE_AND_VALUE(n, ::std::nullptr_t&, null);

    // The type nullptr_t is a synonym for the type of a nullptr expression
    ASSERT_TYPE(::std::nullptr_t, nullptr);

    // [Note: the address of another nullptr_t object that is an lvalue can be taken. — end note]
    ASSERT_TYPE(::std::nullptr_t*, &n);
}
