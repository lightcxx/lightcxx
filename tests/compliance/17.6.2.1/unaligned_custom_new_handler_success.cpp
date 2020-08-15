//EXPECT:STEPS "mock_malloc 1;new_handler 1;mock_malloc 2;new_handler 2;mock_malloc 3;new_handler 3"

#include <new>

#include "testing/test.h"

int times_mock_malloc_called = 0;
int times_new_handler_called = 0;

void Testing::run() {
    mock_malloc.replace([](std::size_t size) -> void* {
        ++times_mock_malloc_called;
        step("mock_malloc %d", times_mock_malloc_called);
        return nullptr;
    });
    std::set_new_handler([]() {
        ++times_new_handler_called;
        step("new_handler %d", times_new_handler_called);
        if (times_new_handler_called == 3) {
            mock_malloc.reset();
        }
    });

    const auto const_ptr = ::operator new(256);
    expectType<void* const&>(const_ptr);
    ::operator delete(const_ptr);
}
