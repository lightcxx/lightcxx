// EXPECT:STEPS "new;delete"

#include <new>

#include "testing.h"

void* operator new(std::size_t size) {
    Testing::step("new");
    return ::malloc(size);
}

void operator delete(void* ptr) noexcept {
    Testing::step("delete");
    return ::free(ptr);
}

TEST() {
    std::set_new_handler([]() {
        fail();
        ::abort();
    });

    auto ptr = ::operator new(256);
    expect_type(void*&, ptr);
    ::operator delete(ptr);
}