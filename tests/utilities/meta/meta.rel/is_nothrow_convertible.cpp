#include <type_traits>

#include "testing.h"

template<class From, class To, bool e>
constexpr void expect_is_nothrow_convertible() {
    static_assert(std::is_nothrow_convertible<From, To>::value == e);
    static_assert(std::is_base_of_v<std::bool_constant<e>, std::is_nothrow_convertible<From, To>>);
    static_assert(std::is_same_v<typename std::is_nothrow_convertible<From, To>::value_type, bool>);
    static_assert(std::is_nothrow_convertible<From, To>{} == e);
    static_assert((bool)std::is_nothrow_convertible<From, To>{} == e);
    static_assert(noexcept((bool)std::is_nothrow_convertible<From, To>{}));
    static_assert(std::is_nothrow_convertible<From, To>{}() == e);
    static_assert(noexcept(std::is_nothrow_convertible<From, To>{}()));
    static_assert(std::is_same_v<bool, decltype(std::is_nothrow_convertible<From, To>{}())>);
    static_assert(std::is_same_v<typename std::is_nothrow_convertible<From, To>::type, std::bool_constant<e>>);
    static_assert(std::is_same_v<decltype(std::is_nothrow_convertible_v<From, To>), const bool>);
    static_assert(std::is_nothrow_convertible_v<From, To> == e);
}

TEST(voids) {
    expect_is_nothrow_convertible<void, void, true>();
    expect_is_nothrow_convertible<const void, void, true>();
    expect_is_nothrow_convertible<void, const void, true>();
    expect_is_nothrow_convertible<const void, const void, true>();

    expect_is_nothrow_convertible<void, int(), false>();
    expect_is_nothrow_convertible<void, int (&)(), false>();
    expect_is_nothrow_convertible<void, int (*)(), false>();
    expect_is_nothrow_convertible<void, int[10], false>();
    expect_is_nothrow_convertible<void, int(&)[10], false>();
    expect_is_nothrow_convertible<void, int[], false>();
    expect_is_nothrow_convertible<void, int, false>();
    expect_is_nothrow_convertible<void, int&, false>();
    expect_is_nothrow_convertible<void, int*, false>();
    expect_is_nothrow_convertible<int, void, false>();
}

TEST(pointers) {
    // To same pointer
    expect_is_nothrow_convertible<int*, int*, true>();
    expect_is_nothrow_convertible<int*, const int*, true>();
    expect_is_nothrow_convertible<int*, volatile int*, true>();
    expect_is_nothrow_convertible<int*, const volatile int*, true>();
    expect_is_nothrow_convertible<const int*, int*, false>();
    expect_is_nothrow_convertible<const int*, const int*, true>();
    expect_is_nothrow_convertible<const int*, volatile int*, false>();
    expect_is_nothrow_convertible<const int*, const volatile int*, true>();
    expect_is_nothrow_convertible<volatile int*, int*, false>();
    expect_is_nothrow_convertible<volatile int*, const int*, false>();
    expect_is_nothrow_convertible<volatile int*, volatile int*, true>();
    expect_is_nothrow_convertible<volatile int*, const volatile int*, true>();
    expect_is_nothrow_convertible<const volatile int*, int*, false>();
    expect_is_nothrow_convertible<const volatile int*, const int*, false>();
    expect_is_nothrow_convertible<const volatile int*, volatile int*, false>();
    expect_is_nothrow_convertible<const volatile int*, const volatile int*, true>();

    // To void pointer
    expect_is_nothrow_convertible<int*, void*, true>();
    expect_is_nothrow_convertible<int*, const void*, true>();
    expect_is_nothrow_convertible<int*, volatile void*, true>();
    expect_is_nothrow_convertible<int*, const volatile void*, true>();
    expect_is_nothrow_convertible<const int*, void*, false>();
    expect_is_nothrow_convertible<const int*, const void*, true>();
    expect_is_nothrow_convertible<const int*, volatile void*, false>();
    expect_is_nothrow_convertible<const int*, const volatile void*, true>();
    expect_is_nothrow_convertible<volatile int*, void*, false>();
    expect_is_nothrow_convertible<volatile int*, const void*, false>();
    expect_is_nothrow_convertible<volatile int*, volatile void*, true>();
    expect_is_nothrow_convertible<volatile int*, const volatile void*, true>();
    expect_is_nothrow_convertible<const volatile int*, void*, false>();
    expect_is_nothrow_convertible<const volatile int*, const void*, false>();
    expect_is_nothrow_convertible<const volatile int*, volatile void*, false>();
    expect_is_nothrow_convertible<const volatile int*, const volatile void*, true>();

    // To pointer of compatible type
    expect_is_nothrow_convertible<int*, long*, false>();
    expect_is_nothrow_convertible<int*, const long*, false>();
    expect_is_nothrow_convertible<int*, volatile long*, false>();
    expect_is_nothrow_convertible<int*, const volatile long*, false>();
    expect_is_nothrow_convertible<const int*, long*, false>();
    expect_is_nothrow_convertible<const int*, const long*, false>();
    expect_is_nothrow_convertible<const int*, volatile long*, false>();
    expect_is_nothrow_convertible<const int*, const volatile long*, false>();
    expect_is_nothrow_convertible<volatile int*, long*, false>();
    expect_is_nothrow_convertible<volatile int*, const long*, false>();
    expect_is_nothrow_convertible<volatile int*, volatile long*, false>();
    expect_is_nothrow_convertible<volatile int*, const volatile long*, false>();
    expect_is_nothrow_convertible<const volatile int*, long*, false>();
    expect_is_nothrow_convertible<const volatile int*, const long*, false>();
    expect_is_nothrow_convertible<const volatile int*, volatile long*, false>();
    expect_is_nothrow_convertible<const volatile int*, const volatile long*, false>();
}

