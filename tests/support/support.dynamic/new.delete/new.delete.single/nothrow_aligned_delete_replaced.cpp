#include <new>

#include "testing.h"
#include <stdlib.h>

bool handler_called = false;

void operator delete(void* ptr, std::align_val_t, const std::nothrow_t&) noexcept {
    handler_called = true;
    ::free(ptr);
}

TEST() {
    auto ptr = ::operator new (256, std::align_val_t{128}, std::nothrow);
    compiler_forget(ptr);
    expect(!handler_called);
    ::operator delete (ptr, std::align_val_t{128}, std::nothrow);
    expect(handler_called);
}
