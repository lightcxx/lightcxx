#include <type_traits>

#include "meta/test_unary_trait.h"

template<bool e, class T, class U = T>
constexpr bool test_is_trivially_assignable() {
    bool b1 = std::is_base_of_v<std::bool_constant<e>, std::is_trivially_assignable<T, U>>;
    bool b2 = std::is_trivially_assignable<T, U>::value == e;
    bool b3 = std::is_same_v<typename std::is_trivially_assignable<T, U>::value_type, bool>;
    bool b4 = std::is_trivially_assignable<T, U>{} == e;
    bool b5 = static_cast<bool>(std::is_trivially_assignable<T, U>{}) == e;
    bool b6 = noexcept(static_cast<bool>(std::is_trivially_assignable<T, U>{}));
    bool b7 = std::is_trivially_assignable<T, U>{}() == e;
    bool b8 = noexcept(std::is_trivially_assignable<T, U>{}());
    bool b9 = std::is_same_v<bool, decltype(std::is_trivially_assignable<T, U>{}())>;
    bool b10 = std::is_same_v<typename std::is_trivially_assignable<T, U>::type, std::bool_constant<e>>;
    bool b11 = std::is_same_v<decltype(std::is_trivially_assignable_v<T, U>), const bool>;
    bool b12 = std::is_trivially_assignable_v<T, U> == e;
    return b1 && b2 && b3 && b4 && b5 && b6 && b7 && b8 && b9 && b10 && b11 && b12;
}

template<class T>
struct ConvertsTo {
    operator T() {
        return T();
    }
};

struct Derived : public Class {};

struct WithAssignOp {
    WithAssignOp& operator=(int);
    void operator=(double);
    WithAssignOp& operator=(long) = delete;
};

// region void
static_assert(test_is_trivially_assignable<false, void, void>());
static_assert(test_is_trivially_assignable<false, void, const void>());
static_assert(test_is_trivially_assignable<false, void, volatile void>());
static_assert(test_is_trivially_assignable<false, void, const volatile void>());
static_assert(test_is_trivially_assignable<false, const void, void>());
static_assert(test_is_trivially_assignable<false, const void, const void>());
static_assert(test_is_trivially_assignable<false, const void, volatile void>());
static_assert(test_is_trivially_assignable<false, const void, const volatile void>());
static_assert(test_is_trivially_assignable<false, volatile void, void>());
static_assert(test_is_trivially_assignable<false, volatile void, const void>());
static_assert(test_is_trivially_assignable<false, volatile void, volatile void>());
static_assert(test_is_trivially_assignable<false, volatile void, const volatile void>());
static_assert(test_is_trivially_assignable<false, const volatile void, void>());
static_assert(test_is_trivially_assignable<false, const volatile void, const void>());
static_assert(test_is_trivially_assignable<false, const volatile void, volatile void>());
static_assert(test_is_trivially_assignable<false, const volatile void, const volatile void>());
// endregion

