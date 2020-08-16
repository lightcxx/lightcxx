#include <new>

#include "testing/test.h"

void Testing::run() {
    std::new_handler g = []() { step("new_handler"); };
    std::new_handler h = []() { throw std::bad_alloc(); };

    expect(std::get_new_handler() == nullptr, "initial");
    std::set_new_handler(g);
    expect(std::get_new_handler() == g, "after first set_new_handler");
    std::set_new_handler(h);
    expect(std::get_new_handler() == h, "after second set_new_handler");
    std::set_new_handler(nullptr);
    expect(std::get_new_handler() == nullptr, "after third set_new_handler");
    std::set_new_handler(g);
    expect(std::get_new_handler() == g, "after fourth set_new_handler");
}
