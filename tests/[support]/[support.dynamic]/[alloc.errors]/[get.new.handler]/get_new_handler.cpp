#include <new>

#include "testing.h"

TEST() {
    std::new_handler g = []() { step("new_handler"); };
    std::new_handler h = []() { throw std::bad_alloc(); };

    expect(std::get_new_handler() == nullptr);
    std::set_new_handler(g);
    expect(std::get_new_handler() == g);
    std::set_new_handler(h);
    expect(std::get_new_handler() == h);
    std::set_new_handler(nullptr);
    expect(std::get_new_handler() == nullptr);
    std::set_new_handler(g);
    expect(std::get_new_handler() == g);
}
