// EXPECT:EXIT KILLED BY SIGNAL SIGABRT
// EXPECT:STEPS terminate

#include <exception>

#include "testing.h"
#include <stdlib.h>

TEST() {
    std::set_terminate([]() {
        step("terminate");
        ::abort();
    });

    std::nested_exception exc;
    ASSERT(exc.nested_ptr() == nullptr);
    exc.rethrow_nested();
}
