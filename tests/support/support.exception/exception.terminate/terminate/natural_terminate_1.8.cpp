// EXPECT:STEPS "terminate"
// EXPECT:EXIT KILLED BY SIGNAL SIGABRT

// This is based on clause [except.terminate], situation 1.8 from the note.

#include <exception>

#include "testing.h"

TEST() {
    std::set_terminate([]() {
        Testing::step("terminate");
        ::abort();
    });

    throw;
}
