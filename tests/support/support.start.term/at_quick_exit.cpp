// EXPECT:EXIT CODE = 4
// EXPECT:STEPS 1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2,1,0

#include <cstdlib>

#include "testing.h"

static int at_exit_callback_index = 0;
static const char* steps[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

TEST() {
    for (int i = 1; i <= 9; i++) {
        ::std::at_quick_exit([]() {
            --at_exit_callback_index;
            step(steps[at_exit_callback_index]);
        });
    }
    for (int i = 1; i <= 9; i++) {
        ::std::at_quick_exit([]() {
            ++at_exit_callback_index;
            step(steps[at_exit_callback_index]);
        });
    }

    ::std::quick_exit(4);
}
