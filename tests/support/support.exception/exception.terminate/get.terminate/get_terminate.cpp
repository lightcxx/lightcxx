#include <exception>

#include "testing.h"
#include <stdlib.h>

TEST() {
    std::terminate_handler g = []() { ::abort(); };
    std::terminate_handler h = []() { _Exit(1); };
    ASSERT(std::get_terminate() == nullptr);
    std::set_terminate(g);
    ASSERT(std::get_terminate() == g);
    std::set_terminate(h);
    ASSERT(std::get_terminate() == h);
    std::set_terminate(nullptr);
    ASSERT(std::get_terminate() == nullptr);
    std::set_terminate(g);
    ASSERT(std::get_terminate() == g);
}
