// EXPECT:STEPS "new;delete"

#include <new>

#include "testing/test.h"

void* operator new(std::size_t size, std::align_val_t align) {
    Testing::step("new");
    return ::aligned_alloc(static_cast<std::size_t>(align), size);
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

    auto ptr = ::operator new (256, std::align_val_t{128});
    expectType<void*&>(ptr);
    ::operator delete(ptr);
}