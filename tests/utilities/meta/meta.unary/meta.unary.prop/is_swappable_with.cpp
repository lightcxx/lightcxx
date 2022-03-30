#include <type_traits>

#include "meta/test_unary_trait.h"

template<bool e, class T, class U = T>
constexpr bool test_is_swappable_with() {
    bool b1 = std::is_base_of_v<std::bool_constant<e>, std::is_swappable_with<T, U>>;
    bool b2 = std::is_swappable_with<T, U>::value == e;
    bool b3 = std::is_same_v<typename std::is_swappable_with<T, U>::value_type, bool>;
    bool b4 = std::is_swappable_with<T, U>{} == e;
    bool b5 = (bool)std::is_swappable_with<T, U>{} == e;
    bool b6 = noexcept((bool)std::is_swappable_with<T, U>{});
    bool b7 = std::is_swappable_with<T, U>{}() == e;
    bool b8 = noexcept(std::is_swappable_with<T, U>{}());
    bool b9 = std::is_same_v<bool, decltype(std::is_swappable_with<T, U>{}())>;
    bool b10 = std::is_same_v<typename std::is_swappable_with<T, U>::type, std::bool_constant<e>>;
    bool b11 = std::is_same_v<decltype(std::is_swappable_with_v<T, U>), const bool>;
    bool b12 = std::is_swappable_with_v<T, U> == e;
    return b1 && b2 && b3 && b4 && b5 && b6 && b7 && b8 && b9 && b10 && b11 && b12;
}

struct MoveCtorAndAssign {
    [[maybe_unused]] int x, y;
};
static_assert(test_is_swappable_with<true, MoveCtorAndAssign&>());

struct HiddenFriendSwap {
    int x;

    HiddenFriendSwap(const HiddenFriendSwap&) = delete;
    HiddenFriendSwap(HiddenFriendSwap&&) = delete;
    HiddenFriendSwap& operator=(const HiddenFriendSwap&) = delete;
    HiddenFriendSwap& operator=(HiddenFriendSwap&&) = delete;

    friend void swap(HiddenFriendSwap& c1, HiddenFriendSwap& c2) {
        std::swap(c1.x, c2.x);
    }

    friend void swap(HiddenFriendSwap& c, int t) {
        std::swap(c.x, t);
    }

    friend void swap(int t, HiddenFriendSwap& c) {
        std::swap(c.x, t);
    }
};
static_assert(test_is_swappable_with<true, HiddenFriendSwap&>());
static_assert(test_is_swappable_with<true, HiddenFriendSwap&, int>());
static_assert(test_is_swappable_with<true, HiddenFriendSwap&, int&>());
static_assert(test_is_swappable_with<true, HiddenFriendSwap&, const int&>());
static_assert(test_is_swappable_with<true, HiddenFriendSwap&, int&&>());
static_assert(test_is_swappable_with<true, HiddenFriendSwap&, const int&&>());
static_assert(test_is_swappable_with<true, int, HiddenFriendSwap&>());
static_assert(test_is_swappable_with<true, int&, HiddenFriendSwap&>());
static_assert(test_is_swappable_with<true, const int&, HiddenFriendSwap&>());
static_assert(test_is_swappable_with<true, int&&, HiddenFriendSwap&>());
static_assert(test_is_swappable_with<true, const int&&, HiddenFriendSwap&>());

namespace ns {

struct ByADL {
    [[maybe_unused]] int x, y;

