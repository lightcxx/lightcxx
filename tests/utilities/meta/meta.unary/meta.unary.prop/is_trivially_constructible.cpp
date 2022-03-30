#include <type_traits>

#include "meta/test_unary_trait.h"

template<bool e, class T, class... Args>
constexpr bool test_is_trivially_constructible() {
    bool b1 = std::is_base_of_v<std::bool_constant<e>, std::is_trivially_constructible<T, Args...>>;
    bool b2 = std::is_trivially_constructible<T, Args...>::value == e;
    bool b3 = std::is_same_v<typename std::is_trivially_constructible<T, Args...>::value_type, bool>;
    bool b4 = std::is_trivially_constructible<T, Args...>{} == e;
    bool b5 = (bool)std::is_trivially_constructible<T, Args...>{} == e;
    bool b6 = noexcept((bool)std::is_trivially_constructible<T, Args...>{});
    bool b7 = std::is_trivially_constructible<T, Args...>{}() == e;
    bool b8 = noexcept(std::is_trivially_constructible<T, Args...>{}());
    bool b9 = std::is_same_v<bool, decltype(std::is_trivially_constructible<T, Args...>{}())>;
    bool b10 = std::is_same_v<typename std::is_trivially_constructible<T, Args...>::type, std::bool_constant<e>>;
    bool b11 = std::is_same_v<decltype(std::is_trivially_constructible_v<T, Args...>), const bool>;
    bool b12 = std::is_trivially_constructible_v<T, Args...> == e;
    return b1 && b2 && b3 && b4 && b5 && b6 && b7 && b8 && b9 && b10 && b11 && b12;
}

template<class T>
struct ConvertsTo {
    operator T() {
        return T();
    }
};

struct Derived : public Class {};

struct NoDfltCtor {
    NoDfltCtor() = delete;
};

// region void
static_assert(test_is_trivially_constructible<false, void>());
static_assert(test_is_trivially_constructible<false, const void>());
static_assert(test_is_trivially_constructible<false, volatile void>());
static_assert(test_is_trivially_constructible<false, const volatile void>());
static_assert(test_is_trivially_constructible<false, void, void>());
static_assert(test_is_trivially_constructible<false, const void, void>());
static_assert(test_is_trivially_constructible<false, volatile void, void>());
static_assert(test_is_trivially_constructible<false, const volatile void, void>());
static_assert(test_is_trivially_constructible<false, void, int>());
static_assert(test_is_trivially_constructible<false, const void, int>());
static_assert(test_is_trivially_constructible<false, volatile void, int>());
static_assert(test_is_trivially_constructible<false, const volatile void, int>());
static_assert(test_is_trivially_constructible<false, void, int, int>());
static_assert(test_is_trivially_constructible<false, const void, int, int>());
static_assert(test_is_trivially_constructible<false, volatile void, int, int>());
static_assert(test_is_trivially_constructible<false, const volatile void, int, int>());
// endregion

