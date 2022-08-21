// EXPECT:STEPS "terminate"
// EXPECT:EXIT KILLED BY SIGNAL SIGABRT

// This is based on clause [except.terminate], situation 1.6 from the note.

#include <exception>

#include "testing.h"
#include <stdlib.h>

struct ThrowInDtor {
    ~ThrowInDtor() noexcept(false) {
        throw 5;
    }
};

[[maybe_unused]] Testing::ForkSafeGlobal<ThrowInDtor> throw_;

TEST() {
    std::set_terminate([]() {
        step("terminate");
        ::abort();
    });
}
