// EXPECT:STEPS "malloc;throw"

#include <new>

#include "intercept_libc.h"
#include "testing.h"

TEST() {
    libc.malloc.replace([](std::size_t size) -> void* {
        expect(size == 256);
        step("malloc");
        return nullptr;
    });

    try {
        const auto const_ptr = ::operator new(256);
        fail();
    } catch (std::bad_alloc& exception) {
        step("throw");
    } catch (...) {
        fail();
    }
}
