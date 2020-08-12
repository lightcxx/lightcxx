//EXPECT:EXIT_CODE 4
//EXPECT:OUTPUT_CONTAINS "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n15\n14\n13\n12\n11\n10\n9\n8\n7\n6\n5\n4\n3\n2\n1\n0\n"

#include <cstdlib>

#include <stdio.h>

#include "testing/test.h"

int at_exit_callback_index = 0;

void Testing::run() {
    for (int i = 1; i <= 16; i++) {
        ::std::at_quick_exit([]() {
          --at_exit_callback_index;
          fprintf(stderr, "%d\n", at_exit_callback_index);
        });
    }
    for (int i = 1; i <= 16; i++) {
        ::std::at_quick_exit([]() {
            ++at_exit_callback_index;
            fprintf(stderr, "%d\n", at_exit_callback_index);
        });
    }

    ::std::quick_exit(4);
}
