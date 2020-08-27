// EXPECT:STEPS "aligned_alloc"
// REQUEST:INTERCEPTORS "libc"

#include <new>

#include "interceptors/libc.h"
#include "testing.h"

TEST() {
    libc.aligned_alloc.replace([](std::size_t align, std::size_t size) -> void* {
        expect(align == 128);
        expect(size == 256);
        step("aligned_alloc");
        return nullptr;
    });

    const auto const_ptr = ::operator new[](256, std::align_val_t{128}, std::nothrow);
    expect(const_ptr == nullptr);
}
