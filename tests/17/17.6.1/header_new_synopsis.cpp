#include <new>

#include <stdio.h>

#include "testing/test.h"

consteval ::std::destroying_delete_t delete_f(::std::destroying_delete_t) {
    return ::std::destroying_delete_t{};
}

::std::nothrow_t nothrow_f(::std::nothrow_t) {
    return ::std::nothrow_t{};
}

TEST() {
    [[maybe_unused]] ::std::bad_alloc b_alloc;
    [[maybe_unused]] ::std::bad_array_new_length b_array_new_length;

    [[maybe_unused]] constexpr auto delete_v = delete_f(::std::destroying_delete);

    [[maybe_unused]] constexpr ::std::align_val_t align_v{10};
    STATIC_EXPECT(static_cast<::std::size_t>(align_v) == 10, "align_val_t");

    [[maybe_unused]] ::std::nothrow_t nt_v = nothrow_f(::std::nothrow);

    ::std::new_handler h = []() { printf("Failed to allocate."); };
    const auto old_handler = ::std::set_new_handler(h);
    expect(old_handler == nullptr, "set_new_handler");
    expect(::std::get_new_handler() == h, "get_new_handler");
    ::std::set_new_handler(nullptr);

    STATIC_EXPECT(::std::hardware_constructive_interference_size >= alignof(void*));
    STATIC_EXPECT(::std::hardware_destructive_interference_size >= alignof(void*));

    using Tp = void*;

    const auto ptr1_explicit = static_cast<Tp*>(::operator new(sizeof(Tp)));
    ::operator delete(ptr1_explicit);

    expect(::std::launder(ptr1_explicit) == ptr1_explicit, "launder");

    const auto ptr1_natural = new Tp();
    delete ptr1_natural;

    const auto ptr2_explicit = ::operator new (sizeof(Tp), ::std::align_val_t{alignof(Tp)});
    ::operator delete (ptr2_explicit, ::std::align_val_t{alignof(Tp)});

    const auto ptr2_natural = new (::std::align_val_t{alignof(Tp)}) Tp();
    // Since there is no natural way to call operator delete (void*, align_val_t), and since there
    // are 6 delete variants and only 4 new variants, delete ptr2_natural using (void*, size_t)
    // instead.
    ::operator delete(ptr2_natural, sizeof(Tp));

    const auto ptr3_explicit = ::operator new(sizeof(Tp), ::std::nothrow);
    ::operator delete(ptr3_explicit, ::std::nothrow);

    const auto ptr3_natural = new (::std::nothrow) Tp();
    // Since there is no natural way to call operator delete (void*, nothrow_t), and since there
    // are 6 delete variants and only 4 new variants, delete ptr3_natural using
    // (void*, size_t, align_val_t) instead.
    ::operator delete (ptr3_natural, sizeof(Tp), ::std::align_val_t{alignof(Tp)});

    const auto ptr4_explicit
      = ::operator new (sizeof(Tp), ::std::align_val_t{alignof(Tp)}, ::std::nothrow);
    ::operator delete (ptr4_explicit, ::std::align_val_t{alignof(Tp)}, ::std::nothrow);

    const auto ptr4_natural = new (::std::align_val_t{alignof(Tp)}, ::std::nothrow) Tp();
    delete ptr4_natural;

    const auto arr1_explicit = static_cast<Tp*>(::operator new[](sizeof(Tp)));
    ::operator delete[](arr1_explicit);

    const auto arr1_natural = new Tp[1];
    delete[] arr1_natural;

    const auto arr2_explicit = ::operator new[](sizeof(Tp), ::std::align_val_t{alignof(Tp)});
    ::operator delete[](arr2_explicit, ::std::align_val_t{alignof(Tp)});

    const auto arr2_natural = new (::std::align_val_t{alignof(Tp)}) Tp[1];
    // Since there is no natural way to call operator delete[] (void*, align_val_t), and since there
    // are 6 delete[] variants and only 4 new[] variants, delete arr2_natural using (void*, size_t)
    // instead.
    ::operator delete[](arr2_natural, sizeof(Tp));

    const auto arr3_explicit = ::operator new[](sizeof(Tp), ::std::nothrow);
    ::operator delete[](arr3_explicit, ::std::nothrow);

    const auto arr3_natural = new (::std::nothrow) Tp[1];
    // Since there is no natural way to call operator delete[] (void*, nothrow_t), and since there
    // are 6 delete[] variants and only 4 new[] variants, delete arr3_natural using
    // (void*, size_t, align_val_t) instead.
    ::operator delete[](arr3_natural, sizeof(Tp), ::std::align_val_t{alignof(Tp)});

    const auto arr4_explicit
      = ::operator new[](sizeof(Tp), ::std::align_val_t{alignof(Tp)}, ::std::nothrow);
    ::operator delete[](arr4_explicit, ::std::align_val_t{alignof(Tp)}, ::std::nothrow);

    const auto arr4_natural = new (::std::align_val_t{alignof(Tp)}, ::std::nothrow) Tp[1];
    delete[] arr4_natural;

    alignas(Tp) char space[sizeof(Tp)];

    const auto placed_ptr_explicit = ::operator new(sizeof(Tp), static_cast<void*>(space));
    expect(placed_ptr_explicit == static_cast<void*>(space),
           "single-object placement new explicit");
    ::operator delete(placed_ptr_explicit, space);

    const auto placed_ptr_natural = new (static_cast<void*>(space)) Tp();
    expect(placed_ptr_natural == static_cast<void*>(space), "single-object placement new natural");
    ::operator delete(placed_ptr_natural, space);

    const auto placed_arr_explicit = ::operator new[](sizeof(Tp), static_cast<void*>(space));
    expect(placed_arr_explicit == static_cast<void*>(space), "array placement new explicit");
    ::operator delete[](placed_arr_explicit, space);

    const auto placed_arr_natural = new (static_cast<void*>(space)) Tp[1];
    expect(placed_arr_natural == static_cast<void*>(space), "array placement new natural");
    ::operator delete[](placed_arr_natural, space);
}
