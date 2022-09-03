// EXPECT:STEPS "new;delete"

#include <new>

#include "testing.h"
#include <stdlib.h>

void* operator new(std::size_t size, std::align_val_t align, const std::nothrow_t&) noexcept {
    step("new");
    return ::aligned_alloc(static_cast<std::size_t>(align), size);
}

void operator delete(void* ptr) noexcept {
    step("delete");
    return ::free(ptr);
}

void operator delete(void* ptr, std::size_t) noexcept {
    step("delete");
    return ::free(ptr);
}

TEST() {
    std::set_new_handler([]() { fail(); });

    auto ptr = ::operator new (256, std::align_val_t{128}, std::nothrow);
    expect_type(void*&, ptr);
    ::operator delete(ptr);
}
