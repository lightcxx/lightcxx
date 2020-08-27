// EXPECT:STEPS "malloc"
// REQUEST:INTERCEPTORS "libc"

#include <new>

#include "interceptors/libc.h"
#include "testing.h"

TEST() {
    libc.malloc.replace([](std::size_t size) -> void* {
        expect(size == 256);
        step("malloc");
        return nullptr;
    });

    const auto const_ptr = ::operator new(256, std::nothrow);
    expect(const_ptr == nullptr);
}