// region scalar
template<class T, class U = T, bool is_union = false>
constexpr bool test_scalar_or_union() {
    static_assert(test_is_trivially_constructible<true, T>());
    static_assert(test_is_trivially_constructible<true, T, U>());
    static_assert(test_is_trivially_constructible<true, T, U&>());
    static_assert(test_is_trivially_constructible<true, T, U&&>());
    static_assert(test_is_trivially_constructible<true, T, const U>());
    static_assert(test_is_trivially_constructible<true, T, const U&>());
    static_assert(test_is_trivially_constructible<true, T, const U&&>());
    // Volatile unions can't be used for construction.
    static_assert(test_is_trivially_constructible<!is_union, T, volatile U>());
    static_assert(test_is_trivially_constructible<!is_union, T, volatile U&>());
    static_assert(test_is_trivially_constructible<!is_union, T, volatile U &&>());
    static_assert(test_is_trivially_constructible<!is_union, T, const volatile U>());
    static_assert(test_is_trivially_constructible<!is_union, T, const volatile U&>());
    static_assert(test_is_trivially_constructible<!is_union, T, const volatile U &&>());
    // With an implicit conversion
    static_assert(test_is_trivially_constructible<false, T, ConvertsTo<U>>());
    static_assert(test_is_trivially_constructible<false, T, ConvertsTo<U>&>());
    static_assert(test_is_trivially_constructible<false, T, ConvertsTo<U>&&>());

    static_assert(test_is_trivially_constructible<true, const T>());
    static_assert(test_is_trivially_constructible<true, const T, U>());
    static_assert(test_is_trivially_constructible<true, const T, U&>());
    static_assert(test_is_trivially_constructible<true, const T, U&&>());
    static_assert(test_is_trivially_constructible<true, const T, const U>());
    static_assert(test_is_trivially_constructible<true, const T, const U&>());
    static_assert(test_is_trivially_constructible<true, const T, const U&&>());
    // Volatile unions can't be used for construction.
    static_assert(test_is_trivially_constructible<!is_union, const T, volatile U>());
    static_assert(test_is_trivially_constructible<!is_union, const T, volatile U&>());
    static_assert(test_is_trivially_constructible<!is_union, const T, volatile U &&>());
    static_assert(test_is_trivially_constructible<!is_union, const T, const volatile U>());
    static_assert(test_is_trivially_constructible<!is_union, const T, const volatile U&>());
    static_assert(test_is_trivially_constructible<!is_union, const T, const volatile U &&>());
    // With an implicit conversion
    static_assert(test_is_trivially_constructible<false, const T, ConvertsTo<U>>());
    static_assert(test_is_trivially_constructible<false, const T, ConvertsTo<U>&>());
    static_assert(test_is_trivially_constructible<false, const T, ConvertsTo<U>&&>());

    static_assert(test_is_trivially_constructible<true, volatile T>());
    static_assert(test_is_trivially_constructible<true, volatile T, U>());
    static_assert(test_is_trivially_constructible<true, volatile T, U&>());
    static_assert(test_is_trivially_constructible<true, volatile T, U&&>());
    static_assert(test_is_trivially_constructible<true, volatile T, const U>());
    static_assert(test_is_trivially_constructible<true, volatile T, const U&>());
    static_assert(test_is_trivially_constructible<true, volatile T, const U&&>());
    // Volatile unions can't be used for construction.
    static_assert(test_is_trivially_constructible<!is_union, volatile T, volatile U>());
    static_assert(test_is_trivially_constructible<!is_union, volatile T, volatile U&>());
    static_assert(test_is_trivially_constructible<!is_union, volatile T, volatile U &&>());
    static_assert(test_is_trivially_constructible<!is_union, volatile T, const volatile U>());
    static_assert(test_is_trivially_constructible<!is_union, volatile T, const volatile U&>());
    static_assert(test_is_trivially_constructible<!is_union, volatile T, const volatile U &&>());
    // With an implicit conversion
    static_assert(test_is_trivially_constructible<false, volatile T, ConvertsTo<U>>());
    static_assert(test_is_trivially_constructible<false, volatile T, ConvertsTo<U>&>());
    static_assert(test_is_trivially_constructible<false, volatile T, ConvertsTo<U>&&>());

    static_assert(test_is_trivially_constructible<true, const volatile T>());
    static_assert(test_is_trivially_constructible<true, const volatile T, U>());
    static_assert(test_is_trivially_constructible<true, const volatile T, U&>());
    static_assert(test_is_trivially_constructible<true, const volatile T, U&&>());
    static_assert(test_is_trivially_constructible<true, const volatile T, const U>());
    static_assert(test_is_trivially_constructible<true, const volatile T, const U&>());
    static_assert(test_is_trivially_constructible<true, const volatile T, const U&&>());
    // Volatile unions can't be used for construction.
    static_assert(test_is_trivially_constructible<!is_union, const volatile T, volatile U>());
    static_assert(test_is_trivially_constructible<!is_union, const volatile T, volatile U&>());
    static_assert(test_is_trivially_constructible<!is_union, const volatile T, volatile U &&>());
    static_assert(test_is_trivially_constructible<!is_union, const volatile T, const volatile U>());
    static_assert(test_is_trivially_constructible<!is_union, const volatile T, const volatile U&>());
    static_assert(test_is_trivially_constructible<!is_union, const volatile T, const volatile U &&>());
    // With an implicit conversion
    static_assert(test_is_trivially_constructible<false, const volatile T, ConvertsTo<U>>());
    static_assert(test_is_trivially_constructible<false, const volatile T, ConvertsTo<U>&>());
    static_assert(test_is_trivially_constructible<false, const volatile T, ConvertsTo<U>&&>());

    // Bonkers arguments
    static_assert(test_is_trivially_constructible<false, T, Class>());
    static_assert(test_is_trivially_constructible<false, T, const Class&>());
    static_assert(test_is_trivially_constructible<false, T, Class, const Class&>());
    static_assert(test_is_trivially_constructible<false, const T, Class>());
    static_assert(test_is_trivially_constructible<false, const T, const Class&>());
    static_assert(test_is_trivially_constructible<false, const T, Class, const Class&>());
    static_assert(test_is_trivially_constructible<false, volatile T, Class>());
    static_assert(test_is_trivially_constructible<false, volatile T, const Class&>());
    static_assert(test_is_trivially_constructible<false, volatile T, Class, const Class&>());
    static_assert(test_is_trivially_constructible<false, const volatile T, Class>());
    static_assert(test_is_trivially_constructible<false, const volatile T, const Class&>());
    static_assert(test_is_trivially_constructible<false, const volatile T, Class, const Class&>());
    return true;
}
static_assert(test_scalar_or_union<decltype(nullptr)>());
static_assert(test_scalar_or_union<bool>());
static_assert(test_scalar_or_union<char>());
static_assert(test_scalar_or_union<char8_t>());
static_assert(test_scalar_or_union<char16_t>());
static_assert(test_scalar_or_union<char32_t>());
static_assert(test_scalar_or_union<wchar_t>());
static_assert(test_scalar_or_union<signed char>());
static_assert(test_scalar_or_union<short>());
static_assert(test_scalar_or_union<int>());
static_assert(test_scalar_or_union<long>());
static_assert(test_scalar_or_union<long long>());
static_assert(test_scalar_or_union<unsigned char>());
static_assert(test_scalar_or_union<unsigned short>());
static_assert(test_scalar_or_union<unsigned int>());
static_assert(test_scalar_or_union<unsigned long>());
static_assert(test_scalar_or_union<unsigned long long>());
static_assert(test_scalar_or_union<float>());
static_assert(test_scalar_or_union<double>());
static_assert(test_scalar_or_union<long double>());
static_assert(test_scalar_or_union<void*>());
static_assert(test_scalar_or_union<void*, decltype(nullptr)>());
static_assert(test_scalar_or_union<const void*>());
static_assert(test_scalar_or_union<volatile void*>());
static_assert(test_scalar_or_union<const volatile void*>());
static_assert(test_scalar_or_union<int*>());
static_assert(test_scalar_or_union<int**>());
static_assert(test_scalar_or_union<int***>());
static_assert(test_scalar_or_union<incomplete_type*>());
static_assert(test_scalar_or_union<int (*)(int)>());
static_assert(test_scalar_or_union<int (**)(int)>());
static_assert(test_is_trivially_constructible<false, int (*)(int), void (*)(long, int)>());
static_assert(test_scalar_or_union<Class*>());
static_assert(test_scalar_or_union<Class*, Derived*>());
static_assert(test_scalar_or_union<volatile Class*, Derived*>());
static_assert(test_scalar_or_union<volatile Class*, volatile Derived*>());
static_assert(test_scalar_or_union<const Class*, Derived*>());
static_assert(test_scalar_or_union<const Class*, const Derived*>());
static_assert(test_scalar_or_union<const volatile Class*, Derived*>());
static_assert(test_scalar_or_union<const volatile Class*, const volatile Derived*>());
static_assert(test_scalar_or_union<const volatile Class*, const Derived*>());
static_assert(test_scalar_or_union<const volatile Class*, volatile Derived*>());
static_assert(test_scalar_or_union<int Class::*>());
static_assert(test_is_trivially_constructible<false, int Class::*, Class Class::*>());
static_assert(test_scalar_or_union<Class Class::*>());
static_assert(test_scalar_or_union<Class * Class::*>());
static_assert(test_scalar_or_union<int (Class::*)(int, int)>());
static_assert(test_scalar_or_union<Class (Class::*)(int, Class Class::*)>());
static_assert(test_scalar_or_union<Class Class::* (Class::*)(int, int)>());
static_assert(test_is_trivially_constructible<false, int (Class::*)(int, int), Class Class::* (Class::*)(int, int)>());
static_assert(test_scalar_or_union<Enum>());
static_assert(test_scalar_or_union<EnumClass>());
static_assert(test_is_trivially_constructible<false, Enum, EnumClass>());
static_assert(test_is_trivially_constructible<false, EnumClass, Enum>());
// endregion

