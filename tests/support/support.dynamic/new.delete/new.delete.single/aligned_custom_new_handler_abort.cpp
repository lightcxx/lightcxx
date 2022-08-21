// EXPECT:EXIT KILLED BY SIGNAL SIGABRT
// EXPECT:STEPS "aligned_alloc;new_handler"

#include <new>

#include "intercept_libc.h"
#include "testing.h"
#include <stdlib.h>

TEST() {
    libc.aligned_alloc.replace([](std::size_t align, std::size_t size) -> void* {
        step("aligned_alloc");
        return nullptr;
    });
    std::set_new_handler([]() {
        step("new_handler");
        ::abort();
    });

    [[maybe_unused]] const auto const_ptr = ::operator new (256, std::align_val_t{128});
    fail();
}