TEST(references) {
    // Lvalue to same lvalue ref
    expect_is_nothrow_convertible<int&, int&, true>();
    expect_is_nothrow_convertible<int&, const int&, true>();
    expect_is_nothrow_convertible<int&, volatile int&, true>();
    expect_is_nothrow_convertible<int&, const volatile int&, true>();
    expect_is_nothrow_convertible<const int&, int&, false>();
    expect_is_nothrow_convertible<const int&, const int&, true>();
    expect_is_nothrow_convertible<const int&, volatile int&, false>();
    expect_is_nothrow_convertible<const int&, const volatile int&, true>();
    expect_is_nothrow_convertible<volatile int&, int&, false>();
    expect_is_nothrow_convertible<volatile int&, const int&, false>();
    expect_is_nothrow_convertible<volatile int&, volatile int&, true>();
    expect_is_nothrow_convertible<volatile int&, const volatile int&, true>();
    expect_is_nothrow_convertible<const volatile int&, int&, false>();
    expect_is_nothrow_convertible<const volatile int&, const int&, false>();
    expect_is_nothrow_convertible<const volatile int&, volatile int&, false>();
    expect_is_nothrow_convertible<const volatile int&, const volatile int&, true>();

    // Lvalue to lvalue ref of compatible type
    expect_is_nothrow_convertible<int&, long&, false>();
    expect_is_nothrow_convertible<int&, const long&, true>();
    expect_is_nothrow_convertible<int&, volatile long&, false>();
    expect_is_nothrow_convertible<int&, const volatile long&, false>();
    expect_is_nothrow_convertible<const int&, long&, false>();
    expect_is_nothrow_convertible<const int&, const long&, true>();
    expect_is_nothrow_convertible<const int&, volatile long&, false>();
    expect_is_nothrow_convertible<const int&, const volatile long&, false>();
    expect_is_nothrow_convertible<volatile int&, long&, false>();
    expect_is_nothrow_convertible<volatile int&, const long&, true>();
    expect_is_nothrow_convertible<volatile int&, volatile long&, false>();
    expect_is_nothrow_convertible<volatile int&, const volatile long&, false>();
    expect_is_nothrow_convertible<const volatile int&, long&, false>();
    expect_is_nothrow_convertible<const volatile int&, const long&, true>();
    expect_is_nothrow_convertible<const volatile int&, volatile long&, false>();
    expect_is_nothrow_convertible<const volatile int&, const volatile long&, false>();

    // Rvalue to same lvalue ref
    expect_is_nothrow_convertible<int&&, int&, false>();
    expect_is_nothrow_convertible<int&&, const int&, true>();
    expect_is_nothrow_convertible<int&&, volatile int&, false>();
    expect_is_nothrow_convertible<int&&, const volatile int&, false>();
    expect_is_nothrow_convertible<const int&&, int&, false>();
    expect_is_nothrow_convertible<const int&&, const int&, true>();
    expect_is_nothrow_convertible<const int&&, volatile int&, false>();
    expect_is_nothrow_convertible<const int&&, const volatile int&, false>();
    expect_is_nothrow_convertible<volatile int&&, int&, false>();
    expect_is_nothrow_convertible<volatile int&&, const int&, false>();
    expect_is_nothrow_convertible<volatile int&&, volatile int&, false>();
    expect_is_nothrow_convertible<volatile int&&, const volatile int&, false>();
    expect_is_nothrow_convertible<const volatile int&&, int&, false>();
    expect_is_nothrow_convertible<const volatile int&&, const int&, false>();
    expect_is_nothrow_convertible<const volatile int&&, volatile int&, false>();
    expect_is_nothrow_convertible<const volatile int&&, const volatile int&, false>();

    // Rvalue to lvalue ref of compatible type
    expect_is_nothrow_convertible<int&&, long&, false>();
    expect_is_nothrow_convertible<int&&, const long&, true>();
    expect_is_nothrow_convertible<int&&, volatile long&, false>();
    expect_is_nothrow_convertible<int&&, const volatile long&, false>();
    expect_is_nothrow_convertible<const int&&, long&, false>();
    expect_is_nothrow_convertible<const int&&, const long&, true>();
    expect_is_nothrow_convertible<const int&&, volatile long&, false>();
    expect_is_nothrow_convertible<const int&&, const volatile long&, false>();
    expect_is_nothrow_convertible<volatile int&&, long&, false>();
    expect_is_nothrow_convertible<volatile int&&, const long&, true>();
    expect_is_nothrow_convertible<volatile int&&, volatile long&, false>();
    expect_is_nothrow_convertible<volatile int&&, const volatile long&, false>();
    expect_is_nothrow_convertible<const volatile int&&, long&, false>();
    expect_is_nothrow_convertible<const volatile int&&, const long&, true>();
    expect_is_nothrow_convertible<const volatile int&&, volatile long&, false>();
    expect_is_nothrow_convertible<const volatile int&&, const volatile long&, false>();

    // Lvalue to same rvalue ref
    expect_is_nothrow_convertible<int&, int&&, false>();
    expect_is_nothrow_convertible<int&, const int&&, false>();
    expect_is_nothrow_convertible<int&, volatile int&&, false>();
    expect_is_nothrow_convertible<int&, const volatile int&&, false>();
    expect_is_nothrow_convertible<const int&, int&&, false>();
    expect_is_nothrow_convertible<const int&, const int&&, false>();
    expect_is_nothrow_convertible<const int&, volatile int&&, false>();
    expect_is_nothrow_convertible<const int&, const volatile int&&, false>();
    expect_is_nothrow_convertible<volatile int&, int&&, false>();
    expect_is_nothrow_convertible<volatile int&, const int&&, false>();
    expect_is_nothrow_convertible<volatile int&, volatile int&&, false>();
    expect_is_nothrow_convertible<volatile int&, const volatile int&&, false>();
    expect_is_nothrow_convertible<const volatile int&, int&&, false>();
    expect_is_nothrow_convertible<const volatile int&, const int&&, false>();
    expect_is_nothrow_convertible<const volatile int&, volatile int&&, false>();
    expect_is_nothrow_convertible<const volatile int&, const volatile int&&, false>();

    // Lvalue to rvalue ref of compatible type
    expect_is_nothrow_convertible<int&, long&&, true>();
    expect_is_nothrow_convertible<int&, const long&&, true>();
    expect_is_nothrow_convertible<int&, volatile long&&, true>();
    expect_is_nothrow_convertible<int&, const volatile long&&, true>();
    expect_is_nothrow_convertible<const int&, long&&, true>();
    expect_is_nothrow_convertible<const int&, const long&&, true>();
    expect_is_nothrow_convertible<const int&, volatile long&&, true>();
    expect_is_nothrow_convertible<const int&, const volatile long&&, true>();
    expect_is_nothrow_convertible<volatile int&, long&&, true>();
    expect_is_nothrow_convertible<volatile int&, const long&&, true>();
    expect_is_nothrow_convertible<volatile int&, volatile long&&, true>();
    expect_is_nothrow_convertible<volatile int&, const volatile long&&, true>();
    expect_is_nothrow_convertible<const volatile int&, long&&, true>();
    expect_is_nothrow_convertible<const volatile int&, const long&&, true>();
    expect_is_nothrow_convertible<const volatile int&, volatile long&&, true>();
    expect_is_nothrow_convertible<const volatile int&, const volatile long&&, true>();

    // Rvalue to same rvalue ref
    expect_is_nothrow_convertible<int&&, int&&, true>();
    expect_is_nothrow_convertible<int&&, const int&&, true>();
    expect_is_nothrow_convertible<int&&, volatile int&&, true>();
    expect_is_nothrow_convertible<int&&, const volatile int&&, true>();
    expect_is_nothrow_convertible<const int&&, int&&, false>();
    expect_is_nothrow_convertible<const int&&, const int&&, true>();
    expect_is_nothrow_convertible<const int&&, volatile int&&, false>();
    expect_is_nothrow_convertible<const int&&, const volatile int&&, true>();
    expect_is_nothrow_convertible<volatile int&&, int&&, false>();
    expect_is_nothrow_convertible<volatile int&&, const int&&, false>();
    expect_is_nothrow_convertible<volatile int&&, volatile int&&, true>();
    expect_is_nothrow_convertible<volatile int&&, const volatile int&&, true>();
    expect_is_nothrow_convertible<const volatile int&&, int&&, false>();
    expect_is_nothrow_convertible<const volatile int&&, const int&&, false>();
    expect_is_nothrow_convertible<const volatile int&&, volatile int&&, false>();
    expect_is_nothrow_convertible<const volatile int&&, const volatile int&&, true>();

    // Rvalue to rvalue ref of compatible type
    expect_is_nothrow_convertible<int&&, long&&, true>();
    expect_is_nothrow_convertible<int&&, const long&&, true>();
    expect_is_nothrow_convertible<int&&, volatile long&&, true>();
    expect_is_nothrow_convertible<int&&, const volatile long&&, true>();
    expect_is_nothrow_convertible<const int&&, long&&, true>();
    expect_is_nothrow_convertible<const int&&, const long&&, true>();
    expect_is_nothrow_convertible<const int&&, volatile long&&, true>();
    expect_is_nothrow_convertible<const int&&, const volatile long&&, true>();
    expect_is_nothrow_convertible<volatile int&&, long&&, true>();
    expect_is_nothrow_convertible<volatile int&&, const long&&, true>();
    expect_is_nothrow_convertible<volatile int&&, volatile long&&, true>();
    expect_is_nothrow_convertible<volatile int&&, const volatile long&&, true>();
    expect_is_nothrow_convertible<const volatile int&&, long&&, true>();
    expect_is_nothrow_convertible<const volatile int&&, const long&&, true>();
    expect_is_nothrow_convertible<const volatile int&&, volatile long&&, true>();
    expect_is_nothrow_convertible<const volatile int&&, const volatile long&&, true>();
}

