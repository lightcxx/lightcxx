#include <new>

#include "testing.h"

TEST() {
    alignas(long double) char space[sizeof(long double)];

    const auto placed_ptr_explicit = ::operator new(sizeof(long double), static_cast<void*>(space));
    ASSERT(placed_ptr_explicit == static_cast<void*>(space));
    ::operator delete(placed_ptr_explicit, space);

    const auto placed_ptr_natural = new (static_cast<void*>(space)) long double();
    ASSERT(placed_ptr_natural == static_cast<void*>(space));
    ::operator delete(placed_ptr_natural, space);

    const auto placed_arr_explicit = ::operator new[](sizeof(long double), static_cast<void*>(space));
    ASSERT(placed_arr_explicit == static_cast<void*>(space));
    ::operator delete[](placed_arr_explicit, space);

    const auto placed_arr_natural = new (static_cast<void*>(space)) long double[1];
    ASSERT(placed_arr_natural == static_cast<void*>(space));
    ::operator delete[](placed_arr_natural, space);
}
