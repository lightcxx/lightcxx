//EXPECT:EXIT KILLED BY SIGNAL SIGABRT

#include <exception>

#include "testing/test.h"

void Testing::run() {
    std::terminate();
}
