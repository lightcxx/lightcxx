// EXPECT:EXIT KILLED BY SIGNAL SIGABRT
// EXPECT:STEPS abort

#ifdef NDEBUG
#    undef NDEBUG
#endif
#include <cassert>

#include "intercept_libc.h"
#include "testing.h"

TEST() {
    libc.abort.replace([]() {
        step("abort");
        libc.abort.reset();
        ::abort();
    });

    bool value_false = false;
    compiler_forget(value_false);
    assert(value_false);
}
