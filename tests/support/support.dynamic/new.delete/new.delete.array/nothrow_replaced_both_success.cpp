// EXPECT:STEPS "new_nothrow;new;delete"

#include <new>

#include "testing.h"
#include <stdlib.h>

void* operator new[](std::size_t size) {
    step("new");
    return ::malloc(size);
}

void* operator new[](std::size_t size, const std::nothrow_t&) noexcept {
    step("new_nothrow");
    try {
        return ::operator new[](size);
    } catch (...) {
        return nullptr;
    }
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
    std::set_new_handler([]() { fail(); });

    auto ptr = ::operator new[](256, std::nothrow);
    expect_type(void*&, ptr);
    ::operator delete[](ptr);
}
