// EXPECT:STEPS "before_new;malloc;new_handler;after_new;before_second_new;second_malloc;catch"

#include <new>

#include "intercept_libc.h"
#include "testing.h"

TEST() {
    std::new_handler g = []() { step("new_handler"); };
    std::new_handler h = []() { throw std::bad_alloc(); };

    expect(std::set_new_handler(g) == nullptr);

    // return nullptr once from malloc.
    libc.malloc.replace([](std::size_t) -> void* {
        step("malloc");
        libc.malloc.reset();
        return nullptr;
    });
    step("before_new");
    auto ptr = new int(4);
    step("after_new");
    compiler_forget(ptr);
    delete ptr;

    expect(std::set_new_handler(h) == g);
    expect(std::set_new_handler(nullptr) == h);

    // return nullptr once from malloc.
    libc.malloc.replace([](std::size_t) -> void* {
        step("second_malloc");
        libc.malloc.reset();
        return nullptr;
    });
    step("before_second_new");
    try {
        [[maybe_unused]] auto failed_ptr = ::operator new(4);
        compiler_forget(failed_ptr);
        fail();
    } catch (std::bad_alloc&) {
        step("catch");
    }

    expect(std::set_new_handler(g) == nullptr);
}
