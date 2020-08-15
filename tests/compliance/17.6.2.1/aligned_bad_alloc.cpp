//EXPECT:STEPS "aligned_alloc;throw"

#include <new>

#include "testing/test.h"

void Testing::run() {
    mock_aligned_alloc.replace([](std::size_t align, std::size_t size) -> void* {
        expect(align == 128, "::aligned_alloc align");
        expect(size == 256, "::aligned_alloc size");
        step("aligned_alloc");
        return nullptr;
    });

    try {
        [[maybe_unused]] const auto const_ptr = ::operator new (256, std::align_val_t{128});
        fail("did not throw");
    } catch (std::bad_alloc& exception) { step("throw"); } catch (...) {
        fail("did not throw bad_alloc");
    }
}
