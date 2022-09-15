// EXPECT:STEPS catch1,catch2,terminate
// EXPECT:EXIT KILLED BY SIGNAL SIGABRT

// This is based on clause [except.terminate], situation 1.4 from the note.

#include <exception>

#include "testing.h"
#include <stdlib.h>

struct ThrowingDestructor {
    ~ThrowingDestructor() noexcept(false) {
        throw 3;
    }
};

TEST() {
    std::set_terminate([]() {
        step("terminate");
        ::abort();
    });

    try {
        throw 1;
    } catch (...) {
        step("catch1");
        try {
            throw 2;
        } catch (...) {
            step("catch2");
            ThrowingDestructor var;
        }
    }
}
