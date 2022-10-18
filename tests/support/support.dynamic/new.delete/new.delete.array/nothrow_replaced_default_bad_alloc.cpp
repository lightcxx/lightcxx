// EXPECT:STEPS new

#include <new>

#include "testing.h"

void* operator new[](std::size_t) {
    step("new");
    throw std::bad_alloc();
}

TEST() {
    std::set_new_handler([]() { FAIL(); });

    const auto const_ptr = ::operator new[](256, std::nothrow);
    ASSERT(const_ptr == nullptr);
}
