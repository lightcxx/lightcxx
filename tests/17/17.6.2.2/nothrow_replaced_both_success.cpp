// EXPECT:STEPS "new_nothrow;new;delete"

#include <new>

#include "testing/test.h"

void* operator new[](std::size_t size) {
    Testing::step("new");
    return ::malloc(size);
}

void* operator new[](std::size_t size, const std::nothrow_t&) noexcept {
    Testing::step("new_nothrow");
    try {
        return ::operator new[](size);
    } catch (...) { return nullptr; }
}

void operator delete[](void* ptr) noexcept {
    Testing::step("delete");
    return ::free(ptr);
}

TEST() {
    std::set_new_handler([]() {
        fail("new_handler");
        ::abort();
    });

    auto ptr = ::operator new[](256, std::nothrow);
    expectType<void*&>(ptr);
    ::operator delete[](ptr);
}
