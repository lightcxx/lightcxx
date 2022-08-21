// EXPECT:STEPS "alloc 1;new_handler 1;alloc 2;new_handler 2;alloc 3;new_handler 3"

#include <new>

#include "intercept_libc.h"
#include "testing.h"

int times_aligned_alloc_called = 0;
int times_new_handler_called = 0;

TEST() {
    libc.aligned_alloc.replace([](std::size_t, std::size_t) -> void* {
        ++times_aligned_alloc_called;
        step("alloc %d", times_aligned_alloc_called);
        return nullptr;
    });
    std::set_new_handler([]() {
        ++times_new_handler_called;
        step("new_handler %d", times_new_handler_called);
        if (times_new_handler_called == 3) {
            libc.aligned_alloc.reset();
        }
    });

    const auto const_ptr = ::operator new[](256, std::align_val_t{128});
    expect_type(void* const&, const_ptr);
    ::operator delete[](const_ptr);
}
