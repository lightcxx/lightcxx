// EXPECT:STEPS "delete;delete_size"

#include <new>

#include "testing/test.h"

void operator delete[](void* ptr) noexcept {
    Testing::step("delete");
    ::free(ptr);
}

void operator delete[](void* ptr, std::size_t) noexcept {
    Testing::step("delete_size");
    ::free(ptr);
}

void Testing::run() {
    const auto ptr1 = ::operator new[](256, std::nothrow);
    ::operator delete[](ptr1);

    const auto ptr2 = ::operator new[](256, std::nothrow);
    ::operator delete[](ptr2, 256);
}
