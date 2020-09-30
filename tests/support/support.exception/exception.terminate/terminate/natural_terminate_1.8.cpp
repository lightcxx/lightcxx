// EXPECT:STEPS "terminate"
// EXPECT:EXIT KILLED BY SIGNAL SIGABRT

// This is based on clause [except.terminate], situation 1.8 from the note.

#include <exception>

#include "testing.h"

#include <stdlib.h>

TEST() {
    std::set_terminate([]() {
        step("terminate");
        ::abort();
    });

    throw;
}