TEST(value) {
    expect_is_nothrow_convertible<int&, int, true>();
    expect_is_nothrow_convertible<const int&, int, true>();
    expect_is_nothrow_convertible<volatile int&, int, true>();
    expect_is_nothrow_convertible<const volatile int&, int, true>();
    expect_is_nothrow_convertible<int&&, int, true>();
    expect_is_nothrow_convertible<const int&&, int, true>();
    expect_is_nothrow_convertible<volatile int&&, int, true>();
    expect_is_nothrow_convertible<const volatile int&&, int, true>();

    expect_is_nothrow_convertible<int, int&, false>();
    expect_is_nothrow_convertible<int, const int&, true>();
    expect_is_nothrow_convertible<int, volatile int&, false>();
    expect_is_nothrow_convertible<int, const volatile int&, false>();
    expect_is_nothrow_convertible<int, int&&, true>();
    expect_is_nothrow_convertible<int, const int&&, true>();
    expect_is_nothrow_convertible<int, volatile int&&, true>();
    expect_is_nothrow_convertible<int, const volatile int&&, true>();
}

TEST(function) {
    expect_is_nothrow_convertible<int(), int (*)(), true>();
    expect_is_nothrow_convertible<int (*)(), int(), false>();

    expect_is_nothrow_convertible<int(), int (&)(), true>();
    expect_is_nothrow_convertible<int (&)(), int(), false>();

    expect_is_nothrow_convertible<int(), int(&&)(), true>();
    expect_is_nothrow_convertible<int(&&)(), int(), false>();

    expect_is_nothrow_convertible<int (&)(), int (*)(), true>();
    expect_is_nothrow_convertible<int (*)(), int (&)(), false>();

    expect_is_nothrow_convertible<int (&)(), int(&&)(), true>();
    expect_is_nothrow_convertible<int(&&)(), int (&)(), true>();

    expect_is_nothrow_convertible<int(&&)(), int (*)(), true>();
    expect_is_nothrow_convertible<int (*)(), int(&&)(), false>();
}

