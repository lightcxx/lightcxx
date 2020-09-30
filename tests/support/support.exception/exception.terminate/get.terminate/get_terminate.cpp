#include <exception>

#include "testing.h"
#include <stdlib.h>

TEST() {
    std::terminate_handler g = []() { ::abort(); };
    std::terminate_handler h = []() { _Exit(1); };
    expect(std::get_terminate() == nullptr);
    std::set_terminate(g);
    expect(std::get_terminate() == g);
    std::set_terminate(h);
    expect(std::get_terminate() == h);
    std::set_terminate(nullptr);
    expect(std::get_terminate() == nullptr);
    std::set_terminate(g);
    expect(std::get_terminate() == g);
}
