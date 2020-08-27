// EXPECT:STEPS "malloc;new_handler"
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

    std::set_new_handler([]() {
        step("new_handler");
        throw std::bad_alloc();
    });

    const auto const_ptr = ::operator new[](256, std::nothrow);
    expect(const_ptr == nullptr);
}
