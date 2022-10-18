#ifndef TESTING_TEST_UNARY_TRAIT_H
#define TESTING_TEST_UNARY_TRAIT_H

#include <type_traits>

using NullptrT = decltype(nullptr);

struct Class {
    int x[2];
    char y[4];
};

union Union {
    int x[2];
    char y[4];
};

enum Enum {
    e_ok,
    e_error,
};

enum class EnumClass {
    ok,
    error,
};

struct incomplete_type;

#define DECLARE_TRAIT_V_READER(TRAIT)                                    \
    template<class T>                                                    \
    struct TRAIT##_reader {                                              \
        constexpr auto read() const noexcept { return ::std::TRAIT<T>; } \
    }

template<template<class> class Trait, template<class> class Trait_v_reader, bool e, class T>
constexpr bool test_unary_trait_against_type_NO_CV() {
    constexpr auto reader = Trait_v_reader<T>{};
    static_assert(Trait<T>::value == e);
    static_assert(std::is_base_of_v<std::bool_constant<e>, Trait<T>>);
    static_assert(std::is_same_v<typename Trait<T>::value_type, bool>);
    static_assert(Trait<T>{} == e);
    static_assert(static_cast<bool>(Trait<T>{}) == e);
    static_assert(noexcept(static_cast<bool>(Trait<T>{})));
    static_assert(Trait<T>{}() == e);
    static_assert(noexcept(Trait<T>{}()));
    static_assert(std::is_same_v<bool, decltype(Trait<T>{}())>);
    static_assert(std::is_same_v<typename Trait<T>::type, std::bool_constant<e>>);
    static_assert(std::is_same_v<decltype(reader.read()), bool>);
    static_assert(reader.read() == e);
    return true;
}

template<template<class> class Trait, template<class> class Trait_v_reader, bool e, class T1, class T2, class... Ts>
constexpr bool test_unary_trait_against_type_NO_CV() {
    return test_unary_trait_against_type_NO_CV<Trait, Trait_v_reader, e, T1>() && test_unary_trait_against_type_NO_CV<Trait, Trait_v_reader, e, T2>()
           && (test_unary_trait_against_type_NO_CV<Trait, Trait_v_reader, e, Ts>() && ...);
}

template<template<class> class Trait, template<class> class Trait_v_reader, bool e, class T>
constexpr bool test_unary_trait_against_type_CONST() {
    return test_unary_trait_against_type_NO_CV<Trait, Trait_v_reader, e, T const>();
}

template<template<class> class Trait, template<class> class Trait_v_reader, bool e, class T1, class T2, class... Ts>
constexpr bool test_unary_trait_against_type_CONST() {
    return test_unary_trait_against_type_CONST<Trait, Trait_v_reader, e, T1>() && test_unary_trait_against_type_CONST<Trait, Trait_v_reader, e, T2>()
           && (test_unary_trait_against_type_CONST<Trait, Trait_v_reader, e, Ts>() && ...);
}

template<template<class> class Trait, template<class> class Trait_v_reader, bool e, class T>
constexpr bool test_unary_trait_against_type_VOLATILE() {
    return test_unary_trait_against_type_NO_CV<Trait, Trait_v_reader, e, T volatile>();
}

template<template<class> class Trait, template<class> class Trait_v_reader, bool e, class T1, class T2, class... Ts>
constexpr bool test_unary_trait_against_type_VOLATILE() {
    return test_unary_trait_against_type_VOLATILE<Trait, Trait_v_reader, e, T1>() && test_unary_trait_against_type_VOLATILE<Trait, Trait_v_reader, e, T2>()
           && (test_unary_trait_against_type_VOLATILE<Trait, Trait_v_reader, e, Ts>() && ...);
}

template<template<class> class Trait, template<class> class Trait_v_reader, bool e, class T>
constexpr bool test_unary_trait_against_type_CONST_VOLATILE() {
    return test_unary_trait_against_type_NO_CV<Trait, Trait_v_reader, e, T const volatile>();
}

template<template<class> class Trait, template<class> class Trait_v_reader, bool e, class T1, class T2, class... Ts>
constexpr bool test_unary_trait_against_type_CONST_VOLATILE() {
    return test_unary_trait_against_type_CONST_VOLATILE<Trait, Trait_v_reader, e, T1>()
           && test_unary_trait_against_type_CONST_VOLATILE<Trait, Trait_v_reader, e, T2>()
           && (test_unary_trait_against_type_CONST_VOLATILE<Trait, Trait_v_reader, e, Ts>() && ...);
}

template<template<class> class Trait, template<class> class Trait_v_reader, bool e, class T>
constexpr bool test_unary_trait_against_type_EVERY_CV() {
    static_assert(test_unary_trait_against_type_NO_CV<Trait, Trait_v_reader, e, T>());
    static_assert(test_unary_trait_against_type_CONST<Trait, Trait_v_reader, e, T>());
    static_assert(test_unary_trait_against_type_VOLATILE<Trait, Trait_v_reader, e, T>());
    static_assert(test_unary_trait_against_type_CONST_VOLATILE<Trait, Trait_v_reader, e, T>());
    return true;
}

template<template<class> class Trait, template<class> class Trait_v_reader, bool e, class T1, class T2, class... Ts>
constexpr bool test_unary_trait_against_type_EVERY_CV() {
    return test_unary_trait_against_type_EVERY_CV<Trait, Trait_v_reader, e, T1>() && test_unary_trait_against_type_EVERY_CV<Trait, Trait_v_reader, e, T2>()
           && (test_unary_trait_against_type_EVERY_CV<Trait, Trait_v_reader, e, Ts>() && ...);
}

