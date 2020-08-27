//EXPECT:EXIT KILLED BY SIGNAL SIGABRT

#include <exception>

#include "testing/test.h"

TEST() {
    std::terminate();
}
