// TODO: Remove dependency on C's <stdatomic.h> once <atomic> is implemented.
#include <stdatomic.h>

_Static_assert(ATOMIC_INT_LOCK_FREE, "Lightcxx requires atomic lock-free int");
_Static_assert(ATOMIC_POINTER_LOCK_FREE, "Lightcxx requires atomic lock-free pointer");

void* light_handler_load(void** ptr) {
    return atomic_load_explicit((_Atomic(void*)*)ptr, memory_order_acquire);
}

void* light_handler_exchange(void** ptr, void* new_ptr) {
    return atomic_exchange_explicit((_Atomic(void*)*)ptr, new_ptr, memory_order_acq_rel);
}

int light_handler_count_load(int* ptr) {
    return atomic_load_explicit((_Atomic(int)*)ptr, memory_order_acquire);
}

int light_handler_count_inc(int* ptr) {
    return atomic_fetch_add_explicit((_Atomic(int)*)ptr, 1, memory_order_acq_rel);
}

int light_handler_count_dec(int* ptr) {
    return atomic_fetch_sub_explicit((_Atomic(int)*)ptr, 1, memory_order_acq_rel);
}
