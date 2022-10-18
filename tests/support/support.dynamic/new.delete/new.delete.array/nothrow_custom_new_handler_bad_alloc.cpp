// EXPECT:STEPS malloc,new_handler

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

    const auto const_ptr = ::operator new[](256, std::nothrow);
    ASSERT(const_ptr == nullptr);
}