// region array
static_assert(test_is_trivially_constructible<true, int[10]>());
static_assert(test_is_trivially_constructible<true, int[10][10]>());
static_assert(test_is_trivially_constructible<true, int[10][10][10]>());
static_assert(test_is_trivially_constructible<true, Class[10]>());
static_assert(test_is_trivially_constructible<true, Class[10][10]>());
static_assert(test_is_trivially_constructible<true, Class[10][10][10]>());
static_assert(test_is_trivially_constructible<false, NoDfltCtor[10]>());
static_assert(test_is_trivially_constructible<false, NoDfltCtor[10][10]>());
static_assert(test_is_trivially_constructible<false, NoDfltCtor[10][10][10]>());
static_assert(test_is_trivially_constructible<false, int[1], int>());
static_assert(test_is_trivially_constructible<false, int[10], int>());
static_assert(test_is_trivially_constructible<false, int[10], int, int, int>());
static_assert(test_is_trivially_constructible<false, Class[1], Class>());
static_assert(test_is_trivially_constructible<false, Class[10], Class>());
static_assert(test_is_trivially_constructible<false, Class[10], Class, Class, Class>());
static_assert(test_is_trivially_constructible<false, int[]>());
static_assert(test_is_trivially_constructible<false, int[][10]>());
static_assert(test_is_trivially_constructible<false, int[][10][10]>());
static_assert(test_is_trivially_constructible<false, int[], int>());
static_assert(test_is_trivially_constructible<false, int[], int, int, int>());
static_assert(test_is_trivially_constructible<false, int[][10], int>());
static_assert(test_is_trivially_constructible<false, int[][1], int>());
static_assert(test_is_trivially_constructible<false, int[][10], int, int, int>());
// endregion

