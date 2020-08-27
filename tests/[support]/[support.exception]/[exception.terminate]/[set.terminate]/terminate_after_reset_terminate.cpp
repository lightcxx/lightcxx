// EXPECT:EXIT KILLED BY SIGNAL SIGABRT

#include <exception>

#include "testing.h"

TEST() {
    std::set_terminate([]() { ::_Exit(3); });
    std::set_terminate(nullptr);

    std::terminate();
}
