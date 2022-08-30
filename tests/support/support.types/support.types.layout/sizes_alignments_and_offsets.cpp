#include <cstddef>

#include "testing.h"
#include <type_traits>

struct StandardLayoutStructure {
    int a;
    int b;
    float c;
};

TEST() {
    expect_ct_and_rt(offsetof(StandardLayoutStructure, c) == sizeof(int) + sizeof(int));
    expect_is_noexcept(offsetof(StandardLayoutStructure, c));

    static_assert(std::is_signed_v<::std::ptrdiff_t>);

    static_assert(std::is_unsigned_v<::std::size_t>);

    expect_ct_and_rt(alignof(::std::max_align_t) >= alignof(long double));
    expect_ct_and_rt(alignof(::std::max_align_t) >= alignof(long long));
}
