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

Testing::ForkSafeGlobal<SetTerminateGlobal> set_terminate_;
Testing::ForkSafeGlobal<ThrowGlobal> throw_;

TEST() {}
