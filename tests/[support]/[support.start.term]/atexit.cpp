// EXPECT:STEPS "1;2;3;4;5;6;7;8;9;10;11;12;13;14;15;16;15;14;13;12;11;10;9;8;7;6;5;4;3;2;1;0"

#include <cstdlib>

#include "testing.h"

int at_exit_callback_index = 0;

TEST() {
    for (int i = 1; i <= 16; i++) {
        ::std::atexit([]() {
            --at_exit_callback_index;
            step("%d", at_exit_callback_index);
        });
    }
    for (int i = 1; i <= 16; i++) {
        ::std::atexit([]() {
            ++at_exit_callback_index;
            step("%d", at_exit_callback_index);
        });
    }
}
