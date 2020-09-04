// EXPECT:EXIT KILLED BY SIGNAL SIGABRT

#include <exception>

#include "testing.h"

TEST() {
    std::terminate();
}
