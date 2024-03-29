// EXPECT:STEPS delete,delete_size

#include <new>

#include "testing.h"
#include <stdlib.h>

void operator delete[](void* ptr, std::align_val_t) noexcept {
    step("delete");
    ::free(ptr);
}

void operator delete[](void* ptr, std::size_t, std::align_val_t) noexcept {
    step("delete_size");
    ::free(ptr);
}

TEST() {
    auto ptr1 = ::operator new[](256, std::align_val_t{128}, std::nothrow);
    compiler_forget(ptr1);
    ::operator delete[] (ptr1, std::align_val_t{128});

    auto ptr2 = ::operator new[](256, std::align_val_t{128}, std::nothrow);
    compiler_forget(ptr2);
    ::operator delete[] (ptr2, 256, std::align_val_t{128});
}
