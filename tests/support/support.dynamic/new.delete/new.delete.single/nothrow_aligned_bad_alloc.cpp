// EXPECT:STEPS aligned_alloc

#include <new>

#include "intercept_libc.h"
#include "testing.h"

TEST() {
    libc.aligned_alloc.replace([](std::size_t align, std::size_t size) -> void* {
        ASSERT(align == 128);
        ASSERT(size == 256);
        step("aligned_alloc");
        return nullptr;
    });

    const auto const_ptr = ::operator new (256, std::align_val_t{128}, std::nothrow);
    ASSERT(const_ptr == nullptr);
}
