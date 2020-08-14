//EXPECT:OUTPUT_CONTAINS "success: called ::malloc\nsuccess: throw bad_alloc"

#include <new>
#include <stdio.h>

#include "testing/test.h"

void Testing::run() {
    mock_malloc.replace([](std::size_t size) -> void* {
        expect(size == 264, "::malloc size");
        fprintf(stderr, "success: called ::malloc\n");
        return nullptr;
    });

    try {
        [[maybe_unused]] const auto const_ptr = ::operator new(256);
        fail("did not throw");
    } catch(std::bad_alloc& exception) {
        fprintf(stderr, "success: throw bad_alloc");
    } catch(...) {
        fail("did not throw bad_alloc");
    }
}
