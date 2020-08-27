// EXPECT:STEPS "terminate"
// EXPECT:EXIT KILLED BY SIGNAL SIGABRT

// This is based on clause [except.terminate], situation 1.6 from the note.

#include <exception>

#include "testing/test.h"

struct ThrowInDtor {
    ~ThrowInDtor() noexcept(false) {
        throw 5;
    }
};

[[maybe_unused]] ThrowInDtor throw_;

TEST() {
    std::set_terminate([]() {
        Testing::step("terminate");
        ::abort();
    });
}
