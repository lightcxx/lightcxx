#include <cstddef>

#include "testing/test.h"

void Testing::run() {
    constexpr void* null = NULL;
    STATIC_EXPECT(null == nullptr, "NULL");

    auto n = nullptr;
    expectTypeAndValue<::std::nullptr_t&>(n, null, "nullptr_t");

    // The type nullptr_t is a synonym for the type of a nullptr expression
    expectType<::std::nullptr_t&&>(nullptr);

    // [Note: the address of another nullptr_t object that is an lvalue can be taken. — end note]
    expectType<::std::nullptr_t*&&>(&n);
}