// region scalar
template<class T, class U = T, bool is_union = false>
constexpr bool test_scalar_or_union() {
    static_assert(test_is_trivially_assignable<is_union, T>());
    static_assert(test_is_trivially_assignable<is_union, T, U>());
    static_assert(test_is_trivially_assignable<is_union, T, U&>());
    static_assert(test_is_trivially_assignable<is_union, T, U&&>());
    static_assert(test_is_trivially_assignable<is_union, T, const U>());
    static_assert(test_is_trivially_assignable<is_union, T, const U&>());
    static_assert(test_is_trivially_assignable<is_union, T, const U&&>());

    static_assert(test_is_trivially_assignable<false, T, volatile U>());
    static_assert(test_is_trivially_assignable<false, T, volatile U&>());
    static_assert(test_is_trivially_assignable<false, T, volatile U&&>());
    static_assert(test_is_trivially_assignable<false, T, const volatile U>());
    static_assert(test_is_trivially_assignable<false, T, const volatile U&>());
    static_assert(test_is_trivially_assignable<false, T, const volatile U&&>());
    // With an implicit conversion
    static_assert(test_is_trivially_assignable<false, T, ConvertsTo<U>>());
    static_assert(test_is_trivially_assignable<false, T, ConvertsTo<U>&>());
    static_assert(test_is_trivially_assignable<false, T, ConvertsTo<U>&&>());

    // Const variables can't be assigned
    static_assert(test_is_trivially_assignable<false, const T>());
    static_assert(test_is_trivially_assignable<false, const T, U>());
    static_assert(test_is_trivially_assignable<false, const T, U&>());
    static_assert(test_is_trivially_assignable<false, const T, U&&>());
    static_assert(test_is_trivially_assignable<false, const T, const U>());
    static_assert(test_is_trivially_assignable<false, const T, const U&>());
    static_assert(test_is_trivially_assignable<false, const T, const U&&>());
    static_assert(test_is_trivially_assignable<false, const T, volatile U>());
    static_assert(test_is_trivially_assignable<false, const T, volatile U&>());
    static_assert(test_is_trivially_assignable<false, const T, volatile U&&>());
    static_assert(test_is_trivially_assignable<false, const T, const volatile U>());
    static_assert(test_is_trivially_assignable<false, const T, const volatile U&>());
    static_assert(test_is_trivially_assignable<false, const T, const volatile U&&>());
    static_assert(test_is_trivially_assignable<false, const T, ConvertsTo<U>>());
    static_assert(test_is_trivially_assignable<false, const T, ConvertsTo<U>&>());
    static_assert(test_is_trivially_assignable<false, const T, ConvertsTo<U>&&>());

    static_assert(test_is_trivially_assignable<false, volatile T>());
    static_assert(test_is_trivially_assignable<false, volatile T, U>());
    static_assert(test_is_trivially_assignable<false, volatile T, U&>());
    static_assert(test_is_trivially_assignable<false, volatile T, U&&>());
    static_assert(test_is_trivially_assignable<false, volatile T, const U>());
    static_assert(test_is_trivially_assignable<false, volatile T, const U&>());
    static_assert(test_is_trivially_assignable<false, volatile T, const U&&>());
    static_assert(test_is_trivially_assignable<false, volatile T, volatile U>());
    static_assert(test_is_trivially_assignable<false, volatile T, volatile U&>());
    static_assert(test_is_trivially_assignable<false, volatile T, volatile U&&>());
    static_assert(test_is_trivially_assignable<false, volatile T, const volatile U>());
    static_assert(test_is_trivially_assignable<false, volatile T, const volatile U&>());
    static_assert(test_is_trivially_assignable<false, volatile T, const volatile U&&>());
    // With an implicit conversion
    static_assert(test_is_trivially_assignable<false, volatile T, ConvertsTo<U>>());
    static_assert(test_is_trivially_assignable<false, volatile T, ConvertsTo<U>&>());
    static_assert(test_is_trivially_assignable<false, volatile T, ConvertsTo<U>&&>());

    // Const variables can't be assigned
    static_assert(test_is_trivially_assignable<false, const volatile T>());
    static_assert(test_is_trivially_assignable<false, const volatile T, U>());
    static_assert(test_is_trivially_assignable<false, const volatile T, U&>());
    static_assert(test_is_trivially_assignable<false, const volatile T, U&&>());
    static_assert(test_is_trivially_assignable<false, const volatile T, const U>());
    static_assert(test_is_trivially_assignable<false, const volatile T, const U&>());
    static_assert(test_is_trivially_assignable<false, const volatile T, const U&&>());
    static_assert(test_is_trivially_assignable<false, const volatile T, volatile U>());
    static_assert(test_is_trivially_assignable<false, const volatile T, volatile U&>());
    static_assert(test_is_trivially_assignable<false, const volatile T, volatile U&&>());
    static_assert(test_is_trivially_assignable<false, const volatile T, const volatile U>());
    static_assert(test_is_trivially_assignable<false, const volatile T, const volatile U&>());
    static_assert(test_is_trivially_assignable<false, const volatile T, const volatile U&&>());
    static_assert(test_is_trivially_assignable<false, const volatile T, ConvertsTo<U>>());
    static_assert(test_is_trivially_assignable<false, const volatile T, ConvertsTo<U>&>());
    static_assert(test_is_trivially_assignable<false, const volatile T, ConvertsTo<U>&&>());

    // Bonkers arguments
    static_assert(test_is_trivially_assignable<false, T, Class>());
    static_assert(test_is_trivially_assignable<false, T, const Class&>());
    static_assert(test_is_trivially_assignable<false, const T, Class>());
    static_assert(test_is_trivially_assignable<false, const T, const Class&>());
    static_assert(test_is_trivially_assignable<false, volatile T, Class>());
    static_assert(test_is_trivially_assignable<false, volatile T, const Class&>());
    static_assert(test_is_trivially_assignable<false, const volatile T, Class>());
    static_assert(test_is_trivially_assignable<false, const volatile T, const Class&>());
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
static_assert(test_is_trivially_assignable<false, int (*)(int), void (*)(long, int)>());
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
static_assert(test_is_trivially_assignable<false, int Class::*, Class Class::*>());
static_assert(test_scalar_or_union<Class Class::*>());
static_assert(test_scalar_or_union<Class * Class::*>());
static_assert(test_scalar_or_union<int (Class::*)(int, int)>());
static_assert(test_scalar_or_union<Class (Class::*)(int, Class Class::*)>());
static_assert(test_scalar_or_union<Class Class::* (Class::*)(int, int)>());
static_assert(test_is_trivially_assignable<false, int (Class::*)(int, int), Class Class::* (Class::*)(int, int)>());
static_assert(test_scalar_or_union<Enum>());
static_assert(test_scalar_or_union<EnumClass>());
static_assert(test_is_trivially_assignable<false, Enum, EnumClass>());
static_assert(test_is_trivially_assignable<false, EnumClass, Enum>());
// endregion

// region array
static_assert(test_is_trivially_assignable<false, int[10]>());
static_assert(test_is_trivially_assignable<false, int[10][10]>());
static_assert(test_is_trivially_assignable<false, int[10][10][10]>());
static_assert(test_is_trivially_assignable<false, Class[10]>());
static_assert(test_is_trivially_assignable<false, Class[10][10]>());
static_assert(test_is_trivially_assignable<false, Class[10][10][10]>());
static_assert(test_is_trivially_assignable<false, int[1], int>());
static_assert(test_is_trivially_assignable<false, int[10], int>());
static_assert(test_is_trivially_assignable<false, Class[1], Class>());
static_assert(test_is_trivially_assignable<false, Class[10], Class>());
static_assert(test_is_trivially_assignable<false, int[]>());
static_assert(test_is_trivially_assignable<false, int[][10]>());
static_assert(test_is_trivially_assignable<false, int[][10][10]>());
static_assert(test_is_trivially_assignable<false, int[], int>());
static_assert(test_is_trivially_assignable<false, int[][10], int>());
static_assert(test_is_trivially_assignable<false, int[][1], int>());
// endregion

// region lvalue reference
static_assert(test_is_trivially_assignable<true, int&>());
static_assert(test_is_trivially_assignable<true, int&, int&>());
static_assert(test_is_trivially_assignable<true, int&, const int&>());
static_assert(test_is_trivially_assignable<true, int&, volatile int&>());
static_assert(test_is_trivially_assignable<true, int&, const volatile int&>());
static_assert(test_is_trivially_assignable<true, int&, int&&>());
static_assert(test_is_trivially_assignable<true, int&, const int&&>());
static_assert(test_is_trivially_assignable<true, int&, volatile int&&>());
static_assert(test_is_trivially_assignable<true, int&, const volatile int&&>());
static_assert(test_is_trivially_assignable<true, int&, int>());
static_assert(test_is_trivially_assignable<true, int&, const int>());
static_assert(test_is_trivially_assignable<true, int&, volatile int>());
static_assert(test_is_trivially_assignable<true, int&, const volatile int>());

static_assert(test_is_trivially_assignable<false, const int&>());
static_assert(test_is_trivially_assignable<false, const int&, int&>());
static_assert(test_is_trivially_assignable<false, const int&, const int&>());
static_assert(test_is_trivially_assignable<false, const int&, volatile int&>());
static_assert(test_is_trivially_assignable<false, const int&, const volatile int&>());
static_assert(test_is_trivially_assignable<false, const int&, int&&>());
static_assert(test_is_trivially_assignable<false, const int&, const int&&>());
static_assert(test_is_trivially_assignable<false, const int&, volatile int&&>());
static_assert(test_is_trivially_assignable<false, const int&, const volatile int&&>());
static_assert(test_is_trivially_assignable<false, const int&, int>());
static_assert(test_is_trivially_assignable<false, const int&, const int>());
static_assert(test_is_trivially_assignable<false, const int&, volatile int>());
static_assert(test_is_trivially_assignable<false, const int&, const volatile int>());

static_assert(test_is_trivially_assignable<true, volatile int&>());
static_assert(test_is_trivially_assignable<true, volatile int&, int&>());
static_assert(test_is_trivially_assignable<true, volatile int&, const int&>());
static_assert(test_is_trivially_assignable<true, volatile int&, volatile int&>());
static_assert(test_is_trivially_assignable<true, volatile int&, const volatile int&>());
static_assert(test_is_trivially_assignable<true, volatile int&, int&&>());
static_assert(test_is_trivially_assignable<true, volatile int&, const int&&>());
static_assert(test_is_trivially_assignable<true, volatile int&, volatile int&&>());
static_assert(test_is_trivially_assignable<true, volatile int&, const volatile int&&>());
static_assert(test_is_trivially_assignable<true, volatile int&, int>());
static_assert(test_is_trivially_assignable<true, volatile int&, const int>());
static_assert(test_is_trivially_assignable<true, volatile int&, volatile int>());
static_assert(test_is_trivially_assignable<true, volatile int&, const volatile int>());

static_assert(test_is_trivially_assignable<false, const volatile int&>());
static_assert(test_is_trivially_assignable<false, const volatile int&, int&>());
static_assert(test_is_trivially_assignable<false, const volatile int&, const int&>());
static_assert(test_is_trivially_assignable<false, const volatile int&, volatile int&>());
static_assert(test_is_trivially_assignable<false, const volatile int&, const volatile int&>());
static_assert(test_is_trivially_assignable<false, const volatile int&, int&&>());
static_assert(test_is_trivially_assignable<false, const volatile int&, const int&&>());
static_assert(test_is_trivially_assignable<false, const volatile int&, volatile int&&>());
static_assert(test_is_trivially_assignable<false, const volatile int&, const volatile int&&>());
static_assert(test_is_trivially_assignable<false, const volatile int&, int>());
static_assert(test_is_trivially_assignable<false, const volatile int&, const int>());
static_assert(test_is_trivially_assignable<false, const volatile int&, volatile int>());
static_assert(test_is_trivially_assignable<false, const volatile int&, const volatile int>());

static_assert(test_is_trivially_assignable<false, int (&)()>());
static_assert(test_is_trivially_assignable<false, int (&)(), int()>());
static_assert(test_is_trivially_assignable<false, int (&)(), int(int)>());
static_assert(test_is_trivially_assignable<false, int (&)(), int (&)()>());
static_assert(test_is_trivially_assignable<false, int (&)(), int (&)(int)>());
static_assert(test_is_trivially_assignable<false, int (&)(), int (&&)()>());
static_assert(test_is_trivially_assignable<false, int (&)(), int (&&)(int)>());

static_assert(test_is_trivially_assignable<true, Class&, Derived&>());
static_assert(test_is_trivially_assignable<true, Class&, const Derived&>());
static_assert(test_is_trivially_assignable<false, Class&, volatile Derived&>());
static_assert(test_is_trivially_assignable<false, Class&, const volatile Derived&>());
static_assert(test_is_trivially_assignable<false, volatile Class&, Derived&>());
static_assert(test_is_trivially_assignable<false, volatile Class&, const Derived&>());
static_assert(test_is_trivially_assignable<false, volatile Class&, volatile Derived&>());
static_assert(test_is_trivially_assignable<false, volatile Class&, const volatile Derived&>());
static_assert(test_is_trivially_assignable<false, const Class&, Derived&>());
static_assert(test_is_trivially_assignable<false, const Class&, const Derived&>());
static_assert(test_is_trivially_assignable<false, const Class&, volatile Derived&>());
static_assert(test_is_trivially_assignable<false, const Class&, const volatile Derived&>());
static_assert(test_is_trivially_assignable<false, const volatile Class&, Derived&>());
static_assert(test_is_trivially_assignable<false, const volatile Class&, const Derived&>());
static_assert(test_is_trivially_assignable<false, const volatile Class&, volatile Derived&>());
static_assert(test_is_trivially_assignable<false, const volatile Class&, const volatile Derived&>());

static_assert(test_is_trivially_assignable<true, Class&, Derived&&>());
static_assert(test_is_trivially_assignable<true, Class&, const Derived&&>());
static_assert(test_is_trivially_assignable<false, Class&, volatile Derived&&>());
static_assert(test_is_trivially_assignable<false, Class&, const volatile Derived&&>());
static_assert(test_is_trivially_assignable<false, volatile Class&, Derived&&>());
static_assert(test_is_trivially_assignable<false, volatile Class&, const Derived&&>());
static_assert(test_is_trivially_assignable<false, volatile Class&, volatile Derived&&>());
static_assert(test_is_trivially_assignable<false, volatile Class&, const volatile Derived&&>());
static_assert(test_is_trivially_assignable<false, const Class&, Derived&&>());
static_assert(test_is_trivially_assignable<false, const Class&, const Derived&&>());
static_assert(test_is_trivially_assignable<false, const Class&, volatile Derived&&>());
static_assert(test_is_trivially_assignable<false, const Class&, const volatile Derived&&>());
static_assert(test_is_trivially_assignable<false, const volatile Class&, Derived&&>());
static_assert(test_is_trivially_assignable<false, const volatile Class&, const Derived&&>());
static_assert(test_is_trivially_assignable<false, const volatile Class&, volatile Derived&&>());
static_assert(test_is_trivially_assignable<false, const volatile Class&, const volatile Derived&&>());

static_assert(test_is_trivially_assignable<true, Class&>());
static_assert(test_is_trivially_assignable<true, Class&, Class>());
static_assert(test_is_trivially_assignable<true, Class&, Class&>());
static_assert(test_is_trivially_assignable<true, Class&, const Class&>());
static_assert(test_is_trivially_assignable<true, Class&, Class&&>());
static_assert(test_is_trivially_assignable<true, Class&, Derived>());
static_assert(test_is_trivially_assignable<true, Class&, const Derived&>());

static_assert(test_is_trivially_assignable<false, WithAssignOp&, int>());
static_assert(test_is_trivially_assignable<false, WithAssignOp&, const int&>());
static_assert(test_is_trivially_assignable<false, WithAssignOp&, int&&>());
static_assert(test_is_trivially_assignable<false, WithAssignOp&, ConvertsTo<int>>());
static_assert(test_is_trivially_assignable<false, WithAssignOp&, double>());
static_assert(test_is_trivially_assignable<false, WithAssignOp&, const double>());
static_assert(test_is_trivially_assignable<false, WithAssignOp&, const double&>());
static_assert(test_is_trivially_assignable<false, WithAssignOp&, long>());
static_assert(test_is_trivially_assignable<false, WithAssignOp&, const long&>());
// endregion

// region rvalue reference
static_assert(test_is_trivially_assignable<false, int&&>());
static_assert(test_is_trivially_assignable<false, int&&, int&>());
static_assert(test_is_trivially_assignable<false, int&&, const int&>());
static_assert(test_is_trivially_assignable<false, int&&, volatile int&>());
static_assert(test_is_trivially_assignable<false, int&&, const volatile int&>());
static_assert(test_is_trivially_assignable<false, int&&, int&&>());
static_assert(test_is_trivially_assignable<false, int&&, const int&&>());
static_assert(test_is_trivially_assignable<false, int&&, volatile int&&>());
static_assert(test_is_trivially_assignable<false, int&&, const volatile int&&>());
static_assert(test_is_trivially_assignable<false, int&&, int>());
static_assert(test_is_trivially_assignable<false, int&&, const int>());
static_assert(test_is_trivially_assignable<false, int&&, volatile int>());
static_assert(test_is_trivially_assignable<false, int&&, const volatile int>());

static_assert(test_is_trivially_assignable<false, const int&&>());
static_assert(test_is_trivially_assignable<false, const int&&, int&>());
static_assert(test_is_trivially_assignable<false, const int&&, const int&>());
static_assert(test_is_trivially_assignable<false, const int&&, volatile int&>());
static_assert(test_is_trivially_assignable<false, const int&&, const volatile int&>());
static_assert(test_is_trivially_assignable<false, const int&&, int&&>());
static_assert(test_is_trivially_assignable<false, const int&&, const int&&>());
static_assert(test_is_trivially_assignable<false, const int&&, volatile int&&>());
static_assert(test_is_trivially_assignable<false, const int&&, const volatile int&&>());
static_assert(test_is_trivially_assignable<false, const int&&, int>());
static_assert(test_is_trivially_assignable<false, const int&&, const int>());
static_assert(test_is_trivially_assignable<false, const int&&, volatile int>());
static_assert(test_is_trivially_assignable<false, const int&&, const volatile int>());

static_assert(test_is_trivially_assignable<false, volatile int&&>());
static_assert(test_is_trivially_assignable<false, volatile int&&, int&>());
static_assert(test_is_trivially_assignable<false, volatile int&&, const int&>());
static_assert(test_is_trivially_assignable<false, volatile int&&, volatile int&>());
static_assert(test_is_trivially_assignable<false, volatile int&&, const volatile int&>());
static_assert(test_is_trivially_assignable<false, volatile int&&, int&&>());
static_assert(test_is_trivially_assignable<false, volatile int&&, const int&&>());
static_assert(test_is_trivially_assignable<false, volatile int&&, volatile int&&>());
static_assert(test_is_trivially_assignable<false, volatile int&&, const volatile int&&>());
static_assert(test_is_trivially_assignable<false, volatile int&&, int>());
static_assert(test_is_trivially_assignable<false, volatile int&&, const int>());
static_assert(test_is_trivially_assignable<false, volatile int&&, volatile int>());
static_assert(test_is_trivially_assignable<false, volatile int&&, const volatile int>());

static_assert(test_is_trivially_assignable<false, const volatile int&&>());
static_assert(test_is_trivially_assignable<false, const volatile int&&, int&>());
static_assert(test_is_trivially_assignable<false, const volatile int&&, const int&>());
static_assert(test_is_trivially_assignable<false, const volatile int&&, volatile int&>());
static_assert(test_is_trivially_assignable<false, const volatile int&&, const volatile int&>());
static_assert(test_is_trivially_assignable<false, const volatile int&&, int&&>());
static_assert(test_is_trivially_assignable<false, const volatile int&&, const int&&>());
static_assert(test_is_trivially_assignable<false, const volatile int&&, volatile int&&>());
static_assert(test_is_trivially_assignable<false, const volatile int&&, const volatile int&&>());
static_assert(test_is_trivially_assignable<false, const volatile int&&, int>());
static_assert(test_is_trivially_assignable<false, const volatile int&&, const int>());
static_assert(test_is_trivially_assignable<false, const volatile int&&, volatile int>());
static_assert(test_is_trivially_assignable<false, const volatile int&&, const volatile int>());

static_assert(test_is_trivially_assignable<false, int (&&)()>());
static_assert(test_is_trivially_assignable<false, int (&&)(), int()>());
static_assert(test_is_trivially_assignable<false, int (&&)(), int(int)>());
static_assert(test_is_trivially_assignable<false, int (&&)(), int (&)()>());
static_assert(test_is_trivially_assignable<false, int (&&)(), int (&)(int)>());
static_assert(test_is_trivially_assignable<false, int (&&)(), int (&&)()>());
static_assert(test_is_trivially_assignable<false, int (&&)(), int (&&)(int)>());

static_assert(test_is_trivially_assignable<true, Class&&, Derived&>());
static_assert(test_is_trivially_assignable<true, Class&&, const Derived&>());
static_assert(test_is_trivially_assignable<false, Class&&, volatile Derived&>());
static_assert(test_is_trivially_assignable<false, Class&&, const volatile Derived&>());
static_assert(test_is_trivially_assignable<false, volatile Class&&, Derived&>());
static_assert(test_is_trivially_assignable<false, volatile Class&&, const Derived&>());
static_assert(test_is_trivially_assignable<false, volatile Class&&, volatile Derived&>());
static_assert(test_is_trivially_assignable<false, volatile Class&&, const volatile Derived&>());
static_assert(test_is_trivially_assignable<false, const Class&&, Derived&>());
static_assert(test_is_trivially_assignable<false, const Class&&, const Derived&>());
static_assert(test_is_trivially_assignable<false, const Class&&, volatile Derived&>());
static_assert(test_is_trivially_assignable<false, const Class&&, const volatile Derived&>());
static_assert(test_is_trivially_assignable<false, const volatile Class&&, Derived&>());
static_assert(test_is_trivially_assignable<false, const volatile Class&&, const Derived&>());
static_assert(test_is_trivially_assignable<false, const volatile Class&&, volatile Derived&>());
static_assert(test_is_trivially_assignable<false, const volatile Class&&, const volatile Derived&>());

static_assert(test_is_trivially_assignable<true, Class&&, Derived&&>());
static_assert(test_is_trivially_assignable<true, Class&&, const Derived&&>());
static_assert(test_is_trivially_assignable<false, Class&&, volatile Derived&&>());
static_assert(test_is_trivially_assignable<false, Class&&, const volatile Derived&&>());
static_assert(test_is_trivially_assignable<false, volatile Class&&, Derived&&>());
static_assert(test_is_trivially_assignable<false, volatile Class&&, const Derived&&>());
static_assert(test_is_trivially_assignable<false, volatile Class&&, volatile Derived&&>());
static_assert(test_is_trivially_assignable<false, volatile Class&&, const volatile Derived&&>());
static_assert(test_is_trivially_assignable<false, const Class&&, Derived&&>());
static_assert(test_is_trivially_assignable<false, const Class&&, const Derived&&>());
static_assert(test_is_trivially_assignable<false, const Class&&, volatile Derived&&>());
static_assert(test_is_trivially_assignable<false, const Class&&, const volatile Derived&&>());
static_assert(test_is_trivially_assignable<false, const volatile Class&&, Derived&&>());
static_assert(test_is_trivially_assignable<false, const volatile Class&&, const Derived&&>());
static_assert(test_is_trivially_assignable<false, const volatile Class&&, volatile Derived&&>());
static_assert(test_is_trivially_assignable<false, const volatile Class&&, const volatile Derived&&>());

static_assert(test_is_trivially_assignable<true, Class&&>());
static_assert(test_is_trivially_assignable<true, Class&&, Class>());
static_assert(test_is_trivially_assignable<true, Class&&, Class&>());
static_assert(test_is_trivially_assignable<true, Class&&, const Class&>());
static_assert(test_is_trivially_assignable<true, Class&&, Class&&>());
static_assert(test_is_trivially_assignable<true, Class&&, Derived>());
static_assert(test_is_trivially_assignable<true, Class&&, const Derived&>());

static_assert(test_is_trivially_assignable<false, WithAssignOp&&, int>());
static_assert(test_is_trivially_assignable<false, WithAssignOp&&, const int&>());
static_assert(test_is_trivially_assignable<false, WithAssignOp&&, int&&>());
static_assert(test_is_trivially_assignable<false, WithAssignOp&&, ConvertsTo<int>>());
static_assert(test_is_trivially_assignable<false, WithAssignOp&&, double>());
static_assert(test_is_trivially_assignable<false, WithAssignOp&&, const double>());
static_assert(test_is_trivially_assignable<false, WithAssignOp&&, const double&>());
static_assert(test_is_trivially_assignable<false, WithAssignOp&&, long>());
static_assert(test_is_trivially_assignable<false, WithAssignOp&&, const long&>());
// endregion

// region union
static_assert(test_scalar_or_union<Union, Union, true>());
// endregion

// region class
static_assert(test_is_trivially_assignable<true, Class>());
static_assert(test_is_trivially_assignable<true, Class, Class>());
static_assert(test_is_trivially_assignable<true, Class, Class&>());
static_assert(test_is_trivially_assignable<true, Class, const Class&>());
static_assert(test_is_trivially_assignable<true, Class, Class&&>());
static_assert(test_is_trivially_assignable<true, Class, Derived>());
static_assert(test_is_trivially_assignable<true, Class, const Derived&>());

static_assert(test_is_trivially_assignable<false, WithAssignOp, int>());
static_assert(test_is_trivially_assignable<false, WithAssignOp, const int&>());
static_assert(test_is_trivially_assignable<false, WithAssignOp, int&&>());
static_assert(test_is_trivially_assignable<false, WithAssignOp, ConvertsTo<int>>());
static_assert(test_is_trivially_assignable<false, WithAssignOp, double>());
static_assert(test_is_trivially_assignable<false, WithAssignOp, const double>());
static_assert(test_is_trivially_assignable<false, WithAssignOp, const double&>());
static_assert(test_is_trivially_assignable<false, WithAssignOp, long>());
static_assert(test_is_trivially_assignable<false, WithAssignOp, const long&>());

struct Abstract {
    virtual ~Abstract() = 0;
};

static_assert(test_is_trivially_assignable<false, Abstract, Abstract>());
static_assert(test_is_trivially_assignable<false, Abstract, const Abstract&>());

// endregion

// region function
static_assert(test_is_trivially_assignable<false, int(), int()>());
static_assert(test_is_trivially_assignable<false, int(), int (&)()>());
static_assert(test_is_trivially_assignable<false, int(), int (&&)()>());
static_assert(test_is_trivially_assignable<false, int(), int(int, int)>());
static_assert(test_is_trivially_assignable<false, int(), int (&)(int, int)>());
static_assert(test_is_trivially_assignable<false, int(), int (&&)(int, int)>());
// endregion