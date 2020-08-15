//EXPECT:EXIT CODE = 4
//EXPECT:STEPS "~inline_thread_local;atexit;~inline_static;~global"

#include <cstdlib>

#include "testing/test.h"

struct FailPrinter {
    const char* name;

    ~FailPrinter() { Testing::fail("~%s", name); }
};

struct SuccessPrinter {
    const char* name = "local";

    ~SuccessPrinter() { Testing::step("~%s", name); }
};

[[maybe_unused]] SuccessPrinter global{.name = "global"};
[[maybe_unused]] thread_local FailPrinter t_local{.name = "thread_local"};

void Testing::run() {
    [[maybe_unused]] static SuccessPrinter inline_static{.name = "inline_static"};
    [[maybe_unused]] thread_local SuccessPrinter inline_t_local{.name = "inline_thread_local"};
    [[maybe_unused]] FailPrinter local;

    ::std::atexit([] { step("atexit"); });

    ::std::at_quick_exit([] { fail("at_quick_exit"); });

    ::std::exit(4);

    // TODO: Test note 9.2 of the spec after cstdio is implemented.
    //  Next, all open C streams (as mediated by the function signatures declared in <cstdio>
    //  ([cstdio.syn])) with unwritten buffered data are flushed, all open C streams are closed, and
    //  all files created by calling tmpfile() are removed.
}
