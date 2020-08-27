// EXPECT:STEPS "malloc"

#include <new>

#include "testing/test.h"

TEST() {
    libc.malloc.replace([](std::size_t size) -> void* {
        expect(size == 256, "::malloc size");
        step("malloc");
        return nullptr;
    });

    const auto const_ptr = ::operator new[](256, std::nothrow);
    expect(const_ptr == nullptr, "did not return null");
}