// region lvalue reference
static_assert(test_is_trivially_constructible<false, int&>());
static_assert(test_is_trivially_constructible<true, int&, int&>());
static_assert(test_is_trivially_constructible<false, int&, const int&>());
static_assert(test_is_trivially_constructible<false, int&, volatile int&>());
static_assert(test_is_trivially_constructible<false, int&, const volatile int&>());
static_assert(test_is_trivially_constructible<false, int&, int&&>());
static_assert(test_is_trivially_constructible<false, int&, const int&&>());
static_assert(test_is_trivially_constructible<false, int&, volatile int&&>());
static_assert(test_is_trivially_constructible<false, int&, const volatile int&&>());
static_assert(test_is_trivially_constructible<false, int&, int>());
static_assert(test_is_trivially_constructible<false, int&, const int>());
static_assert(test_is_trivially_constructible<false, int&, volatile int>());
static_assert(test_is_trivially_constructible<false, int&, const volatile int>());

static_assert(test_is_trivially_constructible<false, const int&>());
static_assert(test_is_trivially_constructible<true, const int&, int&>());
static_assert(test_is_trivially_constructible<true, const int&, const int&>());
static_assert(test_is_trivially_constructible<false, const int&, volatile int&>());
static_assert(test_is_trivially_constructible<false, const int&, const volatile int&>());
static_assert(test_is_trivially_constructible<true, const int&, int&&>());
static_assert(test_is_trivially_constructible<true, const int&, const int&&>());
static_assert(test_is_trivially_constructible<false, const int&, volatile int&&>());
static_assert(test_is_trivially_constructible<false, const int&, const volatile int&&>());
static_assert(test_is_trivially_constructible<true, const int&, int>());
static_assert(test_is_trivially_constructible<true, const int&, const int>());
static_assert(test_is_trivially_constructible<false, const int&, volatile int>());
static_assert(test_is_trivially_constructible<false, const int&, const volatile int>());

static_assert(test_is_trivially_constructible<false, volatile int&>());
static_assert(test_is_trivially_constructible<true, volatile int&, int&>());
static_assert(test_is_trivially_constructible<false, volatile int&, const int&>());
static_assert(test_is_trivially_constructible<true, volatile int&, volatile int&>());
static_assert(test_is_trivially_constructible<false, volatile int&, const volatile int&>());
static_assert(test_is_trivially_constructible<false, volatile int&, int&&>());
static_assert(test_is_trivially_constructible<false, volatile int&, const int&&>());
static_assert(test_is_trivially_constructible<false, volatile int&, volatile int&&>());
static_assert(test_is_trivially_constructible<false, volatile int&, const volatile int&&>());
static_assert(test_is_trivially_constructible<false, volatile int&, int>());
static_assert(test_is_trivially_constructible<false, volatile int&, const int>());
static_assert(test_is_trivially_constructible<false, volatile int&, volatile int>());
static_assert(test_is_trivially_constructible<false, volatile int&, const volatile int>());

