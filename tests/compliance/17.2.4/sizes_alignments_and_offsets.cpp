#include <cstddef>

#include "testing/test.h"

struct StandardLayoutStructure {
    [[maybe_unused]] int a;
    int b;
    [[maybe_unused]] float c;
};

void Testing::run() {
    STATIC_EXPECT(offsetof(StandardLayoutStructure, c) == sizeof(int) + sizeof(int), "offsetof");
    STATIC_EXPECT(noexcept(offsetof(StandardLayoutStructure, c)), "offsetof noexcept");

    // TODO: Test that ptrdiff_t is signed.

    // TODO: Test that size_t is unsigned.

    STATIC_EXPECT(alignof(::std::max_align_t) >= alignof(long double));
    STATIC_EXPECT(alignof(::std::max_align_t) >= alignof(long long));
}
