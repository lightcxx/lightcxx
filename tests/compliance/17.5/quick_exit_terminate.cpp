//EXPECT:SIGNAL_CODE 6
//EXPECT:OUTPUT_CONTAINS "success: third at_quick_exit\nsuccess: second at_quick_exit\nsuccess: terminate\n"
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

    ::std::at_quick_exit([] { fprintf(stderr, "fail: first at_quick_exit\n"); });
    ::std::at_quick_exit([] {
        fprintf(stderr, "success: second at_quick_exit\n");
        throw 5;
    });
    ::std::at_quick_exit([] { fprintf(stderr, "success: third at_quick_exit\n"); });

    ::std::quick_exit(4);
}
