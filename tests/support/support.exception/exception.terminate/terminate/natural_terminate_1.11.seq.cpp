// REQUEST:SKIP Requires parallel algorithms and execution policies.
// EXPECT:STEPS algo_access_func,terminate
// EXPECT:EXIT KILLED BY SIGNAL SIGABRT

// This is based on clause [except.terminate], situation 1.11 from the note.

#include <algorithm>
#include <exception>

#include "testing.h"

TEST() {
    std::set_terminate([]() {
        step("terminate");
        ::abort();
    });

    const int a[]{1, 2, 3, 4};
    std::for_each(std::execution::seq, std::begin(a), std::end(a), []() {
        step("algo_access_func");
        throw 3;
    });
}
