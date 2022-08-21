// EXPECT:STEPS "malloc 1;new_handler 1;malloc 2;new_handler 2;malloc 3;new_handler 3"

#include <new>

#include "intercept_libc.h"
#include "testing.h"

int times_malloc_called = 0;
int times_new_handler_called = 0;

TEST() {
    libc.malloc.replace([](std::size_t size) -> void* {
        ++times_malloc_called;
        step("malloc %d", times_malloc_called);
        return nullptr;
    });
    std::set_new_handler([]() {
        ++times_new_handler_called;
        step("new_handler %d", times_new_handler_called);
        if (times_new_handler_called == 3) {
            libc.malloc.reset();
        }
    });

    const auto const_ptr = ::operator new(256, std::nothrow);
    expect_type(void* const&, const_ptr);
    ::operator delete(const_ptr);
}
