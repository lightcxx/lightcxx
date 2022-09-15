// EXPECT:EXIT KILLED BY SIGNAL SIGABRT
// EXPECT:STEPS third atexit,second atexit,terminate

#include <cstdlib>
#include <exception>

#include "testing.h"

TEST() {
    ::std::set_terminate([] {
        step("terminate");
        ::std::abort();
    });

    ::std::atexit([] { fail(); });
    ::std::atexit([] {
        step("second atexit");
        throw 5;
    });
    ::std::atexit([] { step("third atexit"); });

    ::std::exit(4);
}
