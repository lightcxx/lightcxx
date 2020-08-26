// REQUEST:SKIP "TODO: Enable this after implementing <thread>."
// EXPECT:STEPS "after_ctor;terminate"
// EXPECT:EXIT KILLED BY SIGNAL SIGABRT

// This is based on clause [except.terminate], situation 1.12 from the note.

#include <exception>
#include <thread>

#include "testing/test.h"

void Testing::run() {
    std::set_terminate([]() {
      step("terminate");
      ::abort();
    });

    std::thread th([]() {
        std::this_thread::sleep_for(std::chrono::seconds(3600));
    });
    step("after_ctor");
    th = std::thread([]() {
        std::this_thread::sleep_for(std::chrono::seconds(3600));
    });
}
