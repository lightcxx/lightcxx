// EXPECT:STEPS "delete;delete_size"

#include <new>

#include "testing.h"
#include <stdlib.h>

void operator delete[](void* ptr) noexcept {
    step("delete");
    ::free(ptr);
}

void operator delete[](void* ptr, std::size_t) noexcept {
    step("delete_size");
    ::free(ptr);
}

TEST() {
    auto ptr1 = ::operator new[](256, std::nothrow);
    compiler_forget(ptr1);
    ::operator delete[](ptr1);

    auto ptr2 = ::operator new[](256, std::nothrow);
    compiler_forget(ptr2);
    ::operator delete[](ptr2, 256);
}
