// EXPECT:STEPS aligned_alloc,new_handler,throw

#include <new>

#include "intercept_libc.h"
#include "testing.h"

TEST() {
    libc.aligned_alloc.replace([](std::size_t align, std::size_t size) -> void* {
        expect(align == 128);
        expect(size == 256);
        step("aligned_alloc");
        return nullptr;
    });

    std::set_new_handler([]() {
        step("new_handler");
        throw std::bad_alloc();
    });

    try {
        [[maybe_unused]] const auto const_ptr = ::operator new[](256, std::align_val_t{128});
        fail();
    } catch (std::bad_alloc& exception) {
        step("throw");
    } catch (...) {
        fail();
    }
}
