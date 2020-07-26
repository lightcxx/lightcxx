#include <exception>

#include <cstdlib>
// TODO: Remove dependency on C's <stdatomic.h> once <atomic> is implemented.
#include <stdatomic.h>

namespace {

atomic_intptr_t __terminate_handler = 0;

}

namespace std {

terminate_handler set_terminate(terminate_handler __f) noexcept {
    const auto handler = reinterpret_cast<intptr_t>(__f);
    return reinterpret_cast<terminate_handler>(
      atomic_exchange_explicit(&__terminate_handler, handler, memory_order_acq_rel));
}

terminate_handler get_terminate() noexcept {
    return reinterpret_cast<terminate_handler>(
      atomic_load_explicit(&__terminate_handler, memory_order_acquire));
}

[[noreturn]] void terminate() noexcept {
    const auto handler = get_terminate();
    if (handler) { reinterpret_cast<terminate_handler>(handler)(); }
    ::std::abort();
}

}  // namespace std
