// EXPECT:STEPS terminate
// EXPECT:EXIT KILLED BY SIGNAL SIGABRT

// This is based on clause [except.terminate], situation 1.5 from the note.

#include <exception>

#include "testing.h"
#include <stdlib.h>

struct SetTerminateGlobal {
    SetTerminateGlobal() {
        std::set_terminate([]() {
            step("terminate");
            ::abort();
        });
    }
};

struct ThrowGlobal {
    ThrowGlobal() {
        throw 5;
    }
};

[[maybe_unused]] SetTerminateGlobal set_terminate_;
[[maybe_unused]] ThrowGlobal throw_;

TEST() {}
