#include <new>

#include "testing/test.h"

TEST() {
    alignas(long double) char space[sizeof(long double)];

    const auto placed_ptr_explicit = ::operator new(sizeof(long double), static_cast<void*>(space));
    expect(placed_ptr_explicit == static_cast<void*>(space),
           "single-object placement new explicit");
    ::operator delete(placed_ptr_explicit, space);

    const auto placed_ptr_natural = new (static_cast<void*>(space)) long double();
    expect(placed_ptr_natural == static_cast<void*>(space), "single-object placement new natural");
    ::operator delete(placed_ptr_natural, space);

    const auto placed_arr_explicit = ::operator new[](sizeof(long double), static_cast<void*>(space));
    expect(placed_arr_explicit == static_cast<void*>(space), "array placement new explicit");
    ::operator delete[](placed_arr_explicit, space);

    const auto placed_arr_natural = new (static_cast<void*>(space)) long double[1];
    expect(placed_arr_natural == static_cast<void*>(space), "array placement new natural");
    ::operator delete[](placed_arr_natural, space);
}
