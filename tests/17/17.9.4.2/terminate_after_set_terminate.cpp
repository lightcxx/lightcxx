//EXPECT:EXIT CODE = 3

#include <exception>

#include "testing/test.h"

TEST() {
    std::set_terminate([]() {
        ::_Exit(3);
    });

    std::terminate();
}