static_assert(test_is_trivially_constructible<false, const volatile int&>());
static_assert(test_is_trivially_constructible<true, const volatile int&, int&>());
static_assert(test_is_trivially_constructible<true, const volatile int&, const int&>());
static_assert(test_is_trivially_constructible<true, const volatile int&, volatile int&>());
static_assert(test_is_trivially_constructible<true, const volatile int&, const volatile int&>());
static_assert(test_is_trivially_constructible<false, const volatile int&, int&&>());
static_assert(test_is_trivially_constructible<false, const volatile int&, const int&&>());
static_assert(test_is_trivially_constructible<false, const volatile int&, volatile int&&>());
static_assert(test_is_trivially_constructible<false, const volatile int&, const volatile int&&>());
static_assert(test_is_trivially_constructible<false, const volatile int&, int>());
static_assert(test_is_trivially_constructible<false, const volatile int&, const int>());
static_assert(test_is_trivially_constructible<false, const volatile int&, volatile int>());
static_assert(test_is_trivially_constructible<false, const volatile int&, const volatile int>());

static_assert(test_is_trivially_constructible<false, int (&)()>());
static_assert(test_is_trivially_constructible<true, int (&)(), int()>());
static_assert(test_is_trivially_constructible<false, int (&)(), int(int)>());
static_assert(test_is_trivially_constructible<true, int (&)(), int (&)()>());
static_assert(test_is_trivially_constructible<false, int (&)(), int (&)(int)>());
static_assert(test_is_trivially_constructible<true, int (&)(), int(&&)()>());
static_assert(test_is_trivially_constructible<false, int (&)(), int(&&)(int)>());

static_assert(test_is_trivially_constructible<true, Class&, Derived&>());
static_assert(test_is_trivially_constructible<false, Class&, const Derived&>());
static_assert(test_is_trivially_constructible<false, Class&, volatile Derived&>());
static_assert(test_is_trivially_constructible<false, Class&, const volatile Derived&>());
static_assert(test_is_trivially_constructible<true, volatile Class&, Derived&>());
static_assert(test_is_trivially_constructible<false, volatile Class&, const Derived&>());
static_assert(test_is_trivially_constructible<true, volatile Class&, volatile Derived&>());
static_assert(test_is_trivially_constructible<false, volatile Class&, const volatile Derived&>());
static_assert(test_is_trivially_constructible<true, const Class&, Derived&>());
static_assert(test_is_trivially_constructible<true, const Class&, const Derived&>());
static_assert(test_is_trivially_constructible<false, const Class&, volatile Derived&>());
static_assert(test_is_trivially_constructible<false, const Class&, const volatile Derived&>());
static_assert(test_is_trivially_constructible<true, const volatile Class&, Derived&>());
static_assert(test_is_trivially_constructible<true, const volatile Class&, const Derived&>());
static_assert(test_is_trivially_constructible<true, const volatile Class&, volatile Derived&>());
static_assert(test_is_trivially_constructible<true, const volatile Class&, const volatile Derived&>());

static_assert(test_is_trivially_constructible<false, Class&, Derived&&>());
static_assert(test_is_trivially_constructible<false, Class&, const Derived&&>());
static_assert(test_is_trivially_constructible<false, Class&, volatile Derived&&>());
static_assert(test_is_trivially_constructible<false, Class&, const volatile Derived&&>());
static_assert(test_is_trivially_constructible<false, volatile Class&, Derived&&>());
static_assert(test_is_trivially_constructible<false, volatile Class&, const Derived&&>());
static_assert(test_is_trivially_constructible<false, volatile Class&, volatile Derived&&>());
static_assert(test_is_trivially_constructible<false, volatile Class&, const volatile Derived&&>());
static_assert(test_is_trivially_constructible<true, const Class&, Derived&&>());
static_assert(test_is_trivially_constructible<true, const Class&, const Derived&&>());
static_assert(test_is_trivially_constructible<false, const Class&, volatile Derived&&>());
static_assert(test_is_trivially_constructible<false, const Class&, const volatile Derived&&>());
static_assert(test_is_trivially_constructible<false, const volatile Class&, Derived&&>());
static_assert(test_is_trivially_constructible<false, const volatile Class&, const Derived&&>());
static_assert(test_is_trivially_constructible<false, const volatile Class&, volatile Derived&&>());
static_assert(test_is_trivially_constructible<false, const volatile Class&, const volatile Derived&&>());
// endregion

