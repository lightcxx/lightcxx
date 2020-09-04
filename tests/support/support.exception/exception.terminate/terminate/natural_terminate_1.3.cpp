// EXPECT:STEPS "terminate"
// EXPECT:EXIT KILLED BY SIGNAL SIGABRT

// This is based on clause [except.terminate], situation 1.3 from the note.

#include <exception>

#include "testing.h"

void g(int x) {
    if (x != 2) {
        throw x;
    }
}

void f(int x) noexcept {
    if (x != 3) {
        g(x);
    }
}

TEST() {
    std::set_terminate([]() {
        step("terminate");
        ::abort();
    });

    f(get_argc());
}
