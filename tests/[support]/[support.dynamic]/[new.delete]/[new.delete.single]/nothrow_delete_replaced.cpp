// EXPECT:STEPS "delete"

#include <new>

#include "testing.h"

void operator delete(void* ptr, const std::nothrow_t&) noexcept {
    Testing::step("delete");
    ::free(ptr);
}

TEST() {
    const auto ptr = ::operator new(256, std::nothrow);
    ::operator delete(ptr, std::nothrow);
}
