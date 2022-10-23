#include <concepts>

#include "testing.h"

template<class From, class To, bool e>
constexpr void expect_convertible_to() {
    static_assert(std::convertible_to<From, To> == e);
}

TEST(voids) {
    expect_convertible_to<void, void, true>();
    expect_convertible_to<const void, void, true>();
    expect_convertible_to<void, const void, true>();
    expect_convertible_to<const void, const void, true>();

    expect_convertible_to<void, int(), false>();
    expect_convertible_to<void, int (&)(), false>();
    expect_convertible_to<void, int (*)(), false>();
    expect_convertible_to<void, int[10], false>();
    expect_convertible_to<void, int(&)[10], false>();
    expect_convertible_to<void, int[], false>();
    expect_convertible_to<void, int, false>();
    expect_convertible_to<void, int&, false>();
    expect_convertible_to<void, int*, false>();
    expect_convertible_to<int, void, false>();
}

TEST(pointers) {
    // To same pointer
    expect_convertible_to<int*, int*, true>();
    expect_convertible_to<int*, const int*, true>();
    expect_convertible_to<int*, volatile int*, true>();
    expect_convertible_to<int*, const volatile int*, true>();
    expect_convertible_to<const int*, int*, false>();
    expect_convertible_to<const int*, const int*, true>();
    expect_convertible_to<const int*, volatile int*, false>();
    expect_convertible_to<const int*, const volatile int*, true>();
    expect_convertible_to<volatile int*, int*, false>();
    expect_convertible_to<volatile int*, const int*, false>();
    expect_convertible_to<volatile int*, volatile int*, true>();
    expect_convertible_to<volatile int*, const volatile int*, true>();
    expect_convertible_to<const volatile int*, int*, false>();
    expect_convertible_to<const volatile int*, const int*, false>();
    expect_convertible_to<const volatile int*, volatile int*, false>();
    expect_convertible_to<const volatile int*, const volatile int*, true>();

    // To void pointer
    expect_convertible_to<int*, void*, true>();
    expect_convertible_to<int*, const void*, true>();
    expect_convertible_to<int*, volatile void*, true>();
    expect_convertible_to<int*, const volatile void*, true>();
    expect_convertible_to<const int*, void*, false>();
    expect_convertible_to<const int*, const void*, true>();
    expect_convertible_to<const int*, volatile void*, false>();
    expect_convertible_to<const int*, const volatile void*, true>();
    expect_convertible_to<volatile int*, void*, false>();
    expect_convertible_to<volatile int*, const void*, false>();
    expect_convertible_to<volatile int*, volatile void*, true>();
    expect_convertible_to<volatile int*, const volatile void*, true>();
    expect_convertible_to<const volatile int*, void*, false>();
    expect_convertible_to<const volatile int*, const void*, false>();
    expect_convertible_to<const volatile int*, volatile void*, false>();
    expect_convertible_to<const volatile int*, const volatile void*, true>();

    // To pointer of compatible type
    expect_convertible_to<int*, long*, false>();
    expect_convertible_to<int*, const long*, false>();
    expect_convertible_to<int*, volatile long*, false>();
    expect_convertible_to<int*, const volatile long*, false>();
    expect_convertible_to<const int*, long*, false>();
    expect_convertible_to<const int*, const long*, false>();
    expect_convertible_to<const int*, volatile long*, false>();
    expect_convertible_to<const int*, const volatile long*, false>();
    expect_convertible_to<volatile int*, long*, false>();
    expect_convertible_to<volatile int*, const long*, false>();
    expect_convertible_to<volatile int*, volatile long*, false>();
    expect_convertible_to<volatile int*, const volatile long*, false>();
    expect_convertible_to<const volatile int*, long*, false>();
    expect_convertible_to<const volatile int*, const long*, false>();
    expect_convertible_to<const volatile int*, volatile long*, false>();
    expect_convertible_to<const volatile int*, const volatile long*, false>();
}

