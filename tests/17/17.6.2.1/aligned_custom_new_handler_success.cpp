//EXPECT:STEPS "mock_aligned_alloc 1;new_handler 1;mock_aligned_alloc 2;new_handler 2;mock_aligned_alloc 3;new_handler 3"

#include <new>

#include "testing/test.h"

int times_mock_aligned_alloc_called = 0;
int times_new_handler_called = 0;

void Testing::run() {
    mock_aligned_alloc.replace([](std::size_t, std::size_t) -> void* {
        ++times_mock_aligned_alloc_called;
        step("mock_aligned_alloc %d", times_mock_aligned_alloc_called);
        return nullptr;
    });
    std::set_new_handler([]() {
        ++times_new_handler_called;
        step("new_handler %d", times_new_handler_called);
        if (times_new_handler_called == 3) {
            mock_aligned_alloc.reset();
        }
    });

    const auto const_ptr = ::operator new(256, std::align_val_t{128});
    expectType<void* const&>(const_ptr);
    ::operator delete(const_ptr);
}
