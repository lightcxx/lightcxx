// EXPECT:EXIT CODE = 3

#include <exception>

#include "testing.h"

TEST() {
    std::set_terminate([]() { ::_Exit(3); });

    std::terminate();
}