template<template<class> class Trait, template<class> class Trait_v_reader, class T, std::size_t e>
constexpr bool test_unary_prop_query() {
    static_assert(Trait<T>::value == e);
    static_assert(std::is_base_of_v<std::integral_constant<std::size_t, e>, Trait<T>>);
    static_assert(std::is_same_v<typename Trait<T>::value_type, std::size_t>);
    static_assert(Trait<T>{} == e);
    static_assert(static_cast<std::size_t>(Trait<T>{}) == e);
    static_assert(noexcept(static_cast<std::size_t>(Trait<T>{})));
    static_assert(Trait<T>{}() == e);
    static_assert(noexcept(Trait<T>{}()));
    static_assert(std::is_same_v<std::size_t, decltype(Trait<T>{}())>);
    static_assert(std::is_same_v<typename Trait<T>::type, std::integral_constant<std::size_t, e>>);
    constexpr auto reader = Trait_v_reader<T>{};
    static_assert(std::is_same_v<decltype(reader.read()), std::size_t>);
    static_assert(reader.read() == e);
    return true;
}

#define TEST_UNARY_TRAIT_AGAINST_TYPES(EXPECTED, TRAIT, SUFFIX, ...) \
    static_assert(test_unary_trait_against_type_##SUFFIX<std::TRAIT, TRAIT##_v_reader, EXPECTED, __VA_ARGS__>())

#define TEST_UNARY_TRAIT_AGAINST_VOID(EXPECTED, TRAIT, SUFFIX) TEST_UNARY_TRAIT_AGAINST_TYPES(EXPECTED, TRAIT, SUFFIX, void)

#define TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(EXPECTED, TRAIT, SUFFIX) TEST_UNARY_TRAIT_AGAINST_TYPES(EXPECTED, TRAIT, SUFFIX, NullptrT)

#define TEST_UNARY_TRAIT_AGAINST_INTEGRAL(EXPECTED, TRAIT, SUFFIX)                                                                                   \
    TEST_UNARY_TRAIT_AGAINST_TYPES(EXPECTED, TRAIT, SUFFIX, bool, char, char8_t, char16_t, char32_t, wchar_t, signed char, short int, int, long int, \
                                   long long int, unsigned char, unsigned short int, unsigned int, unsigned long int, unsigned long long int)

#define TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(EXPECTED, TRAIT, SUFFIX) TEST_UNARY_TRAIT_AGAINST_TYPES(EXPECTED, TRAIT, SUFFIX, float, double, long double)

#define TEST_UNARY_TRAIT_AGAINST_ARRAY(EXPECTED, TRAIT, SUFFIX) \
    TEST_UNARY_TRAIT_AGAINST_TYPES(EXPECTED, TRAIT, SUFFIX, int[10], int[10][10], int[], int[][10], int[][10][10])

#define TEST_UNARY_TRAIT_AGAINST_POINTER(EXPECTED, TRAIT, SUFFIX)                                                                                            \
    TEST_UNARY_TRAIT_AGAINST_TYPES(EXPECTED, TRAIT, SUFFIX, void*, const void*, volatile void*, const volatile void*, int*, int**, int***, incomplete_type*, \
                                   int (**)(int), int (*)(int))

#define TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(EXPECTED, TRAIT)                                                                                 \
    TEST_UNARY_TRAIT_AGAINST_TYPES(EXPECTED, TRAIT, NO_CV, int&, const int&, volatile int&, const volatile int&, int (&)(int), int*&, int* const&, \
                                   int* volatile&, int* const volatile&, incomplete_type&, const incomplete_type&, volatile incomplete_type&,      \
                                   const volatile incomplete_type&)

#define TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(EXPECTED, TRAIT)                                                                                        \
    TEST_UNARY_TRAIT_AGAINST_TYPES(EXPECTED, TRAIT, NO_CV, int&&, const int&&, volatile int&&, const volatile int&&, int (&&)(int), int*&&, int* const&&, \
                                   int* volatile&&, int* const volatile&&, incomplete_type&&, const incomplete_type&&, volatile incomplete_type&&,        \
                                   const volatile incomplete_type&&)

#define TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(EXPECTED, TRAIT, SUFFIX) \
    TEST_UNARY_TRAIT_AGAINST_TYPES(EXPECTED, TRAIT, SUFFIX, int Class::*, Class Class::*, Class* Class::*)

#define TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(EXPECTED, TRAIT, SUFFIX)                                            \
    TEST_UNARY_TRAIT_AGAINST_TYPES(EXPECTED, TRAIT, SUFFIX, int (Class::*)(int, int), Class (Class::*)(int, Class Class::*), \
                                   Class Class::* (Class::*)(int, int))

#define TEST_UNARY_TRAIT_AGAINST_ENUM(EXPECTED, TRAIT, SUFFIX) TEST_UNARY_TRAIT_AGAINST_TYPES(EXPECTED, TRAIT, SUFFIX, Enum, EnumClass)

#define TEST_UNARY_TRAIT_AGAINST_UNION(EXPECTED, TRAIT, SUFFIX) TEST_UNARY_TRAIT_AGAINST_TYPES(EXPECTED, TRAIT, SUFFIX, Union)

#define TEST_UNARY_TRAIT_AGAINST_CLASS(EXPECTED, TRAIT, SUFFIX) TEST_UNARY_TRAIT_AGAINST_TYPES(EXPECTED, TRAIT, SUFFIX, Class)

#define TEST_UNARY_TRAIT_AGAINST_FUNCTION(EXPECTED, TRAIT) \
    TEST_UNARY_TRAIT_AGAINST_TYPES(EXPECTED, TRAIT, NO_CV, void(), int(), int(int), int(int, int), int(int()), int(...), int() noexcept)

#endif