// region rvalue reference
static_assert(test_is_trivially_constructible<false, int&&>());
static_assert(test_is_trivially_constructible<false, int&&, int&>());
static_assert(test_is_trivially_constructible<false, int&&, const int&>());
static_assert(test_is_trivially_constructible<false, int&&, volatile int&>());
static_assert(test_is_trivially_constructible<false, int&&, const volatile int&>());
static_assert(test_is_trivially_constructible<true, int&&, int&&>());
static_assert(test_is_trivially_constructible<false, int&&, const int&&>());
static_assert(test_is_trivially_constructible<false, int&&, volatile int&&>());
static_assert(test_is_trivially_constructible<false, int&&, const volatile int&&>());
static_assert(test_is_trivially_constructible<true, int&&, int>());
static_assert(test_is_trivially_constructible<false, int&&, const int>());
static_assert(test_is_trivially_constructible<false, int&&, volatile int>());
static_assert(test_is_trivially_constructible<false, int&&, const volatile int>());

static_assert(test_is_trivially_constructible<false, const int&&>());
static_assert(test_is_trivially_constructible<false, const int&&, int&>());
static_assert(test_is_trivially_constructible<false, const int&&, const int&>());
static_assert(test_is_trivially_constructible<false, const int&&, volatile int&>());
static_assert(test_is_trivially_constructible<false, const int&&, const volatile int&>());
static_assert(test_is_trivially_constructible<true, const int&&, int&&>());
static_assert(test_is_trivially_constructible<true, const int&&, const int&&>());
static_assert(test_is_trivially_constructible<false, const int&&, volatile int&&>());
static_assert(test_is_trivially_constructible<false, const int&&, const volatile int&&>());
static_assert(test_is_trivially_constructible<true, const int&&, int>());
static_assert(test_is_trivially_constructible<true, const int&&, const int>());
static_assert(test_is_trivially_constructible<false, const int&&, volatile int>());
static_assert(test_is_trivially_constructible<false, const int&&, const volatile int>());

static_assert(test_is_trivially_constructible<false, volatile int&&>());
static_assert(test_is_trivially_constructible<false, volatile int&&, int&>());
static_assert(test_is_trivially_constructible<false, volatile int&&, const int&>());
static_assert(test_is_trivially_constructible<false, volatile int&&, volatile int&>());
static_assert(test_is_trivially_constructible<false, volatile int&&, const volatile int&>());
static_assert(test_is_trivially_constructible<true, volatile int&&, int&&>());
static_assert(test_is_trivially_constructible<false, volatile int&&, const int&&>());
static_assert(test_is_trivially_constructible<true, volatile int&&, volatile int&&>());
static_assert(test_is_trivially_constructible<false, volatile int&&, const volatile int&&>());
static_assert(test_is_trivially_constructible<true, volatile int&&, int>());
static_assert(test_is_trivially_constructible<false, volatile int&&, const int>());
static_assert(test_is_trivially_constructible<true, volatile int&&, volatile int>());
static_assert(test_is_trivially_constructible<false, volatile int&&, const volatile int>());

static_assert(test_is_trivially_constructible<false, const volatile int&&>());
static_assert(test_is_trivially_constructible<false, const volatile int&&, int&>());
static_assert(test_is_trivially_constructible<false, const volatile int&&, const int&>());
static_assert(test_is_trivially_constructible<false, const volatile int&&, volatile int&>());
static_assert(test_is_trivially_constructible<false, const volatile int&&, const volatile int&>());
static_assert(test_is_trivially_constructible<true, const volatile int&&, int&&>());
static_assert(test_is_trivially_constructible<true, const volatile int&&, const int&&>());
static_assert(test_is_trivially_constructible<true, const volatile int&&, volatile int&&>());
static_assert(test_is_trivially_constructible<true, const volatile int&&, const volatile int&&>());
static_assert(test_is_trivially_constructible<true, const volatile int&&, int>());
static_assert(test_is_trivially_constructible<true, const volatile int&&, const int>());
static_assert(test_is_trivially_constructible<true, const volatile int&&, volatile int>());
static_assert(test_is_trivially_constructible<true, const volatile int&&, const volatile int>());

