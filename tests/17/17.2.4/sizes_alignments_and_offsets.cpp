#include <cstddef>

#include "testing/test.h"

struct StandardLayoutStructure {
    [[maybe_unused]] int a;
    int b;
    [[maybe_unused]] float c;
};

TEST() {
    STATIC_EXPECT(offsetof(StandardLayoutStructure, c) == sizeof(int) + sizeof(int), "offsetof");
    STATIC_EXPECT(noexcept(offsetof(StandardLayoutStructure, c)), "offsetof noexcept");

    static_assert(Testing::IsSignedIntegerType<::std::ptrdiff_t>);

    static_assert(Testing::IsUnsignedIntegerType<::std::size_t>);

    STATIC_EXPECT(alignof(::std::max_align_t) >= alignof(long double));
    STATIC_EXPECT(alignof(::std::max_align_t) >= alignof(long long));
}
