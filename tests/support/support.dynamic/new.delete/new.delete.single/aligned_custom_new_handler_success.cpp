// EXPECT:STEPS alloc1,new_handler1,alloc2,new_handler2,alloc3,new_handler3

#include <new>

#include "intercept_libc.h"
#include "testing.h"

static const char* alloc_steps[] = {"alloc1", "alloc2", "alloc3"};
static const char* new_handler_steps[] = {"new_handler1", "new_handler2", "new_handler3"};

static int times_aligned_alloc_called = 0;
static int times_new_handler_called = 0;

TEST() {
    libc.aligned_alloc.replace([](std::size_t, std::size_t) -> void* {
        step(alloc_steps[times_aligned_alloc_called++]);
        return nullptr;
    });
    std::set_new_handler([]() {
        step(new_handler_steps[times_new_handler_called++]);
        if (times_new_handler_called == 3) {
            libc.aligned_alloc.reset();
        }
    });

    const auto const_ptr = ::operator new (256, std::align_val_t{128});
    expect_type(void* const&, const_ptr);
    ::operator delete(const_ptr);
}
