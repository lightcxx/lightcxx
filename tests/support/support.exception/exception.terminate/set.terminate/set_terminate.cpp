#include <exception>

#include "testing.h"
#include <stdlib.h>

TEST() {
    std::terminate_handler g = []() { ::abort(); };
    std::terminate_handler h = []() { _Exit(1); };
    expect(std::set_terminate(g) == nullptr);
    expect(std::set_terminate(h) == g);
    expect(std::set_terminate(nullptr) == h);
    expect(std::set_terminate(g) == nullptr);
}