static_assert(test_is_trivially_constructible<false, int(&&)()>());
static_assert(test_is_trivially_constructible<true, int(&&)(), int()>());
static_assert(test_is_trivially_constructible<false, int(&&)(), int(int)>());
static_assert(test_is_trivially_constructible<true, int(&&)(), int (&)()>());
static_assert(test_is_trivially_constructible<false, int(&&)(), int (&)(int)>());
static_assert(test_is_trivially_constructible<true, int(&&)(), int(&&)()>());
static_assert(test_is_trivially_constructible<false, int(&&)(), int(&&)(int)>());

static_assert(test_is_trivially_constructible<false, Class&&, Derived&>());
static_assert(test_is_trivially_constructible<false, Class&&, const Derived&>());
static_assert(test_is_trivially_constructible<false, Class&&, volatile Derived&>());
static_assert(test_is_trivially_constructible<false, Class&&, const volatile Derived&>());
static_assert(test_is_trivially_constructible<false, volatile Class&&, Derived&>());
static_assert(test_is_trivially_constructible<false, volatile Class&&, const Derived&>());
static_assert(test_is_trivially_constructible<false, volatile Class&&, volatile Derived&>());
static_assert(test_is_trivially_constructible<false, volatile Class&&, const volatile Derived&>());
static_assert(test_is_trivially_constructible<false, const Class&&, Derived&>());
static_assert(test_is_trivially_constructible<false, const Class&&, const Derived&>());
static_assert(test_is_trivially_constructible<false, const Class&&, volatile Derived&>());
static_assert(test_is_trivially_constructible<false, const Class&&, const volatile Derived&>());
static_assert(test_is_trivially_constructible<false, const volatile Class&&, Derived&>());
static_assert(test_is_trivially_constructible<false, const volatile Class&&, const Derived&>());
static_assert(test_is_trivially_constructible<false, const volatile Class&&, volatile Derived&>());
static_assert(test_is_trivially_constructible<false, const volatile Class&&, const volatile Derived&>());

static_assert(test_is_trivially_constructible<true, Class&&, Derived&&>());
static_assert(test_is_trivially_constructible<false, Class&&, const Derived&&>());
static_assert(test_is_trivially_constructible<false, Class&&, volatile Derived&&>());
static_assert(test_is_trivially_constructible<false, Class&&, const volatile Derived&&>());
static_assert(test_is_trivially_constructible<true, volatile Class&&, Derived&&>());
static_assert(test_is_trivially_constructible<false, volatile Class&&, const Derived&&>());
static_assert(test_is_trivially_constructible<true, volatile Class&&, volatile Derived&&>());
static_assert(test_is_trivially_constructible<false, volatile Class&&, const volatile Derived&&>());
static_assert(test_is_trivially_constructible<true, const Class&&, Derived&&>());
static_assert(test_is_trivially_constructible<true, const Class&&, const Derived&&>());
static_assert(test_is_trivially_constructible<false, const Class&&, volatile Derived&&>());
static_assert(test_is_trivially_constructible<false, const Class&&, const volatile Derived&&>());
static_assert(test_is_trivially_constructible<true, const volatile Class&&, Derived&&>());
static_assert(test_is_trivially_constructible<true, const volatile Class&&, const Derived&&>());
static_assert(test_is_trivially_constructible<true, const volatile Class&&, volatile Derived&&>());
static_assert(test_is_trivially_constructible<true, const volatile Class&&, const volatile Derived&&>());
// endregion

// region union
static_assert(test_scalar_or_union<Union, Union, true>());
// endregion

// region class
static_assert(test_is_trivially_constructible<true, Class>());
static_assert(test_is_trivially_constructible<true, Class, Class>());
static_assert(test_is_trivially_constructible<true, Class, Class&>());
static_assert(test_is_trivially_constructible<true, Class, const Class&>());
static_assert(test_is_trivially_constructible<true, Class, Class&&>());

struct WithCtor {
    WithCtor(int);
    WithCtor(int, int);
    WithCtor(long, int) = delete;

