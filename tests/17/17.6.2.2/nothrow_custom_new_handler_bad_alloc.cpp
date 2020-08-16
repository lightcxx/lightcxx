// EXPECT:STEPS "malloc;new_handler"

#include <new>

#include "testing/test.h"

void Testing::run() {
    libc.malloc.replace([](std::size_t size) -> void* {
        expect(size == 256, "::malloc size");
        step("malloc");
        return nullptr;
    });

    std::set_new_handler([]() {
        step("new_handler");
        throw std::bad_alloc();
    });

    const auto const_ptr = ::operator new[](256, std::nothrow);
    expect(const_ptr == nullptr, "did not return null");
}
