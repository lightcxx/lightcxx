#include <cstddef>

#include "testing/test.h"

struct S {
    [[maybe_unused]] int a;
    [[maybe_unused]] int b;
};

void Testing::run() {
    constexpr void* n = NULL;
    STATIC_EXPECT(n == nullptr, "NULL");
    STATIC_EXPECT(offsetof(::S, a) == 0, "offsetof");
    STATIC_EXPECT(offsetof(::S, b) == sizeof(int), "offsetof");
    STATIC_EXPECT((::std::ptrdiff_t)5 == 5, "ptrdiff_t");
    STATIC_EXPECT((::std::size_t)5 == 5, "size_t");
    STATIC_EXPECT(alignof(::std::max_align_t) >= alignof(long double));
    STATIC_EXPECT((::std::nullptr_t)0 == nullptr, "nullptr_t");
}
