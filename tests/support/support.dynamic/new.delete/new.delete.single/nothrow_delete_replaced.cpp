// EXPECT:STEPS "delete"

#include <new>

#include "testing.h"
#include <stdlib.h>

void operator delete(void* ptr, const std::nothrow_t&) noexcept {
    step("delete");
    ::free(ptr);
}

TEST() {
    auto ptr = ::operator new(256, std::nothrow);
    compiler_forget(ptr);
    ::operator delete(ptr, std::nothrow);
}
