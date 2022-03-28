#include <type_traits>

struct B {};
struct B1 : B {};

template<class Base, class Derived, bool e>
constexpr bool test_is_base_of() {
    static_assert(std::is_base_of<Base, Derived>::value == e);
    static_assert(std::is_base_of_v<std::bool_constant<e>, std::is_base_of<Base, Derived>>);
    static_assert(std::is_same_v<typename std::is_base_of<Base, Derived>::value_type, bool>);
    static_assert(std::is_base_of<Base, Derived>{} == e);
    static_assert((bool)std::is_base_of<Base, Derived>{} == e);
    static_assert(noexcept((bool)std::is_base_of<Base, Derived>{}));
    static_assert(std::is_base_of<Base, Derived>{}() == e);
    static_assert(noexcept(std::is_base_of<Base, Derived>{}()));
    static_assert(std::is_same_v<bool, decltype(std::is_base_of<Base, Derived>{}())>);
    static_assert(std::is_same_v<typename std::is_base_of<Base, Derived>::type, std::bool_constant<e>>);
    static_assert(std::is_same_v<decltype(std::is_base_of_v<Base, Derived>), const bool>);
    static_assert(std::is_base_of_v<Base, Derived> == e);
    return true;
}


template<class Base, class Derived, bool e>
constexpr bool test_all_cvs() {
    static_assert(test_is_base_of<Base, Derived, e>());
    static_assert(test_is_base_of<Base, const Derived, e>());
    static_assert(test_is_base_of<Base, volatile Derived, e>());
    static_assert(test_is_base_of<Base, const volatile Derived, e>());

    static_assert(test_is_base_of<const Base, Derived, e>());
    static_assert(test_is_base_of<const Base, const Derived, e>());
    static_assert(test_is_base_of<const Base, volatile Derived, e>());
    static_assert(test_is_base_of<const Base, const volatile Derived, e>());

    static_assert(test_is_base_of<volatile Base, Derived, e>());
    static_assert(test_is_base_of<volatile Base, const Derived, e>());
    static_assert(test_is_base_of<volatile Base, volatile Derived, e>());
    static_assert(test_is_base_of<volatile Base, const volatile Derived, e>());

    static_assert(test_is_base_of<const volatile Base, Derived, e>());
    static_assert(test_is_base_of<const volatile Base, const Derived, e>());
    static_assert(test_is_base_of<const volatile Base, volatile Derived, e>());
    static_assert(test_is_base_of<const volatile Base, const volatile Derived, e>());

    return true;
}

static_assert(test_all_cvs<B, B, true>());
static_assert(test_all_cvs<B, B1, true>());
static_assert(test_all_cvs<B1, B, false>());

static_assert(test_all_cvs<B*, B1, false>());
static_assert(test_all_cvs<B, B1*, false>());
static_assert(test_all_cvs<B*, B1*, false>());

static_assert(test_all_cvs<B&, B1, false>());
static_assert(test_all_cvs<B, B1&, false>());
static_assert(test_all_cvs<B&, B1&, false>());

static_assert(test_all_cvs<B&, B1*, false>());
static_assert(test_all_cvs<B*, B1&, false>());

static_assert(test_all_cvs<int, B, false>());
static_assert(test_all_cvs<B&, B*, false>());
static_assert(test_all_cvs<int, int, false>());

struct B_protected: protected B {};
static_assert(test_all_cvs<B, B_protected, true>());

struct B_private: private B {};
static_assert(test_all_cvs<B, B_private, true>());

struct B_virtual: virtual B {};
static_assert(test_all_cvs<B, B_virtual, true>());

// Examples provided in the standard draft
struct B2 : B {};
struct D : private B1, private B2 {};

static_assert(test_all_cvs<B, D, true>());
static_assert(!std::is_base_of_v<D, B>);
static_assert(!std::is_base_of_v<B&, D&>);
static_assert(!std::is_base_of_v<B[3], D[3]>);
static_assert(!std::is_base_of_v<int, int>);
