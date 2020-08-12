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
