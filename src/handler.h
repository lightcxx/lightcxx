#ifndef _LIGHTCXX_GUARD_SRC_HANDLER_H
#define _LIGHTCXX_GUARD_SRC_HANDLER_H

#include <type_traits>

namespace std::_Light {

extern "C" void* light_handler_load(void** ptr);
extern "C" void* light_handler_exchange(void** ptr, void* new_ptr);
extern "C" int light_handler_count_load(int* ptr);
extern "C" int light_handler_count_inc(int* ptr);
extern "C" int light_handler_count_dec(int* ptr);

template<class H>
class handler {
    static_assert(is_pointer_v<H>);

    void* handler = nullptr;

  public:
    H set(H value) noexcept {
        return reinterpret_cast<H>(light_handler_exchange(&handler, reinterpret_cast<void*>(value)));
    }

    H get() noexcept {
        return reinterpret_cast<H>(light_handler_load(&handler));
    }
};

template<class H, int N>
class handler_array {
    int num_hs = 0;
    handler<H> hs[N]{};

  public:
    int add(H h) {
        const auto index = light_handler_count_inc(&num_hs);
        if (index >= N) {
            light_handler_count_dec(&num_hs);
            return 1;
        }
        hs[index].set(h);
        return 0;
    }

    void run() {
        auto index = light_handler_count_load(&num_hs);
        if (index > N) {
            index = N;
        }
        for (; index > 0; --index) {
            try {
                hs[index - 1].get()();
            } catch (...) {
                std::terminate();
            }
        }
    }
};

}  // namespace std::_Light

#endif
