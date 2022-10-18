#include <exception>

#include "testing.h"
#include <stdlib.h>

TEST() {
    std::terminate_handler g = []() { ::abort(); };
    std::terminate_handler h = []() { _Exit(1); };
    ASSERT(std::set_terminate(g) == nullptr);
    ASSERT(std::set_terminate(h) == g);
    ASSERT(std::set_terminate(nullptr) == h);
    ASSERT(std::set_terminate(g) == nullptr);
}
