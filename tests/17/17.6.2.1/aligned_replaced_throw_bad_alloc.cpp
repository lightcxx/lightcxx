//EXPECT:STEPS "new;catch"

#include <new>

#include "testing/test.h"

void* operator new(std::size_t, std::align_val_t) {
    Testing::step("new");
    throw std::bad_alloc();
}

void Testing::run() {
    std::set_new_handler([]() {
        fail("new_handler");
        ::abort();
    });

    try {
        [[maybe_unused]] const auto const_ptr = ::operator new(256, std::align_val_t{128});
        fail("did not throw");
    } catch (std::bad_alloc& exception) { step("catch"); } catch (...) {
        fail("did not throw bad_alloc");
    }
}