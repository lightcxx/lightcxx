// EXPECT:EXIT CODE = 4
// EXPECT:STEPS ~inline_thread_local,atexit,~inline_static,~global

#include <cstdlib>

#include "testing.h"

struct FailPrinter {
    const char* name;

    ~FailPrinter() {
        fail();
    }
};

struct SuccessPrinter {
    const char* name = "local";

    ~SuccessPrinter() {
        step("~%s", name);
    }
};

SuccessPrinter global{.name = "global"};
thread_local FailPrinter t_local{.name = "thread_local"};

TEST() {
    static SuccessPrinter inline_static{.name = "inline_static"};
    thread_local SuccessPrinter inline_t_local{.name = "inline_thread_local"};
    FailPrinter local;

    ::std::atexit([] { step("atexit"); });

    ::std::at_quick_exit([] { fail(); });

    ::std::exit(4);

    // TODO: Test note 9.2 of the spec after cstdio is implemented.
    //  Next, all open C streams (as mediated by the function signatures declared in <cstdio>
    //  ([cstdio.bitset.syn])) with unwritten buffered data are flushed, all open C streams are closed, and
    //  all files created by calling tmpfile() are removed.
}
