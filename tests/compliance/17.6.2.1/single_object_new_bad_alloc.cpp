//EXPECT:STEPS "malloc;throw"

#include <new>

#include "testing/test.h"

void Testing::run() {
    mock_malloc.replace([](std::size_t size) -> void* {
        expect(size == 256, "::malloc size");
        step("malloc");
        return nullptr;
    });

    try {
        [[maybe_unused]] const auto const_ptr = ::operator new(256);
        fail("did not throw");
    } catch(std::bad_alloc& exception) {
        step("throw");
    } catch(...) {
        fail("did not throw bad_alloc");
    }
}
