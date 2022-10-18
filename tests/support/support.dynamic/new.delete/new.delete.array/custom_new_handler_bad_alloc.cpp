// EXPECT:STEPS malloc,new_handler,throw

#include <new>

#include "intercept_libc.h"
#include "testing.h"

TEST() {
    libc.malloc.replace([](std::size_t size) -> void* {
        ASSERT(size == 256);
        step("malloc");
        return nullptr;
    });

    std::set_new_handler([]() {
        step("new_handler");
        throw std::bad_alloc();
    });

    try {
        [[maybe_unused]] const auto const_ptr = ::operator new[](256);
        FAIL();
    } catch (std::bad_alloc& exception) {
        step("throw");
    } catch (...) {
        FAIL();
    }
}