    ByADL(const ByADL&) = delete;
    ByADL(ByADL&&) = delete;
    ByADL& operator=(const ByADL&) = delete;
    ByADL& operator=(ByADL&&) = delete;
};

inline void swap(ByADL&, ByADL&) {}
inline void swap(ByADL&, int) {}
inline void swap(int, ByADL&) {}

}  // namespace ns
static_assert(test_is_swappable_with<true, ns::ByADL&>());
static_assert(test_is_swappable_with<true, ns::ByADL&, int>());
static_assert(test_is_swappable_with<true, ns::ByADL&, int&>());
static_assert(test_is_swappable_with<true, ns::ByADL&, const int&>());
static_assert(test_is_swappable_with<true, ns::ByADL&, int&&>());
static_assert(test_is_swappable_with<true, ns::ByADL&, const int&&>());
static_assert(test_is_swappable_with<true, int, ns::ByADL&>());
static_assert(test_is_swappable_with<true, int&, ns::ByADL&>());
static_assert(test_is_swappable_with<true, const int&, ns::ByADL&>());
static_assert(test_is_swappable_with<true, int&&, ns::ByADL&>());
static_assert(test_is_swappable_with<true, const int&&, ns::ByADL&>());

struct AsymmetricSwap {
    int x;

    friend void swap(AsymmetricSwap& c, int t) {
        std::swap(c.x, t);
    }
};
static_assert(test_is_swappable_with<false, AsymmetricSwap&, int>());
static_assert(test_is_swappable_with<false, AsymmetricSwap&, int&>());
static_assert(test_is_swappable_with<false, AsymmetricSwap&, const int&>());
static_assert(test_is_swappable_with<false, AsymmetricSwap&, int&&>());
static_assert(test_is_swappable_with<false, AsymmetricSwap&, const int&&>());
static_assert(test_is_swappable_with<false, int, AsymmetricSwap>());
static_assert(test_is_swappable_with<false, int&, AsymmetricSwap>());
static_assert(test_is_swappable_with<false, const int&, AsymmetricSwap>());
static_assert(test_is_swappable_with<false, int&&, AsymmetricSwap>());
static_assert(test_is_swappable_with<false, const int&&, AsymmetricSwap>());

// Next, test that nothing is swappable without any custom overloads except lvalue references with
// the same cv qualifier (that does not contain const).

// region void
static_assert(test_is_swappable_with<false, void, void>());
static_assert(test_is_swappable_with<false, void, const void>());
static_assert(test_is_swappable_with<false, void, volatile void>());
static_assert(test_is_swappable_with<false, void, const volatile void>());
static_assert(test_is_swappable_with<false, const void, void>());
static_assert(test_is_swappable_with<false, const void, const void>());
static_assert(test_is_swappable_with<false, const void, volatile void>());
static_assert(test_is_swappable_with<false, const void, const volatile void>());
static_assert(test_is_swappable_with<false, volatile void, void>());
static_assert(test_is_swappable_with<false, volatile void, const void>());
static_assert(test_is_swappable_with<false, volatile void, volatile void>());
static_assert(test_is_swappable_with<false, volatile void, const volatile void>());
static_assert(test_is_swappable_with<false, const volatile void, void>());
static_assert(test_is_swappable_with<false, const volatile void, const void>());
static_assert(test_is_swappable_with<false, const volatile void, volatile void>());
static_assert(test_is_swappable_with<false, const volatile void, const volatile void>());
// endregion

// region scalar

