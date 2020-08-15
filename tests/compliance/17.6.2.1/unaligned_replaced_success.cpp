//EXPECT:STEPS "new;delete"

#include <new>

#include "testing/test.h"

void* operator new(std::size_t size) {
    Testing::step("new");
    return ::malloc(size);
}

void operator delete(void* ptr) noexcept {
    Testing::step("delete");
    return ::free(ptr);
}

void Testing::run() {
    std::set_new_handler([]() {
        fail("new_handler");
        ::abort();
    });

    auto ptr = ::operator new(256);
    expectType<void*&>(ptr);
    ::operator delete(ptr);
}