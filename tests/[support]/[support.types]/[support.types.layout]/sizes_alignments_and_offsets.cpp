#include <cstddef>

#include "testing.h"

struct StandardLayoutStructure {
    [[maybe_unused]] int a;
    int b;
    [[maybe_unused]] float c;
};

TEST() {
    expect_ct_and_rt(offsetof(StandardLayoutStructure, c) == sizeof(int) + sizeof(int));
    expect_ct_and_rt(noexcept(offsetof(StandardLayoutStructure, c)));

    static_assert(Testing::IsSignedIntegerType<::std::ptrdiff_t>);

    static_assert(Testing::IsUnsignedIntegerType<::std::size_t>);

    expect_ct_and_rt(alignof(::std::max_align_t) >= alignof(long double));
    expect_ct_and_rt(alignof(::std::max_align_t) >= alignof(long long));
}
