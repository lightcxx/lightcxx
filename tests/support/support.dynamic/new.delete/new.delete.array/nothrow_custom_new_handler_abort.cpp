// EXPECT:EXIT KILLED BY SIGNAL SIGABRT
// EXPECT:STEPS malloc,new_handler

#include <new>

#include "intercept_libc.h"
#include "testing.h"
#include <stdlib.h>

TEST() {
    libc.malloc.replace([](std::size_t) -> void* {
        step("malloc");
        return nullptr;
    });
    std::set_new_handler([]() {
        step("new_handler");
        ::abort();
    });

    [[maybe_unused]] const auto const_ptr = ::operator new[](256, std::nothrow);
    fail();
}
