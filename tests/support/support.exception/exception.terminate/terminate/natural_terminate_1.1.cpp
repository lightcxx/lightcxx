// EXPECT:STEPS copy_ctor,terminate
// EXPECT:EXIT KILLED BY SIGNAL SIGABRT

// This is based on clause [except.terminate], situation 1.1 from the note.

#include <exception>

#include "testing.h"
#include <stdlib.h>

struct NonCompliantException : public std::exception {
    NonCompliantException() = default;
    NonCompliantException(const NonCompliantException&): std::exception() {
        step("copy_ctor");
        throw 5;
    }
    NonCompliantException& operator=(const NonCompliantException&) {
        throw 5;
    }

    NonCompliantException(NonCompliantException&&) = delete;
    NonCompliantException& operator=(NonCompliantException&&) = delete;
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcatch-value"
TEST() {
    std::set_terminate([]() {
        step("terminate");
        ::abort();
    });

    try {
        throw NonCompliantException();
    } catch (NonCompliantException copy) {
        fail();
    }
}
#pragma GCC diagnostic pop
