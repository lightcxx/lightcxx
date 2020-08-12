//EXPECT:SIGNAL_CODE 6
//EXPECT:OUTPUT_CONTAINS "success: third atexit\nsuccess: second atexit\nsuccess: terminate\n"
//EXPECT:OUTPUT_NOT_CONTAINS "fail"

#include <cstdlib>
#include <exception>

#include <stdio.h>

#include "testing/test.h"

void Testing::run() {
    ::std::set_terminate([] {
        fprintf(stderr, "success: terminate\n");
        ::std::abort();
    });

    ::std::atexit([] { fprintf(stderr, "fail: first atexit\n"); });
    ::std::atexit([] {
        fprintf(stderr, "success: second atexit\n");
        throw 5;
    });
    ::std::atexit([] { fprintf(stderr, "success: third atexit\n"); });

    ::std::exit(4);
}
