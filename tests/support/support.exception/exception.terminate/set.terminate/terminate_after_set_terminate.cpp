// EXPECT:EXIT CODE = 3

#include <exception>

#include "testing.h"
#include <stdlib.h>

TEST() {
    std::set_terminate([]() { ::_Exit(3); });

    std::terminate();
}
