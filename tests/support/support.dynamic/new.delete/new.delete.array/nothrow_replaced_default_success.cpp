// EXPECT:STEPS new,delete

#include <new>

#include "testing.h"
#include <stdlib.h>

void* operator new[](std::size_t size, const std::nothrow_t&) noexcept {
    step("new");
    return ::malloc(size);
}

void operator delete[](void* ptr) noexcept {
    step("delete");
    return ::free(ptr);
}

void operator delete[](void* ptr, std::size_t) noexcept {
    step("delete");
    return ::free(ptr);
}

TEST() {
    std::set_new_handler([]() { FAIL(); });

    auto ptr = ::operator new[](256, std::nothrow);
    ASSERT_TYPE(void*&, ptr);
    ::operator delete[](ptr);
}
