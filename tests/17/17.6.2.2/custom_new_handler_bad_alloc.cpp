// EXPECT:STEPS "malloc;new_handler;throw"

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

    try {
        [[maybe_unused]] const auto const_ptr = ::operator new[](256);
        fail("did not throw");
    } catch (std::bad_alloc& exception) { step("throw"); } catch (...) {
        fail("did not throw bad_alloc");
    }
}
