#include <cstddef>

#include "testing.h"

struct S {
    [[maybe_unused]] int a;
    [[maybe_unused]] int b;
};

TEST() {
    constexpr void* n = NULL;
    expect_ct_and_rt(n == nullptr);
    expect_ct_and_rt(offsetof(::S, a) == 0);
    expect_ct_and_rt(offsetof(::S, b) == sizeof(int));
    expect_ct_and_rt((::std::ptrdiff_t)5 == 5);
    expect_ct_and_rt((::std::size_t)5 == 5);
    expect_ct_and_rt(alignof(::std::max_align_t) >= alignof(long double));
    expect_ct_and_rt((::std::nullptr_t)0 == nullptr);
}
