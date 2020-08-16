#ifndef __LIGHTCXX_GUARD_SRC_HANDLER_H
#define __LIGHTCXX_GUARD_SRC_HANDLER_H

// TODO: Remove dependency on C's <stdatomic.h> once <atomic> is implemented.
#include <stdatomic.h>

namespace _Light {

template<class H>
class Handler {
    atomic_intptr_t handler = 0;

  public:
    H set(H value) noexcept {
        const auto h = reinterpret_cast<intptr_t>(value);
        return reinterpret_cast<H>(atomic_exchange_explicit(&handler, h, memory_order_acq_rel));
    }

    H get() noexcept {
        return reinterpret_cast<H>(atomic_load_explicit(&handler, memory_order_acquire));
    }
};

}  // namespace _Light

#endif
