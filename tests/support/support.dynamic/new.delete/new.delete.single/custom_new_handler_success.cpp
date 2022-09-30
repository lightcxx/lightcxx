// EXPECT:STEPS malloc1,new_handler1,malloc2,new_handler2,malloc3,new_handler3

#include <new>

#include "intercept_libc.h"
#include "testing.h"

static const char* malloc_steps[] = {"malloc1", "malloc2", "malloc3"};
static const char* new_handler_steps[] = {"new_handler1", "new_handler2", "new_handler3"};

static int times_malloc_called = 0;
static int times_new_handler_called = 0;

TEST() {
    libc.malloc.replace([](std::size_t) -> void* {
        step(malloc_steps[times_malloc_called++]);
        return nullptr;
    });
    std::set_new_handler([]() {
        step(new_handler_steps[times_new_handler_called++]);
        if (times_new_handler_called == 3) {
            libc.malloc.reset();
        }
    });

    const auto const_ptr = ::operator new(256);
    expect_type(void* const&, const_ptr);
    ::operator delete(const_ptr);
}
