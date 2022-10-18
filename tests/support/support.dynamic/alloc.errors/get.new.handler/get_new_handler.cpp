#include <new>

#include "testing.h"

TEST() {
    std::new_handler g = []() { step("new_handler"); };
    std::new_handler h = []() { throw std::bad_alloc(); };

    ASSERT(std::get_new_handler() == nullptr);
    std::set_new_handler(g);
    ASSERT(std::get_new_handler() == g);
    std::set_new_handler(h);
    ASSERT(std::get_new_handler() == h);
    std::set_new_handler(nullptr);
    ASSERT(std::get_new_handler() == nullptr);
    std::set_new_handler(g);
    ASSERT(std::get_new_handler() == g);
}
