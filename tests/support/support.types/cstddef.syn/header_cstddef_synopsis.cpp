#include <cstddef>

#include "testing.h"

struct S {
    int a;
    int b;
};

TEST() {
    constexpr void* n = NULL;
    ASSERT_CT_RT(n == nullptr);
    ASSERT_CT_RT(offsetof(::S, a) == 0);
    ASSERT_CT_RT(offsetof(::S, b) == sizeof(int));
    ASSERT_CT_RT(static_cast<::std::ptrdiff_t>(5) == 5);
    ASSERT_CT_RT(static_cast<::std::size_t>(5) == 5);
    ASSERT_CT_RT(alignof(::std::max_align_t) >= alignof(long double));
    ASSERT_CT_RT(static_cast<::std::nullptr_t>(0) == nullptr);
}