// Scalars cannot be passed to swap().
template<class T, class U = T>
constexpr bool test_scalar() {
    static_assert(test_is_swappable_with<false, T>());
    static_assert(test_is_swappable_with<false, T, U>());
    static_assert(test_is_swappable_with<false, T, U&>());
    static_assert(test_is_swappable_with<false, T, U&&>());
    static_assert(test_is_swappable_with<false, T, const U>());
    static_assert(test_is_swappable_with<false, T, const U&>());
    static_assert(test_is_swappable_with<false, T, const U&&>());
    static_assert(test_is_swappable_with<false, T, volatile U>());
    static_assert(test_is_swappable_with<false, T, volatile U&>());
    static_assert(test_is_swappable_with<false, T, volatile U&&>());
    static_assert(test_is_swappable_with<false, T, const volatile U>());
    static_assert(test_is_swappable_with<false, T, const volatile U&>());
    static_assert(test_is_swappable_with<false, T, const volatile U&&>());
    static_assert(test_is_swappable_with<false, const T>());
    static_assert(test_is_swappable_with<false, const T, U>());
    static_assert(test_is_swappable_with<false, const T, U&>());
    static_assert(test_is_swappable_with<false, const T, U&&>());
    static_assert(test_is_swappable_with<false, const T, const U>());
    static_assert(test_is_swappable_with<false, const T, const U&>());
    static_assert(test_is_swappable_with<false, const T, const U&&>());
    static_assert(test_is_swappable_with<false, const T, volatile U>());
    static_assert(test_is_swappable_with<false, const T, volatile U&>());
    static_assert(test_is_swappable_with<false, const T, volatile U&&>());
    static_assert(test_is_swappable_with<false, const T, const volatile U>());
    static_assert(test_is_swappable_with<false, const T, const volatile U&>());
    static_assert(test_is_swappable_with<false, const T, const volatile U&&>());
    static_assert(test_is_swappable_with<false, volatile T>());
    static_assert(test_is_swappable_with<false, volatile T, U>());
    static_assert(test_is_swappable_with<false, volatile T, U&>());
    static_assert(test_is_swappable_with<false, volatile T, U&&>());
    static_assert(test_is_swappable_with<false, volatile T, const U>());
    static_assert(test_is_swappable_with<false, volatile T, const U&>());
    static_assert(test_is_swappable_with<false, volatile T, const U&&>());
    static_assert(test_is_swappable_with<false, volatile T, volatile U>());
    static_assert(test_is_swappable_with<false, volatile T, volatile U&>());
    static_assert(test_is_swappable_with<false, volatile T, volatile U&&>());
    static_assert(test_is_swappable_with<false, volatile T, const volatile U>());
    static_assert(test_is_swappable_with<false, volatile T, const volatile U&>());
    static_assert(test_is_swappable_with<false, volatile T, const volatile U&&>());
    static_assert(test_is_swappable_with<false, const volatile T>());
    static_assert(test_is_swappable_with<false, const volatile T, U>());
    static_assert(test_is_swappable_with<false, const volatile T, U&>());
    static_assert(test_is_swappable_with<false, const volatile T, U&&>());
    static_assert(test_is_swappable_with<false, const volatile T, const U>());
    static_assert(test_is_swappable_with<false, const volatile T, const U&>());
    static_assert(test_is_swappable_with<false, const volatile T, const U&&>());
    static_assert(test_is_swappable_with<false, const volatile T, volatile U>());
    static_assert(test_is_swappable_with<false, const volatile T, volatile U&>());
    static_assert(test_is_swappable_with<false, const volatile T, volatile U&&>());
    static_assert(test_is_swappable_with<false, const volatile T, const volatile U>());
    static_assert(test_is_swappable_with<false, const volatile T, const volatile U&>());
    static_assert(test_is_swappable_with<false, const volatile T, const volatile U&&>());
    static_assert(test_is_swappable_with<false, T, Class>());
    static_assert(test_is_swappable_with<false, T, const Class&>());
    static_assert(test_is_swappable_with<false, const T, Class>());
    static_assert(test_is_swappable_with<false, const T, const Class&>());
    static_assert(test_is_swappable_with<false, volatile T, Class>());
    static_assert(test_is_swappable_with<false, volatile T, const Class&>());
    static_assert(test_is_swappable_with<false, const volatile T, Class>());
    static_assert(test_is_swappable_with<false, const volatile T, const Class&>());
    return true;
}
static_assert(test_scalar<decltype(nullptr)>());
static_assert(test_scalar<bool>());
static_assert(test_scalar<char>());
static_assert(test_scalar<char8_t>());
static_assert(test_scalar<char16_t>());
static_assert(test_scalar<char32_t>());
static_assert(test_scalar<wchar_t>());
static_assert(test_scalar<signed char>());
static_assert(test_scalar<short>());
static_assert(test_scalar<int>());
static_assert(test_scalar<long>());
static_assert(test_scalar<long long>());
static_assert(test_scalar<unsigned char>());
static_assert(test_scalar<unsigned short>());
static_assert(test_scalar<unsigned int>());
static_assert(test_scalar<unsigned long>());
static_assert(test_scalar<unsigned long long>());
static_assert(test_scalar<float>());
static_assert(test_scalar<double>());
static_assert(test_scalar<long double>());
static_assert(test_scalar<void*>());
static_assert(test_scalar<void*, decltype(nullptr)>());
static_assert(test_scalar<const void*>());
static_assert(test_scalar<volatile void*>());
static_assert(test_scalar<const volatile void*>());
static_assert(test_scalar<int*>());
static_assert(test_scalar<int**>());
static_assert(test_scalar<int***>());
static_assert(test_scalar<incomplete_type*>());
static_assert(test_scalar<int (*)(int)>());
static_assert(test_scalar<int (**)(int)>());
static_assert(test_is_swappable_with<false, int (*)(int), void (*)(long, int)>());
static_assert(test_scalar<Class*>());
static_assert(test_scalar<int Class::*>());
static_assert(test_is_swappable_with<false, int Class::*, Class Class::*>());
static_assert(test_scalar<Class Class::*>());
static_assert(test_scalar<Class * Class::*>());
static_assert(test_scalar<int (Class::*)(int, int)>());
static_assert(test_scalar<Class (Class::*)(int, Class Class::*)>());
static_assert(test_scalar<Class Class::* (Class::*)(int, int)>());
static_assert(test_is_swappable_with<false, int (Class::*)(int, int), Class Class::* (Class::*)(int, int)>());
static_assert(test_scalar<Enum>());
static_assert(test_scalar<EnumClass>());
static_assert(test_is_swappable_with<false, Enum, EnumClass>());
static_assert(test_is_swappable_with<false, EnumClass, Enum>());
// endregion

