// EXPECT:STEPS new

#include <new>

#include "testing.h"

void* operator new[](std::size_t, std::align_val_t) {
    step("new");
    throw std::bad_alloc();
}

TEST() {
    std::set_new_handler([]() { FAIL(); });

    const auto const_ptr = ::operator new[](256, std::align_val_t{128}, std::nothrow);
    ASSERT(const_ptr == nullptr);
}
