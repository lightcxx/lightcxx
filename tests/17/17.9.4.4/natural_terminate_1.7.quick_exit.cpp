// EXPECT:EXIT KILLED BY SIGNAL SIGABRT
// EXPECT:STEPS "third at_quick_exit;second at_quick_exit;terminate"

// This is based on clause [except.terminate], situation 1.7 from the note.

#include <cstdlib>
#include <exception>

#include "testing/test.h"

void Testing::run() {
    ::std::set_terminate([] {
        step("terminate");
        ::std::abort();
    });

    ::std::at_quick_exit([] { fail("first at_quick_exit"); });
    ::std::at_quick_exit([] {
        step("second at_quick_exit");
        throw 5;
    });
    ::std::at_quick_exit([] { step("third at_quick_exit"); });

    ::std::quick_exit(4);
}
