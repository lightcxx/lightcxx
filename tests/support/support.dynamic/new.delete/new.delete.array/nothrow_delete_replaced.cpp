#include <new>

#include "testing.h"
#include <stdlib.h>

bool handler_called = false;

void operator delete[](void* ptr, const std::nothrow_t&) noexcept {
    handler_called = true;
    ::free(ptr);
}

TEST() {
    auto ptr = ::operator new[](256, std::nothrow);
    compiler_forget(ptr);
    expect(!handler_called);
    ::operator delete[](ptr, std::nothrow);
    expect(handler_called);
}
