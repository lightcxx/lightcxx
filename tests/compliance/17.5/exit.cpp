//EXPECT:EXIT_CODE 4
//EXPECT:OUTPUT_CONTAINS "success: destructor of inline_thread_local\nsuccess: atexit\nsuccess: destructor of inline_static\nsuccess: destructor of global\n"
//EXPECT:OUTPUT_NOT_CONTAINS "fail"

#include <cstdlib>

#include <stdio.h>

#include "testing/test.h"

struct FailPrinter {
    const char* name;

    ~FailPrinter() { fprintf(stderr, "fail: destructor of %s\n", name); }
};

struct SuccessPrinter {
    const char* name = "local";

    ~SuccessPrinter() { fprintf(stderr, "success: destructor of %s\n", name); }
};

[[maybe_unused]] SuccessPrinter global{.name = "global"};
[[maybe_unused]] thread_local FailPrinter t_local{.name = "thread_local"};

void Testing::run() {
    [[maybe_unused]] static SuccessPrinter inline_static{.name = "inline_static"};
    [[maybe_unused]] thread_local SuccessPrinter inline_t_local{.name = "inline_thread_local"};
    [[maybe_unused]] FailPrinter local;

    ::std::atexit([] { fprintf(stderr, "success: atexit\n"); });

    ::std::at_quick_exit([] { fprintf(stderr, "fail: at_quick_exit\n"); });

    ::std::exit(4);

    // TODO: Test note 9.2 of the spec after cstdio is implemented.
    //  Next, all open C streams (as mediated by the function signatures declared in <cstdio>
    //  ([cstdio.syn])) with unwritten buffered data are flushed, all open C streams are closed, and
    //  all files created by calling tmpfile() are removed.
}
