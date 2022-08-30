#include <csignal>

#include "testing.h"

#ifndef SIG_DFL
#error "SIG_DFL not defined"
#endif

#ifndef SIG_ERR
#error "SIG_ERR not defined"
#endif

#ifndef SIG_IGN
#error "SIG_IGN not defined"
#endif

#ifndef SIGABRT
#error "SIGABRT not defined"
#endif

#ifndef SIGFPE
#error "SIGFPE not defined"
#endif

#ifndef SIGILL
#error "SIGILL not defined"
#endif

#ifndef SIGINT
#error "SIGINT not defined"
#endif

#ifndef SIGSEGV
#error "SIGSEGV not defined"
#endif

#ifndef SIGTERM
#error "SIGTERM not defined"
#endif

TEST() {
    std::sig_atomic_t i;

    const auto signal_lambda = []() { std::signal(SIGABRT, [](int sig) {}); };

    const auto raise_lambda = []() { std::raise(SIGABRT); };
}