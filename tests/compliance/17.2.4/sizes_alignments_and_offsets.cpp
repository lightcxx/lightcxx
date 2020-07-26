#include <cstddef>

#include "lightcxx_test.h"

struct StandardLayoutStructure {
    int a;
    int b;
    float c;
};

void LightCXXTest::run() noexcept {
    STATIC_EXPECT(offsetof(StandardLayoutStructure, c) == sizeof(int) + sizeof(int), "offsetof");
    STATIC_EXPECT(noexcept(offsetof(StandardLayoutStructure, c)), "offsetof noexcept");

    // TODO: Test that ptrdiff_t is signed.

    // TODO: Test that size_t is unsigned.

    STATIC_EXPECT(alignof(::std::max_align_t) >= alignof(long double));
    STATIC_EXPECT(alignof(::std::max_align_t) >= alignof(long long));
}
