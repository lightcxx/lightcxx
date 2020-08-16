// EXPECT:EXIT KILLED BY SIGNAL SIGABRT
// EXPECT:STEPS "malloc;new_handler"

#include <new>

#include "testing/test.h"
#include <stdlib.h>

void Testing::run() {
    libc.malloc.replace([](std::size_t size) -> void* {
        step("malloc");
        return nullptr;
    });
    std::set_new_handler([]() {
        step("new_handler");
        ::abort();
    });

    [[maybe_unused]] const auto const_ptr = ::operator new[](256);
    fail("did not abort");
}
