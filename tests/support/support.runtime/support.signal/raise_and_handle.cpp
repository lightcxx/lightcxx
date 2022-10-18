#include <csignal>

#include "testing.h"

bool caught_signal;
bool caught_correct_signal;

TEST() {
    caught_signal = false;
    caught_correct_signal = false;

    std::signal(SIGUSR1, [](int v) {
        caught_signal = true;
        caught_correct_signal = (v == SIGUSR1);
    });

    std::raise(SIGUSR1);

    ASSERT(caught_signal);
    ASSERT(caught_correct_signal);
}
