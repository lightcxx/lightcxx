// EXPECT:STEPS "delete;delete_size"

#include <new>

#include "testing/test.h"

void operator delete(void* ptr, std::align_val_t) noexcept {
    Testing::step("delete");
    ::free(ptr);
}

void operator delete(void* ptr, std::size_t, std::align_val_t) noexcept {
    Testing::step("delete_size");
    ::free(ptr);
}

void Testing::run() {
    const auto ptr1 = ::operator new(256, std::align_val_t{128}, std::nothrow);
    ::operator delete(ptr1, std::align_val_t{128});

    const auto ptr2 = ::operator new(256, std::align_val_t{128}, std::nothrow);
    ::operator delete(ptr2, 256, std::align_val_t{128});
}
