// EXPECT:STEPS "before_new;malloc;new_handler;after_new;before_second_new;second_malloc;catch"

#include <new>

#include "testing/test.h"

TEST() {
    std::new_handler g = []() { step("new_handler"); };
    std::new_handler h = []() { throw std::bad_alloc(); };

    expect(std::set_new_handler(g) == nullptr, "first set_new_handler returns nullptr");

    // return nullptr once from malloc.
    libc.malloc.replace([](std::size_t size) -> void* {
        step("malloc");
        libc.malloc.reset();
        return nullptr;
    });
    step("before_new");
    auto ptr = new int(4);
    step("after_new");
    delete ptr;

    expect(std::set_new_handler(h) == g, "second set_new_handler returns argument of first");
    expect(std::set_new_handler(nullptr) == h, "third set_new_handler returns argument of second");

    // return nullptr once from malloc.
    libc.malloc.replace([](std::size_t size) -> void* {
        step("second_malloc");
        libc.malloc.reset();
        return nullptr;
    });
    step("before_second_new");
    try {
        [[maybe_unused]] auto failed_ptr = ::operator new(4);
        fail("did not throw when new handler was reset to null");
    } catch (std::bad_alloc&) { step("catch"); }

    expect(std::set_new_handler(g) == nullptr, "fourth set_new_handler returns argument of third");
}
