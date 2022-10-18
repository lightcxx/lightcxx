#include <new>

#include "testing.h"
#include <stdlib.h>

bool called_handler = false;

void operator delete[](void* ptr, std::align_val_t, const std::nothrow_t&) noexcept {
    called_handler = true;
    ::free(ptr);
}

TEST() {
    auto ptr = ::operator new[](256, std::align_val_t{128}, std::nothrow);
    compiler_forget(ptr);
    ASSERT(!called_handler);
    ::operator delete[] (ptr, std::align_val_t{128}, std::nothrow);
    ASSERT(called_handler);
}