TEST(array) {
    expect_is_nothrow_convertible<int[10], int*, true>();
    expect_is_nothrow_convertible<int*, int[10], false>();

    expect_is_nothrow_convertible<int[], int*, true>();
    expect_is_nothrow_convertible<int*, int[], false>();

    expect_is_nothrow_convertible<int[10], int[], false>();
    expect_is_nothrow_convertible<int[], int[10], false>();
}

struct A {
    A(const char*) {}
};

struct B {
    operator const char*() {
        return nullptr;
    }
};

struct C {
    operator const char*() const {
        return nullptr;
    }
};

struct D {
    explicit D(const char*) {}
};

struct E {
    explicit operator const char*() const {
        return nullptr;
    }
};

struct A2 {
    A2(const char*) noexcept {}
};

struct B2 {
    operator const char*() noexcept {
        return nullptr;
    }
};

struct C2 {
    operator const char*() const noexcept {
        return nullptr;
    }
};

struct D2 {
    explicit D2(const char*) noexcept {}
};

struct E2 {
    explicit operator const char*() const noexcept {
        return nullptr;
    }
};

TEST(user_defined) {
    expect_is_nothrow_convertible<A, const char*, false>();
    expect_is_nothrow_convertible<const A, const char*, false>();
    expect_is_nothrow_convertible<const char*, A, false>();

    expect_is_nothrow_convertible<B, const char*, false>();
    expect_is_nothrow_convertible<const B, const char*, false>();
    expect_is_nothrow_convertible<const char*, B, false>();

    expect_is_nothrow_convertible<C, const char*, false>();
    expect_is_nothrow_convertible<const C, const char*, false>();
    expect_is_nothrow_convertible<const char*, C, false>();

    expect_is_nothrow_convertible<D, const char*, false>();
    expect_is_nothrow_convertible<const D, const char*, false>();
    expect_is_nothrow_convertible<const char*, D, false>();

    expect_is_nothrow_convertible<E, const char*, false>();
    expect_is_nothrow_convertible<const E, const char*, false>();
    expect_is_nothrow_convertible<const char*, E, false>();

    expect_is_nothrow_convertible<A2, const char*, false>();
    expect_is_nothrow_convertible<const A2, const char*, false>();
    expect_is_nothrow_convertible<const char*, A2, true>();

    expect_is_nothrow_convertible<B2, const char*, true>();
    expect_is_nothrow_convertible<const B2, const char*, false>();
    expect_is_nothrow_convertible<const char*, B2, false>();

    expect_is_nothrow_convertible<C2, const char*, true>();
    expect_is_nothrow_convertible<const C2, const char*, true>();
    expect_is_nothrow_convertible<const char*, C2, false>();

    expect_is_nothrow_convertible<D2, const char*, false>();
    expect_is_nothrow_convertible<const D2, const char*, false>();
    expect_is_nothrow_convertible<const char*, D2, false>();

    expect_is_nothrow_convertible<E2, const char*, false>();
    expect_is_nothrow_convertible<const E2, const char*, false>();
    expect_is_nothrow_convertible<const char*, E2, false>();
}
