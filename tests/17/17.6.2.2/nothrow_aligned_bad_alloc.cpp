// EXPECT:STEPS "aligned_alloc"

#include <new>

#include "testing/test.h"

void Testing::run() {
    libc.aligned_alloc.replace([](std::size_t align, std::size_t size) -> void* {
        expect(align == 128, "::aligned_alloc align");
        expect(size == 256, "::aligned_alloc size");
        step("aligned_alloc");
        return nullptr;
    });

    const auto const_ptr = ::operator new[](256, std::align_val_t{128}, std::nothrow);
    expect(const_ptr == nullptr, "did not return null");
}
