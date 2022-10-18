#include <new>

#include "testing.h"
#include <stdlib.h>

bool simple_handler_called = false;
bool sized_handler_called = false;

void operator delete(void* ptr, std::align_val_t) noexcept {
    simple_handler_called = true;
    ::free(ptr);
}

void operator delete(void* ptr, std::size_t, std::align_val_t) noexcept {
    sized_handler_called = true;
    ::free(ptr);
}

TEST() {
    auto ptr1 = ::operator new (256, std::align_val_t{128}, std::nothrow);
    compiler_forget(ptr1);
    ASSERT(!simple_handler_called);
    ::operator delete (ptr1, std::align_val_t{128});
    ASSERT(simple_handler_called);

    auto ptr2 = ::operator new (256, std::align_val_t{128}, std::nothrow);
    compiler_forget(ptr2);
    ASSERT(!sized_handler_called);
    ::operator delete (ptr2, 256, std::align_val_t{128});
    ASSERT(sized_handler_called);
}
