//EXPECT:EXIT KILLED BY SIGNAL SIGABRT
//EXPECT:STEPS "terminate"

#include <exception>

#include "testing/test.h"

void Testing::run() {
    std::set_terminate([]() {
        step("terminate");
        ::abort();
    });

    std::rethrow_exception(nullptr);
}
