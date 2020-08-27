// REQUEST:SKIP "TODO: Enable this after implementing <thread>."
// EXPECT:STEPS "start_thread;terminate"
// EXPECT:EXIT KILLED BY SIGNAL SIGABRT

// This is based on clause [except.terminate], situation 1.10 from the note.

#include <exception>
#include <thread>

#include "testing.h"

TEST() {
    std::set_terminate([]() {
        step("terminate");
        ::abort();
    });

    std::thread th([]() {
        step("start_thread");
        throw 5;
    });
}
