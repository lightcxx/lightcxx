// EXPECT:STEPS "new;catch"

#include <new>

#include "testing.h"

void* operator new[](std::size_t, std::align_val_t) {
    step("new");
    throw std::bad_alloc();
}

TEST() {
    std::set_new_handler([]() { fail(); });

    try {
        [[maybe_unused]] const auto const_ptr = ::operator new[](256, std::align_val_t{128});
        fail();
    } catch (std::bad_alloc& exception) {
        step("catch");
    } catch (...) {
        fail();
    }
}