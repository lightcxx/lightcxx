// EXPECT:STEPS "delete"

#include <new>

#include "testing.h"

void operator delete(void* ptr, std::align_val_t, const std::nothrow_t&) noexcept {
    Testing::step("delete");
    ::free(ptr);
}

TEST() {
    const auto ptr = ::operator new (256, std::align_val_t{128}, std::nothrow);
    ::operator delete (ptr, std::align_val_t{128}, std::nothrow);
}
