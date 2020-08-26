#include <exception>

#include "testing/test.h"

void Testing::run() {
    std::terminate_handler g = []() { ::abort(); };
    std::terminate_handler h = []() { _Exit(1); };
    expect(std::set_terminate(g) == nullptr, "first set_terminate returns nullptr");
    expect(std::set_terminate(h) == g, "second set_terminate returns argument of first");
    expect(std::set_terminate(nullptr) == h, "third set_terminate returns argument of second");
    expect(std::set_terminate(g) == nullptr, "fourth set_terminate returns argument of third");
}