// region array
static_assert(test_is_swappable_with<false, int[10]>());
static_assert(test_is_swappable_with<false, int[10][10]>());
static_assert(test_is_swappable_with<false, int[10][10][10]>());
static_assert(test_is_swappable_with<false, Class[10]>());
static_assert(test_is_swappable_with<false, Class[10][10]>());
static_assert(test_is_swappable_with<false, Class[10][10][10]>());
static_assert(test_is_swappable_with<false, int[1], int>());
static_assert(test_is_swappable_with<false, int[10], int>());
static_assert(test_is_swappable_with<false, Class[1], Class>());
static_assert(test_is_swappable_with<false, Class[10], Class>());
static_assert(test_is_swappable_with<false, int[]>());
static_assert(test_is_swappable_with<false, int[][10]>());
static_assert(test_is_swappable_with<false, int[][10][10]>());
static_assert(test_is_swappable_with<false, int[], int>());
static_assert(test_is_swappable_with<false, int[][10], int>());
static_assert(test_is_swappable_with<false, int[][1], int>());
// endregion

// region lvalue reference
static_assert(test_is_swappable_with<true, int&>());
static_assert(test_is_swappable_with<false, int&, const int&>());
static_assert(test_is_swappable_with<false, int&, volatile int&>());
static_assert(test_is_swappable_with<false, int&, const volatile int&>());
static_assert(test_is_swappable_with<false, int&, int&&>());
static_assert(test_is_swappable_with<false, int&, const int&&>());
static_assert(test_is_swappable_with<false, int&, volatile int&&>());
static_assert(test_is_swappable_with<false, int&, const volatile int&&>());
static_assert(test_is_swappable_with<false, int&, int>());
static_assert(test_is_swappable_with<false, int&, const int>());
static_assert(test_is_swappable_with<false, int&, volatile int>());
static_assert(test_is_swappable_with<false, int&, const volatile int>());

