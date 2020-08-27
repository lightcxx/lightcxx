//EXPECT:STEPS "terminate"
//EXPECT:EXIT KILLED BY SIGNAL SIGABRT

// This is based on clause [except.terminate], situation 1.2 from the note.

#include <exception>

#include "testing/test.h"

TEST() {
    std::set_terminate([]() {
      step("terminate");
      ::abort();
    });

    throw 5;
}
