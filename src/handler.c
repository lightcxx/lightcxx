// TODO: Remove dependency on C's <stdatomic.h> once <atomic> is implemented.
#include <stdatomic.h>

_Static_assert(ATOMIC_INT_LOCK_FREE, "Lightcxx requires atomic lock-free int");
_Static_assert(sizeof(_Atomic(unsigned int)) == sizeof(unsigned int), "Lightcxx requires atomic lock-free int");
_Static_assert(_Alignof(_Atomic(unsigned int)) == _Alignof(unsigned int), "Lightcxx requires atomic lock-free int");

_Static_assert(ATOMIC_POINTER_LOCK_FREE, "Lightcxx requires atomic lock-free pointer");
_Static_assert(sizeof(_Atomic(void*)) == sizeof(void*), "Lightcxx requires atomic lock-free pointer");
_Static_assert(_Alignof(_Atomic(void*)) == _Alignof(void*), "Lightcxx requires atomic lock-free pointer");

void* light_handler_load(void** ptr) {
    return atomic_load_explicit((_Atomic(void*)*)ptr, memory_order_acquire);
}

void* light_handler_exchange(void** ptr, void* new_ptr) {
    return atomic_exchange_explicit((_Atomic(void*)*)ptr, new_ptr, memory_order_acq_rel);
}

unsigned int light_handler_count_load(unsigned int* ptr) {
    return atomic_load_explicit((_Atomic(unsigned int)*)ptr, memory_order_acquire);
}

unsigned int light_handler_count_inc(unsigned int* ptr) {
    return atomic_fetch_add_explicit((_Atomic(unsigned int)*)ptr, 1, memory_order_acq_rel);
}

unsigned int light_handler_count_dec(unsigned int* ptr) {
    return atomic_fetch_sub_explicit((_Atomic(unsigned int)*)ptr, 1, memory_order_acq_rel);
}