static_assert(test_is_swappable_with<false, const int&>());
static_assert(test_is_swappable_with<false, const int&, int&>());
static_assert(test_is_swappable_with<false, const int&, const int&>());
static_assert(test_is_swappable_with<false, const int&, volatile int&>());
static_assert(test_is_swappable_with<false, const int&, const volatile int&>());
static_assert(test_is_swappable_with<false, const int&, int&&>());
static_assert(test_is_swappable_with<false, const int&, const int&&>());
static_assert(test_is_swappable_with<false, const int&, volatile int&&>());
static_assert(test_is_swappable_with<false, const int&, const volatile int&&>());
static_assert(test_is_swappable_with<false, const int&, int>());
static_assert(test_is_swappable_with<false, const int&, const int>());
static_assert(test_is_swappable_with<false, const int&, volatile int>());
static_assert(test_is_swappable_with<false, const int&, const volatile int>());

static_assert(test_is_swappable_with<true, volatile int&>());
static_assert(test_is_swappable_with<false, volatile int&, int&>());
static_assert(test_is_swappable_with<false, volatile int&, const int&>());
static_assert(test_is_swappable_with<false, volatile int&, const volatile int&>());
static_assert(test_is_swappable_with<false, volatile int&, int&&>());
static_assert(test_is_swappable_with<false, volatile int&, const int&&>());
static_assert(test_is_swappable_with<false, volatile int&, volatile int&&>());
static_assert(test_is_swappable_with<false, volatile int&, const volatile int&&>());
static_assert(test_is_swappable_with<false, volatile int&, int>());
static_assert(test_is_swappable_with<false, volatile int&, const int>());
static_assert(test_is_swappable_with<false, volatile int&, volatile int>());
static_assert(test_is_swappable_with<false, volatile int&, const volatile int>());

static_assert(test_is_swappable_with<false, const volatile int&>());
static_assert(test_is_swappable_with<false, const volatile int&, int&>());
static_assert(test_is_swappable_with<false, const volatile int&, const int&>());
static_assert(test_is_swappable_with<false, const volatile int&, volatile int&>());
static_assert(test_is_swappable_with<false, const volatile int&, const volatile int&>());
static_assert(test_is_swappable_with<false, const volatile int&, int&&>());
static_assert(test_is_swappable_with<false, const volatile int&, const int&&>());
static_assert(test_is_swappable_with<false, const volatile int&, volatile int&&>());
static_assert(test_is_swappable_with<false, const volatile int&, const volatile int&&>());
static_assert(test_is_swappable_with<false, const volatile int&, int>());
static_assert(test_is_swappable_with<false, const volatile int&, const int>());
static_assert(test_is_swappable_with<false, const volatile int&, volatile int>());
static_assert(test_is_swappable_with<false, const volatile int&, const volatile int>());

static_assert(test_is_swappable_with<false, int (&)()>());
static_assert(test_is_swappable_with<false, int (&)(), int()>());
static_assert(test_is_swappable_with<false, int (&)(), int(int)>());
static_assert(test_is_swappable_with<false, int (&)(), int (&)()>());
static_assert(test_is_swappable_with<false, int (&)(), int (&)(int)>());
static_assert(test_is_swappable_with<false, int (&)(), int(&&)()>());
static_assert(test_is_swappable_with<false, int (&)(), int(&&)(int)>());
// endregion

// region rvalue reference
static_assert(test_is_swappable_with<false, int&&>());
static_assert(test_is_swappable_with<false, int&&, int&>());
static_assert(test_is_swappable_with<false, int&&, const int&>());
static_assert(test_is_swappable_with<false, int&&, volatile int&>());
static_assert(test_is_swappable_with<false, int&&, const volatile int&>());
static_assert(test_is_swappable_with<false, int&&, int&&>());
static_assert(test_is_swappable_with<false, int&&, const int&&>());
static_assert(test_is_swappable_with<false, int&&, volatile int&&>());
static_assert(test_is_swappable_with<false, int&&, const volatile int&&>());
static_assert(test_is_swappable_with<false, int&&, int>());
static_assert(test_is_swappable_with<false, int&&, const int>());
static_assert(test_is_swappable_with<false, int&&, volatile int>());
static_assert(test_is_swappable_with<false, int&&, const volatile int>());