TEST(references) {
    // Lvalue to same lvalue ref
    expect_convertible_to<int&, int&, true>();
    expect_convertible_to<int&, const int&, true>();
    expect_convertible_to<int&, volatile int&, true>();
    expect_convertible_to<int&, const volatile int&, true>();
    expect_convertible_to<const int&, int&, false>();
    expect_convertible_to<const int&, const int&, true>();
    expect_convertible_to<const int&, volatile int&, false>();
    expect_convertible_to<const int&, const volatile int&, true>();
    expect_convertible_to<volatile int&, int&, false>();
    expect_convertible_to<volatile int&, const int&, false>();
    expect_convertible_to<volatile int&, volatile int&, true>();
    expect_convertible_to<volatile int&, const volatile int&, true>();
    expect_convertible_to<const volatile int&, int&, false>();
    expect_convertible_to<const volatile int&, const int&, false>();
    expect_convertible_to<const volatile int&, volatile int&, false>();
    expect_convertible_to<const volatile int&, const volatile int&, true>();

    // Lvalue to lvalue ref of compatible type
    expect_convertible_to<int&, long&, false>();
    expect_convertible_to<int&, const long&, true>();
    expect_convertible_to<int&, volatile long&, false>();
    expect_convertible_to<int&, const volatile long&, false>();
    expect_convertible_to<const int&, long&, false>();
    expect_convertible_to<const int&, const long&, true>();
    expect_convertible_to<const int&, volatile long&, false>();
    expect_convertible_to<const int&, const volatile long&, false>();
    expect_convertible_to<volatile int&, long&, false>();
    expect_convertible_to<volatile int&, const long&, true>();
    expect_convertible_to<volatile int&, volatile long&, false>();
    expect_convertible_to<volatile int&, const volatile long&, false>();
    expect_convertible_to<const volatile int&, long&, false>();
    expect_convertible_to<const volatile int&, const long&, true>();
    expect_convertible_to<const volatile int&, volatile long&, false>();
    expect_convertible_to<const volatile int&, const volatile long&, false>();

    // Rvalue to same lvalue ref
    expect_convertible_to<int&&, int&, false>();
    expect_convertible_to<int&&, const int&, true>();
    expect_convertible_to<int&&, volatile int&, false>();
    expect_convertible_to<int&&, const volatile int&, false>();
    expect_convertible_to<const int&&, int&, false>();
    expect_convertible_to<const int&&, const int&, true>();
    expect_convertible_to<const int&&, volatile int&, false>();
    expect_convertible_to<const int&&, const volatile int&, false>();
    expect_convertible_to<volatile int&&, int&, false>();
    expect_convertible_to<volatile int&&, const int&, false>();
    expect_convertible_to<volatile int&&, volatile int&, false>();
    expect_convertible_to<volatile int&&, const volatile int&, false>();
    expect_convertible_to<const volatile int&&, int&, false>();
    expect_convertible_to<const volatile int&&, const int&, false>();
    expect_convertible_to<const volatile int&&, volatile int&, false>();
    expect_convertible_to<const volatile int&&, const volatile int&, false>();

    // Rvalue to lvalue ref of compatible type
    expect_convertible_to<int&&, long&, false>();
    expect_convertible_to<int&&, const long&, true>();
    expect_convertible_to<int&&, volatile long&, false>();
    expect_convertible_to<int&&, const volatile long&, false>();
    expect_convertible_to<const int&&, long&, false>();
    expect_convertible_to<const int&&, const long&, true>();
    expect_convertible_to<const int&&, volatile long&, false>();
    expect_convertible_to<const int&&, const volatile long&, false>();
    expect_convertible_to<volatile int&&, long&, false>();
    expect_convertible_to<volatile int&&, const long&, true>();
    expect_convertible_to<volatile int&&, volatile long&, false>();
    expect_convertible_to<volatile int&&, const volatile long&, false>();
    expect_convertible_to<const volatile int&&, long&, false>();
    expect_convertible_to<const volatile int&&, const long&, true>();
    expect_convertible_to<const volatile int&&, volatile long&, false>();
    expect_convertible_to<const volatile int&&, const volatile long&, false>();

    // Lvalue to same rvalue ref
    expect_convertible_to<int&, int&&, false>();
    expect_convertible_to<int&, const int&&, false>();
    expect_convertible_to<int&, volatile int&&, false>();
    expect_convertible_to<int&, const volatile int&&, false>();
    expect_convertible_to<const int&, int&&, false>();
    expect_convertible_to<const int&, const int&&, false>();
    expect_convertible_to<const int&, volatile int&&, false>();
    expect_convertible_to<const int&, const volatile int&&, false>();
    expect_convertible_to<volatile int&, int&&, false>();
    expect_convertible_to<volatile int&, const int&&, false>();
    expect_convertible_to<volatile int&, volatile int&&, false>();
    expect_convertible_to<volatile int&, const volatile int&&, false>();
    expect_convertible_to<const volatile int&, int&&, false>();
    expect_convertible_to<const volatile int&, const int&&, false>();
    expect_convertible_to<const volatile int&, volatile int&&, false>();
    expect_convertible_to<const volatile int&, const volatile int&&, false>();

    // Lvalue to rvalue ref of compatible type
    expect_convertible_to<int&, long&&, true>();
    expect_convertible_to<int&, const long&&, true>();
    expect_convertible_to<int&, volatile long&&, true>();
    expect_convertible_to<int&, const volatile long&&, true>();
    expect_convertible_to<const int&, long&&, true>();
    expect_convertible_to<const int&, const long&&, true>();
    expect_convertible_to<const int&, volatile long&&, true>();
    expect_convertible_to<const int&, const volatile long&&, true>();
    expect_convertible_to<volatile int&, long&&, true>();
    expect_convertible_to<volatile int&, const long&&, true>();
    expect_convertible_to<volatile int&, volatile long&&, true>();
    expect_convertible_to<volatile int&, const volatile long&&, true>();
    expect_convertible_to<const volatile int&, long&&, true>();
    expect_convertible_to<const volatile int&, const long&&, true>();
    expect_convertible_to<const volatile int&, volatile long&&, true>();
    expect_convertible_to<const volatile int&, const volatile long&&, true>();

    // Rvalue to same rvalue ref
    expect_convertible_to<int&&, int&&, true>();
    expect_convertible_to<int&&, const int&&, true>();
    expect_convertible_to<int&&, volatile int&&, true>();
    expect_convertible_to<int&&, const volatile int&&, true>();
    expect_convertible_to<const int&&, int&&, false>();
    expect_convertible_to<const int&&, const int&&, true>();
    expect_convertible_to<const int&&, volatile int&&, false>();
    expect_convertible_to<const int&&, const volatile int&&, true>();
    expect_convertible_to<volatile int&&, int&&, false>();
    expect_convertible_to<volatile int&&, const int&&, false>();
    expect_convertible_to<volatile int&&, volatile int&&, true>();
    expect_convertible_to<volatile int&&, const volatile int&&, true>();
    expect_convertible_to<const volatile int&&, int&&, false>();
    expect_convertible_to<const volatile int&&, const int&&, false>();
    expect_convertible_to<const volatile int&&, volatile int&&, false>();
    expect_convertible_to<const volatile int&&, const volatile int&&, true>();

    // Rvalue to rvalue ref of compatible type
    expect_convertible_to<int&&, long&&, true>();
    expect_convertible_to<int&&, const long&&, true>();
    expect_convertible_to<int&&, volatile long&&, true>();
    expect_convertible_to<int&&, const volatile long&&, true>();
    expect_convertible_to<const int&&, long&&, true>();
    expect_convertible_to<const int&&, const long&&, true>();
    expect_convertible_to<const int&&, volatile long&&, true>();
    expect_convertible_to<const int&&, const volatile long&&, true>();
    expect_convertible_to<volatile int&&, long&&, true>();
    expect_convertible_to<volatile int&&, const long&&, true>();
    expect_convertible_to<volatile int&&, volatile long&&, true>();
    expect_convertible_to<volatile int&&, const volatile long&&, true>();
    expect_convertible_to<const volatile int&&, long&&, true>();
    expect_convertible_to<const volatile int&&, const long&&, true>();
    expect_convertible_to<const volatile int&&, volatile long&&, true>();
    expect_convertible_to<const volatile int&&, const volatile long&&, true>();
}

