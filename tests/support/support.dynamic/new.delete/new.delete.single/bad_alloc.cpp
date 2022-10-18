// EXPECT:STEPS malloc,throw

#include <new>

#include "intercept_libc.h"
#include "testing.h"

TEST() {
    libc.malloc.replace([](std::size_t size) -> void* {
        ASSERT(size == 256);
        step("malloc");
        return nullptr;
    });

    try {
        [[maybe_unused]] const auto const_ptr = ::operator new(256);
        FAIL();
    } catch (std::bad_alloc& exception) {
        step("throw");
    } catch (...) {
        FAIL();
    }
}