static_assert(test_is_swappable_with<false, const int&&>());
static_assert(test_is_swappable_with<false, const int&&, int&>());
static_assert(test_is_swappable_with<false, const int&&, const int&>());
static_assert(test_is_swappable_with<false, const int&&, volatile int&>());
static_assert(test_is_swappable_with<false, const int&&, const volatile int&>());
static_assert(test_is_swappable_with<false, const int&&, int&&>());
static_assert(test_is_swappable_with<false, const int&&, const int&&>());
static_assert(test_is_swappable_with<false, const int&&, volatile int&&>());
static_assert(test_is_swappable_with<false, const int&&, const volatile int&&>());
static_assert(test_is_swappable_with<false, const int&&, int>());
static_assert(test_is_swappable_with<false, const int&&, const int>());
static_assert(test_is_swappable_with<false, const int&&, volatile int>());
static_assert(test_is_swappable_with<false, const int&&, const volatile int>());

static_assert(test_is_swappable_with<false, volatile int&&>());
static_assert(test_is_swappable_with<false, volatile int&&, int&>());
static_assert(test_is_swappable_with<false, volatile int&&, const int&>());
static_assert(test_is_swappable_with<false, volatile int&&, volatile int&>());
static_assert(test_is_swappable_with<false, volatile int&&, const volatile int&>());
static_assert(test_is_swappable_with<false, volatile int&&, int&&>());
static_assert(test_is_swappable_with<false, volatile int&&, const int&&>());
static_assert(test_is_swappable_with<false, volatile int&&, volatile int&&>());
static_assert(test_is_swappable_with<false, volatile int&&, const volatile int&&>());
static_assert(test_is_swappable_with<false, volatile int&&, int>());
static_assert(test_is_swappable_with<false, volatile int&&, const int>());
static_assert(test_is_swappable_with<false, volatile int&&, volatile int>());
static_assert(test_is_swappable_with<false, volatile int&&, const volatile int>());

static_assert(test_is_swappable_with<false, const volatile int&&>());
static_assert(test_is_swappable_with<false, const volatile int&&, int&>());
static_assert(test_is_swappable_with<false, const volatile int&&, const int&>());
static_assert(test_is_swappable_with<false, const volatile int&&, volatile int&>());
static_assert(test_is_swappable_with<false, const volatile int&&, const volatile int&>());
static_assert(test_is_swappable_with<false, const volatile int&&, int&&>());
static_assert(test_is_swappable_with<false, const volatile int&&, const int&&>());
static_assert(test_is_swappable_with<false, const volatile int&&, volatile int&&>());
static_assert(test_is_swappable_with<false, const volatile int&&, const volatile int&&>());
static_assert(test_is_swappable_with<false, const volatile int&&, int>());
static_assert(test_is_swappable_with<false, const volatile int&&, const int>());
static_assert(test_is_swappable_with<false, const volatile int&&, volatile int>());
static_assert(test_is_swappable_with<false, const volatile int&&, const volatile int>());

static_assert(test_is_swappable_with<false, int(&&)()>());
static_assert(test_is_swappable_with<false, int(&&)(), int()>());
static_assert(test_is_swappable_with<false, int(&&)(), int(int)>());
static_assert(test_is_swappable_with<false, int(&&)(), int (&)()>());
static_assert(test_is_swappable_with<false, int(&&)(), int (&)(int)>());
static_assert(test_is_swappable_with<false, int(&&)(), int(&&)()>());
static_assert(test_is_swappable_with<false, int(&&)(), int(&&)(int)>());
// endregion

// region union
static_assert(test_is_swappable_with<false, Union, Union>());
// endregion

// region class
static_assert(test_is_swappable_with<false, Class, Class>());
// endregion

// region function
static_assert(test_is_swappable_with<false, int(), int()>());
static_assert(test_is_swappable_with<false, int(), int (&)()>());
static_assert(test_is_swappable_with<false, int(), int(&&)()>());
static_assert(test_is_swappable_with<false, int(), int(int, int)>());
static_assert(test_is_swappable_with<false, int(), int (&)(int, int)>());
static_assert(test_is_swappable_with<false, int(), int(&&)(int, int)>());
// endregion