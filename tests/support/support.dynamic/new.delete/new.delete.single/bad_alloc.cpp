// EXPECT:STEPS "malloc;throw"
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

    try {
        [[maybe_unused]] const auto const_ptr = ::operator new(256);
        fail();
    } catch (std::bad_alloc& exception) { step("throw"); } catch (...) {
        fail();
    }
}
