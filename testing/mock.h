#ifndef _LIGHTCXX_GUARD_TESTING_MOCK_H
#define _LIGHTCXX_GUARD_TESTING_MOCK_H

#include <stdlib.h>

namespace Testing {

void* find_next_symbol(const char* name);

template<class F>
class CFunctionMock;

template<class R, class... Args>
class CFunctionMock<R(Args...)> {
    using F = R(Args...);
    using Replacement = R(void*, void*, Args...);

    const char* symbol;
    F* original = nullptr;
    void* raw_replacement = nullptr;
    void* raw_replacement_state = nullptr;
    Replacement* replacement = nullptr;

  public:
    explicit CFunctionMock(const char* symbol): symbol(symbol) {}

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
        replacement = [](void* raw_repl, void*, Args... args) {
            return reinterpret_cast<R (*)(Args...)>(raw_repl)(args...);
        };
    }

    // Since this is only intended for libc & system functions, there is no need to worry about
    // forwarding arguments when calling.
    R invoke(Args... args) {
        if (replacement) {
            return replacement(raw_replacement, raw_replacement_state, args...);
        } else {
            if (!original) { original = reinterpret_cast<F*>(find_next_symbol(symbol)); }
            return original(args...);
        }
    }

  private:
};

extern CFunctionMock<void*(::size_t)> mock_malloc;
extern CFunctionMock<void(void*)> mock_free;
extern CFunctionMock<void*(::size_t, ::size_t)> mock_aligned_alloc;

}  // namespace Testing

#endif
