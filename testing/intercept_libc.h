#ifndef TESTING_INTERCEPTORS_LIBC_H
#define TESTING_INTERCEPTORS_LIBC_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

namespace Testing {

template<class F>
class CFunctionInterceptor;

template<class R, class... Args>
class CFunctionInterceptor<R(Args...)> {
    using F = R(Args...);
    using Replacement = R(void*, void*, Args...);

    const char* symbol;
    F* original = nullptr;
    void* raw_replacement = nullptr;
    void* raw_replacement_state = nullptr;
    Replacement* replacement = nullptr;

  public:
    CFunctionInterceptor(const char* symbol)
            : symbol(symbol) {}

    void reset() {
        raw_replacement = nullptr;
        raw_replacement_state = nullptr;
        replacement = nullptr;
    }

    template<class T>
    void replace(T& state, R (*repl)(T&, Args...)) {
        raw_replacement_state = reinterpret_cast<void*>(&state);
        raw_replacement = reinterpret_cast<void*>(repl);
        replacement = [](void* raw_repl, void* raw_state, Args... args) {
            return reinterpret_cast<R (*)(T&, Args...)>(raw_repl)(*reinterpret_cast<T*>(raw_state), args...);
        };
    }

    void replace(R (*repl)(Args...)) {
        raw_replacement_state = nullptr;
        raw_replacement = reinterpret_cast<void*>(repl);
        replacement = [](void* raw_repl, void*, Args... args) { return reinterpret_cast<R (*)(Args...)>(raw_repl)(args...); };
    }

    // Since this is only intended for libc & system functions, there is no need to worry about
    // forwarding arguments when calling.
    R invoke(Args... args) {
        if (replacement) {
            return replacement(raw_replacement, raw_replacement_state, args...);
        } else {
            if (!original) {
                original = reinterpret_cast<F*>(dlsym(RTLD_NEXT, symbol));
            }
            return original(args...);
        }
    }
};

extern struct LibCInterceptors {
    CFunctionInterceptor<void*(::size_t)> malloc{"malloc"};
    CFunctionInterceptor<void(void*)> free{"free"};
    CFunctionInterceptor<void*(::size_t, ::size_t)> aligned_alloc{"aligned_alloc"};
    CFunctionInterceptor<void()> abort{"abort"};
} libc;

}  // namespace Testing

#endif
