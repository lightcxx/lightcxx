#include <new>

#include "testing.h"
#include <stdlib.h>

bool simple_handler_called = false;
bool sized_handler_called = false;

void operator delete(void* ptr) noexcept {
    simple_handler_called = true;
    ::free(ptr);
}

void operator delete(void* ptr, std::size_t) noexcept {
    sized_handler_called = true;
    ::free(ptr);
}

TEST() {
    auto ptr1 = ::operator new(256, std::nothrow);
    compiler_forget(ptr1);
    ASSERT(!simple_handler_called);
    ::operator delete(ptr1);
    ASSERT(simple_handler_called);

    auto ptr2 = ::operator new(256, std::nothrow);
    compiler_forget(ptr2);
    ASSERT(!sized_handler_called);
    ::operator delete(ptr2, 256);
    ASSERT(sized_handler_called);
}
