// EXPECT:STEPS "new;catch"

#include <new>

#include "testing.h"

void* operator new[](std::size_t) {
    step("new");
    throw std::bad_alloc();
}

TEST() {
    std::set_new_handler([]() { fail(); });

    try {
        const auto const_ptr = ::operator new[](256);
        fail();
    } catch (std::bad_alloc& exception) {
        step("catch");
    } catch (...) {
        fail();
    }
}