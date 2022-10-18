#include <cstddef>

#include "testing.h"
#include <type_traits>

struct StandardLayoutStructure {
    int a;
    int b;
    float c;
};

TEST() {
    ASSERT_CT_RT(offsetof(StandardLayoutStructure, c) == sizeof(int) + sizeof(int));
    ASSERT_NOEXCEPT(offsetof(StandardLayoutStructure, c));

    static_assert(std::is_signed_v<::std::ptrdiff_t>);

    static_assert(std::is_unsigned_v<::std::size_t>);

    ASSERT_CT_RT(alignof(::std::max_align_t) >= alignof(long double));
    ASSERT_CT_RT(alignof(::std::max_align_t) >= alignof(long long));
}
