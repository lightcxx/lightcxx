//EXPECT:EXIT KILLED BY SIGNAL SIGABRT

#include <exception>

#include "testing/test.h"

void Testing::run() {
    std::set_terminate([]() {
        ::_Exit(3);
    });
    std::set_terminate(nullptr);

    std::terminate();
}
