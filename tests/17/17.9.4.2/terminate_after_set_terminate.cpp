//EXPECT:EXIT CODE = 3

#include <exception>

#include "testing/test.h"

void Testing::run() {
    std::set_terminate([]() {
        ::_Exit(3);
    });

    std::terminate();
}
