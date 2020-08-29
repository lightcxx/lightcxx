#include <cstddef>

#include "testing.h"

TEST() {
    constexpr void* null = NULL;
    expect_ct_and_rt(null == nullptr);

    auto n = nullptr;
    expect_type_and_value<::std::nullptr_t&>(n, null);

    // The type nullptr_t is a synonym for the type of a nullptr expression
    expect_type(::std::nullptr_t, nullptr);

    // [Note: the address of another nullptr_t object that is an lvalue can be taken. — end note]
    expect_type(::std::nullptr_t*, &n);
}
