// EXPECT:STEPS "malloc;new_handler;throw"
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

    try {
        [[maybe_unused]] const auto const_ptr = ::operator new[](256);
        fail();
    } catch (std::bad_alloc& exception) {
        step("throw");
    } catch (...) {
        fail();
    }
}