  private:
    WithCtor(int, int, int);
};
static_assert(test_is_trivially_constructible<false, WithCtor, int>());
static_assert(test_is_trivially_constructible<false, WithCtor, const int&>());
static_assert(test_is_trivially_constructible<false, WithCtor, int&&>());
static_assert(test_is_trivially_constructible<false, WithCtor, long>());
static_assert(test_is_trivially_constructible<false, WithCtor, ConvertsTo<int>>());
static_assert(test_is_trivially_constructible<false, WithCtor, const long&>());
static_assert(test_is_trivially_constructible<false, WithCtor, int, int>());
static_assert(test_is_trivially_constructible<false, WithCtor, const int&, int>());
static_assert(test_is_trivially_constructible<false, WithCtor, int&&, int>());
static_assert(test_is_trivially_constructible<false, WithCtor, long, int>());
static_assert(test_is_trivially_constructible<false, WithCtor, const long&, int>());
static_assert(test_is_trivially_constructible<false, WithCtor, long, long>());
static_assert(test_is_trivially_constructible<false, WithCtor, int, int, int>());
static_assert(test_is_trivially_constructible<false, WithCtor, int, int, int>());

struct WithTrivialCtor {
    [[maybe_unused]] int x, y;

    WithTrivialCtor() = default;
    WithTrivialCtor(const WithTrivialCtor&) = default;
};
static_assert(test_is_trivially_constructible<true, WithTrivialCtor>());
static_assert(test_is_trivially_constructible<true, WithTrivialCtor, WithTrivialCtor>());
static_assert(test_is_trivially_constructible<true, WithTrivialCtor, WithTrivialCtor&>());
static_assert(test_is_trivially_constructible<true, WithTrivialCtor, WithTrivialCtor&&>());
static_assert(test_is_trivially_constructible<true, WithTrivialCtor, const WithTrivialCtor>());
static_assert(test_is_trivially_constructible<true, WithTrivialCtor, const WithTrivialCtor&>());
static_assert(test_is_trivially_constructible<true, WithTrivialCtor, const WithTrivialCtor&&>());
static_assert(test_is_trivially_constructible<false, WithTrivialCtor, int>());
static_assert(test_is_trivially_constructible<false, WithTrivialCtor, const int&>());
static_assert(test_is_trivially_constructible<false, WithTrivialCtor, int&&>());
static_assert(test_is_trivially_constructible<false, WithTrivialCtor, long>());
static_assert(test_is_trivially_constructible<false, WithTrivialCtor, ConvertsTo<int>>());
static_assert(test_is_trivially_constructible<false, WithTrivialCtor, const long&>());
static_assert(test_is_trivially_constructible<false, WithTrivialCtor, int, int>());
static_assert(test_is_trivially_constructible<false, WithTrivialCtor, const int&, int>());
static_assert(test_is_trivially_constructible<false, WithTrivialCtor, int&&, int>());
static_assert(test_is_trivially_constructible<false, WithTrivialCtor, long, int>());
static_assert(test_is_trivially_constructible<false, WithTrivialCtor, const long&, int>());
static_assert(test_is_trivially_constructible<false, WithTrivialCtor, long, long>());
static_assert(test_is_trivially_constructible<false, WithTrivialCtor, int, int, int>());
static_assert(test_is_trivially_constructible<false, WithTrivialCtor, int, int, int>());

struct WithNonTrivialCtor {
    [[maybe_unused]] int x, y;

    WithNonTrivialCtor() {}
    WithNonTrivialCtor(const WithNonTrivialCtor&) {}
};
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, WithNonTrivialCtor>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, WithNonTrivialCtor&>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, WithNonTrivialCtor&&>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, const WithNonTrivialCtor>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, const WithNonTrivialCtor&>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, const WithNonTrivialCtor&&>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, int>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, const int&>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, int&&>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, long>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, ConvertsTo<int>>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, const long&>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, int, int>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, const int&, int>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, int&&, int>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, long, int>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, const long&, int>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, long, long>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, int, int, int>());
static_assert(test_is_trivially_constructible<false, WithNonTrivialCtor, int, int, int>());

struct Abstract {
    virtual ~Abstract() = 0;
};

static_assert(test_is_trivially_constructible<false, Abstract>());
static_assert(test_is_trivially_constructible<false, Abstract, const Abstract&>());
static_assert(test_is_trivially_constructible<true, Class, Derived>());
static_assert(test_is_trivially_constructible<true, Class, const Derived&>());

// endregion

// region function
static_assert(test_is_trivially_constructible<false, int(), int()>());
static_assert(test_is_trivially_constructible<false, int(), int (&)()>());
static_assert(test_is_trivially_constructible<false, int(), int(&&)()>());
static_assert(test_is_trivially_constructible<false, int(), int(int, int)>());
static_assert(test_is_trivially_constructible<false, int(), int (&)(int, int)>());
static_assert(test_is_trivially_constructible<false, int(), int(&&)(int, int)>());
// endregion