TEST(value) {
    expect_convertible_to<int&, int, true>();
    expect_convertible_to<const int&, int, true>();
    expect_convertible_to<volatile int&, int, true>();
    expect_convertible_to<const volatile int&, int, true>();
    expect_convertible_to<int&&, int, true>();
    expect_convertible_to<const int&&, int, true>();
    expect_convertible_to<volatile int&&, int, true>();
    expect_convertible_to<const volatile int&&, int, true>();

    expect_convertible_to<int, int&, false>();
    expect_convertible_to<int, const int&, true>();
    expect_convertible_to<int, volatile int&, false>();
    expect_convertible_to<int, const volatile int&, false>();
    expect_convertible_to<int, int&&, true>();
    expect_convertible_to<int, const int&&, true>();
    expect_convertible_to<int, volatile int&&, true>();
    expect_convertible_to<int, const volatile int&&, true>();
}

TEST(function) {
    expect_convertible_to<int(), int (*)(), true>();
    expect_convertible_to<int (*)(), int(), false>();

    expect_convertible_to<int(), int (&)(), true>();
    expect_convertible_to<int (&)(), int(), false>();

    expect_convertible_to<int(), int (&&)(), true>();
    expect_convertible_to<int (&&)(), int(), false>();

    expect_convertible_to<int (&)(), int (*)(), true>();
    expect_convertible_to<int (*)(), int (&)(), false>();

    expect_convertible_to<int (&)(), int (&&)(), true>();
    expect_convertible_to<int (&&)(), int (&)(), true>();

    expect_convertible_to<int (&&)(), int (*)(), true>();
    expect_convertible_to<int (*)(), int (&&)(), false>();
}

TEST(array) {
    expect_convertible_to<int[10], int*, true>();
    expect_convertible_to<int*, int[10], false>();

    expect_convertible_to<int[], int*, true>();
    expect_convertible_to<int*, int[], false>();

    expect_convertible_to<int[10], int[], false>();
    expect_convertible_to<int[], int[10], false>();
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

TEST(user_defined) {
    expect_convertible_to<A, const char*, false>();
    expect_convertible_to<const A, const char*, false>();
    expect_convertible_to<const char*, A, true>();

    expect_convertible_to<B, const char*, true>();
    expect_convertible_to<const B, const char*, false>();
    expect_convertible_to<const char*, B, false>();

    expect_convertible_to<C, const char*, true>();
    expect_convertible_to<const C, const char*, true>();
    expect_convertible_to<const char*, C, false>();

    expect_convertible_to<D, const char*, false>();
    expect_convertible_to<const D, const char*, false>();
    expect_convertible_to<const char*, D, false>();

    expect_convertible_to<E, const char*, false>();
    expect_convertible_to<const E, const char*, false>();
    expect_convertible_to<const char*, E, false>();
}
