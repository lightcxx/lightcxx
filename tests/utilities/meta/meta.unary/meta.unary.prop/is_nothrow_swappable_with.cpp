#include <type_traits>

#include "test_unary_trait.h"

template<bool e, class T, class U = T>
constexpr bool test_is_nothrow_swappable_with() {
    bool b1 = std::is_base_of_v<std::bool_constant<e>, std::is_nothrow_swappable_with<T, U>>;
    bool b2 = std::is_nothrow_swappable_with<T, U>::value == e;
    bool b3 = std::is_same_v<typename std::is_nothrow_swappable_with<T, U>::value_type, bool>;
    bool b4 = std::is_nothrow_swappable_with<T, U>{} == e;
    bool b5 = static_cast<bool>(std::is_nothrow_swappable_with<T, U>{}) == e;
    bool b6 = noexcept(static_cast<bool>(std::is_nothrow_swappable_with<T, U>{}));
    bool b7 = std::is_nothrow_swappable_with<T, U>{}() == e;
    bool b8 = noexcept(std::is_nothrow_swappable_with<T, U>{}());
    bool b9 = std::is_same_v<bool, decltype(std::is_nothrow_swappable_with<T, U>{}())>;
    bool b10 = std::is_same_v<typename std::is_nothrow_swappable_with<T, U>::type, std::bool_constant<e>>;
    bool b11 = std::is_same_v<decltype(std::is_nothrow_swappable_with_v<T, U>), const bool>;
    bool b12 = std::is_nothrow_swappable_with_v<T, U> == e;
    return b1 && b2 && b3 && b4 && b5 && b6 && b7 && b8 && b9 && b10 && b11 && b12;
}

struct MoveCtorAndAssign {
    int x, y;
};
static_assert(test_is_nothrow_swappable_with<true, MoveCtorAndAssign&>());

struct HiddenFriendSwap {
    int x;

    HiddenFriendSwap(const HiddenFriendSwap&) = delete;
    HiddenFriendSwap(HiddenFriendSwap&&) = delete;
    HiddenFriendSwap& operator=(const HiddenFriendSwap&) = delete;
    HiddenFriendSwap& operator=(HiddenFriendSwap&&) = delete;

    friend void swap(HiddenFriendSwap& c1, HiddenFriendSwap& c2) noexcept(false) {
        std::swap(c1.x, c2.x);
    }

    friend void swap(HiddenFriendSwap& c, int t) noexcept(false) {
        std::swap(c.x, t);
    }

    friend void swap(int t, HiddenFriendSwap& c) noexcept(false) {
        std::swap(c.x, t);
    }
};
static_assert(test_is_nothrow_swappable_with<false, HiddenFriendSwap&>());
static_assert(test_is_nothrow_swappable_with<false, HiddenFriendSwap&, int>());
static_assert(test_is_nothrow_swappable_with<false, HiddenFriendSwap&, int&>());
static_assert(test_is_nothrow_swappable_with<false, HiddenFriendSwap&, const int&>());
static_assert(test_is_nothrow_swappable_with<false, HiddenFriendSwap&, int&&>());
static_assert(test_is_nothrow_swappable_with<false, HiddenFriendSwap&, const int&&>());
static_assert(test_is_nothrow_swappable_with<false, int, HiddenFriendSwap&>());
static_assert(test_is_nothrow_swappable_with<false, int&, HiddenFriendSwap&>());
static_assert(test_is_nothrow_swappable_with<false, const int&, HiddenFriendSwap&>());
static_assert(test_is_nothrow_swappable_with<false, int&&, HiddenFriendSwap&>());
static_assert(test_is_nothrow_swappable_with<false, const int&&, HiddenFriendSwap&>());

namespace ns {

struct ByADL {
    int x, y;

    ByADL(const ByADL&) = delete;
    ByADL(ByADL&&) = delete;
    ByADL& operator=(const ByADL&) = delete;
    ByADL& operator=(ByADL&&) = delete;
};

inline void swap(ByADL&, ByADL&) noexcept(false) {}
inline void swap(ByADL&, int) noexcept(false) {}
inline void swap(int, ByADL&) noexcept(false) {}

}  // namespace ns
static_assert(test_is_nothrow_swappable_with<false, ns::ByADL&>());
static_assert(test_is_nothrow_swappable_with<false, ns::ByADL&, int>());
static_assert(test_is_nothrow_swappable_with<false, ns::ByADL&, int&>());
static_assert(test_is_nothrow_swappable_with<false, ns::ByADL&, const int&>());
static_assert(test_is_nothrow_swappable_with<false, ns::ByADL&, int&&>());
static_assert(test_is_nothrow_swappable_with<false, ns::ByADL&, const int&&>());
static_assert(test_is_nothrow_swappable_with<false, int, ns::ByADL&>());
static_assert(test_is_nothrow_swappable_with<false, int&, ns::ByADL&>());
static_assert(test_is_nothrow_swappable_with<false, const int&, ns::ByADL&>());
static_assert(test_is_nothrow_swappable_with<false, int&&, ns::ByADL&>());
static_assert(test_is_nothrow_swappable_with<false, const int&&, ns::ByADL&>());

struct HiddenFriendNothrowSwap {
    int x;

    HiddenFriendNothrowSwap(const HiddenFriendNothrowSwap&) = delete;
    HiddenFriendNothrowSwap(HiddenFriendNothrowSwap&&) = delete;
    HiddenFriendNothrowSwap& operator=(const HiddenFriendNothrowSwap&) = delete;
    HiddenFriendNothrowSwap& operator=(HiddenFriendNothrowSwap&&) = delete;

    friend void swap(HiddenFriendNothrowSwap& c1, HiddenFriendNothrowSwap& c2) noexcept {
        std::swap(c1.x, c2.x);
    }

    friend void swap(HiddenFriendNothrowSwap& c, int t) noexcept {
        std::swap(c.x, t);
    }

    friend void swap(int t, HiddenFriendNothrowSwap& c) noexcept {
        std::swap(c.x, t);
    }
};
static_assert(test_is_nothrow_swappable_with<true, HiddenFriendNothrowSwap&>());
static_assert(test_is_nothrow_swappable_with<true, HiddenFriendNothrowSwap&, int>());
static_assert(test_is_nothrow_swappable_with<true, HiddenFriendNothrowSwap&, int&>());
static_assert(test_is_nothrow_swappable_with<true, HiddenFriendNothrowSwap&, const int&>());
static_assert(test_is_nothrow_swappable_with<true, HiddenFriendNothrowSwap&, int&&>());
static_assert(test_is_nothrow_swappable_with<true, HiddenFriendNothrowSwap&, const int&&>());
static_assert(test_is_nothrow_swappable_with<true, int, HiddenFriendNothrowSwap&>());
static_assert(test_is_nothrow_swappable_with<true, int&, HiddenFriendNothrowSwap&>());
static_assert(test_is_nothrow_swappable_with<true, const int&, HiddenFriendNothrowSwap&>());
static_assert(test_is_nothrow_swappable_with<true, int&&, HiddenFriendNothrowSwap&>());
static_assert(test_is_nothrow_swappable_with<true, const int&&, HiddenFriendNothrowSwap&>());

namespace ns {

struct ByADLNothrow {
    int x, y;

    ByADLNothrow(const ByADLNothrow&) = delete;
    ByADLNothrow(ByADLNothrow&&) = delete;
    ByADLNothrow& operator=(const ByADLNothrow&) = delete;
    ByADLNothrow& operator=(ByADLNothrow&&) = delete;
};

inline void swap(ByADLNothrow&, ByADLNothrow&) noexcept {}
inline void swap(ByADLNothrow&, int) noexcept {}
inline void swap(int, ByADLNothrow&) noexcept {}

}  // namespace ns
static_assert(test_is_nothrow_swappable_with<true, ns::ByADLNothrow&>());
static_assert(test_is_nothrow_swappable_with<true, ns::ByADLNothrow&, int>());
static_assert(test_is_nothrow_swappable_with<true, ns::ByADLNothrow&, int&>());
static_assert(test_is_nothrow_swappable_with<true, ns::ByADLNothrow&, const int&>());
static_assert(test_is_nothrow_swappable_with<true, ns::ByADLNothrow&, int&&>());
static_assert(test_is_nothrow_swappable_with<true, ns::ByADLNothrow&, const int&&>());
static_assert(test_is_nothrow_swappable_with<true, int, ns::ByADLNothrow&>());
static_assert(test_is_nothrow_swappable_with<true, int&, ns::ByADLNothrow&>());
static_assert(test_is_nothrow_swappable_with<true, const int&, ns::ByADLNothrow&>());
static_assert(test_is_nothrow_swappable_with<true, int&&, ns::ByADLNothrow&>());
static_assert(test_is_nothrow_swappable_with<true, const int&&, ns::ByADLNothrow&>());

struct AsymmetricSwap {
    int x;

    friend void swap(AsymmetricSwap& c, int t) noexcept(false) {
        std::swap(c.x, t);
    }
};
static_assert(test_is_nothrow_swappable_with<false, AsymmetricSwap&, int>());
static_assert(test_is_nothrow_swappable_with<false, AsymmetricSwap&, int&>());
static_assert(test_is_nothrow_swappable_with<false, AsymmetricSwap&, const int&>());
static_assert(test_is_nothrow_swappable_with<false, AsymmetricSwap&, int&&>());
static_assert(test_is_nothrow_swappable_with<false, AsymmetricSwap&, const int&&>());
static_assert(test_is_nothrow_swappable_with<false, int, AsymmetricSwap>());
static_assert(test_is_nothrow_swappable_with<false, int&, AsymmetricSwap>());
static_assert(test_is_nothrow_swappable_with<false, const int&, AsymmetricSwap>());
static_assert(test_is_nothrow_swappable_with<false, int&&, AsymmetricSwap>());
static_assert(test_is_nothrow_swappable_with<false, const int&&, AsymmetricSwap>());

struct AsymmetricSwapNothrow {
    int x;

    friend void swap(AsymmetricSwapNothrow& c, int t) noexcept {
        std::swap(c.x, t);
    }
};
static_assert(test_is_nothrow_swappable_with<false, AsymmetricSwapNothrow&, int>());
static_assert(test_is_nothrow_swappable_with<false, AsymmetricSwapNothrow&, int&>());
static_assert(test_is_nothrow_swappable_with<false, AsymmetricSwapNothrow&, const int&>());
static_assert(test_is_nothrow_swappable_with<false, AsymmetricSwapNothrow&, int&&>());
static_assert(test_is_nothrow_swappable_with<false, AsymmetricSwapNothrow&, const int&&>());
static_assert(test_is_nothrow_swappable_with<false, int, AsymmetricSwapNothrow>());
static_assert(test_is_nothrow_swappable_with<false, int&, AsymmetricSwapNothrow>());
static_assert(test_is_nothrow_swappable_with<false, const int&, AsymmetricSwapNothrow>());
static_assert(test_is_nothrow_swappable_with<false, int&&, AsymmetricSwapNothrow>());
static_assert(test_is_nothrow_swappable_with<false, const int&&, AsymmetricSwapNothrow>());

// Next, test that nothing is swappable without any custom overloads except lvalue references with
// the same cv qualifier (that does not contain const).

// region void
static_assert(test_is_nothrow_swappable_with<false, void, void>());
static_assert(test_is_nothrow_swappable_with<false, void, const void>());
static_assert(test_is_nothrow_swappable_with<false, void, volatile void>());
static_assert(test_is_nothrow_swappable_with<false, void, const volatile void>());
static_assert(test_is_nothrow_swappable_with<false, const void, void>());
static_assert(test_is_nothrow_swappable_with<false, const void, const void>());
static_assert(test_is_nothrow_swappable_with<false, const void, volatile void>());
static_assert(test_is_nothrow_swappable_with<false, const void, const volatile void>());
static_assert(test_is_nothrow_swappable_with<false, volatile void, void>());
static_assert(test_is_nothrow_swappable_with<false, volatile void, const void>());
static_assert(test_is_nothrow_swappable_with<false, volatile void, volatile void>());
static_assert(test_is_nothrow_swappable_with<false, volatile void, const volatile void>());
static_assert(test_is_nothrow_swappable_with<false, const volatile void, void>());
static_assert(test_is_nothrow_swappable_with<false, const volatile void, const void>());
static_assert(test_is_nothrow_swappable_with<false, const volatile void, volatile void>());
static_assert(test_is_nothrow_swappable_with<false, const volatile void, const volatile void>());
// endregion

// region scalar

// Scalars cannot be passed to swap().
template<class T, class U = T>
constexpr bool test_scalar() {
    static_assert(test_is_nothrow_swappable_with<false, T>());
    static_assert(test_is_nothrow_swappable_with<false, T, U>());
    static_assert(test_is_nothrow_swappable_with<false, T, U&>());
    static_assert(test_is_nothrow_swappable_with<false, T, U&&>());
    static_assert(test_is_nothrow_swappable_with<false, T, const U>());
    static_assert(test_is_nothrow_swappable_with<false, T, const U&>());
    static_assert(test_is_nothrow_swappable_with<false, T, const U&&>());
    static_assert(test_is_nothrow_swappable_with<false, T, volatile U>());
    static_assert(test_is_nothrow_swappable_with<false, T, volatile U&>());
    static_assert(test_is_nothrow_swappable_with<false, T, volatile U&&>());
    static_assert(test_is_nothrow_swappable_with<false, T, const volatile U>());
    static_assert(test_is_nothrow_swappable_with<false, T, const volatile U&>());
    static_assert(test_is_nothrow_swappable_with<false, T, const volatile U&&>());
    static_assert(test_is_nothrow_swappable_with<false, const T>());
    static_assert(test_is_nothrow_swappable_with<false, const T, U>());
    static_assert(test_is_nothrow_swappable_with<false, const T, U&>());
    static_assert(test_is_nothrow_swappable_with<false, const T, U&&>());
    static_assert(test_is_nothrow_swappable_with<false, const T, const U>());
    static_assert(test_is_nothrow_swappable_with<false, const T, const U&>());
    static_assert(test_is_nothrow_swappable_with<false, const T, const U&&>());
    static_assert(test_is_nothrow_swappable_with<false, const T, volatile U>());
    static_assert(test_is_nothrow_swappable_with<false, const T, volatile U&>());
    static_assert(test_is_nothrow_swappable_with<false, const T, volatile U&&>());
    static_assert(test_is_nothrow_swappable_with<false, const T, const volatile U>());
    static_assert(test_is_nothrow_swappable_with<false, const T, const volatile U&>());
    static_assert(test_is_nothrow_swappable_with<false, const T, const volatile U&&>());
    static_assert(test_is_nothrow_swappable_with<false, volatile T>());
    static_assert(test_is_nothrow_swappable_with<false, volatile T, U>());
    static_assert(test_is_nothrow_swappable_with<false, volatile T, U&>());
    static_assert(test_is_nothrow_swappable_with<false, volatile T, U&&>());
    static_assert(test_is_nothrow_swappable_with<false, volatile T, const U>());
    static_assert(test_is_nothrow_swappable_with<false, volatile T, const U&>());
    static_assert(test_is_nothrow_swappable_with<false, volatile T, const U&&>());
    static_assert(test_is_nothrow_swappable_with<false, volatile T, volatile U>());
    static_assert(test_is_nothrow_swappable_with<false, volatile T, volatile U&>());
    static_assert(test_is_nothrow_swappable_with<false, volatile T, volatile U&&>());
    static_assert(test_is_nothrow_swappable_with<false, volatile T, const volatile U>());
    static_assert(test_is_nothrow_swappable_with<false, volatile T, const volatile U&>());
    static_assert(test_is_nothrow_swappable_with<false, volatile T, const volatile U&&>());
    static_assert(test_is_nothrow_swappable_with<false, const volatile T>());
    static_assert(test_is_nothrow_swappable_with<false, const volatile T, U>());
    static_assert(test_is_nothrow_swappable_with<false, const volatile T, U&>());
    static_assert(test_is_nothrow_swappable_with<false, const volatile T, U&&>());
    static_assert(test_is_nothrow_swappable_with<false, const volatile T, const U>());
    static_assert(test_is_nothrow_swappable_with<false, const volatile T, const U&>());
    static_assert(test_is_nothrow_swappable_with<false, const volatile T, const U&&>());
    static_assert(test_is_nothrow_swappable_with<false, const volatile T, volatile U>());
    static_assert(test_is_nothrow_swappable_with<false, const volatile T, volatile U&>());
    static_assert(test_is_nothrow_swappable_with<false, const volatile T, volatile U&&>());
    static_assert(test_is_nothrow_swappable_with<false, const volatile T, const volatile U>());
    static_assert(test_is_nothrow_swappable_with<false, const volatile T, const volatile U&>());
    static_assert(test_is_nothrow_swappable_with<false, const volatile T, const volatile U&&>());
    static_assert(test_is_nothrow_swappable_with<false, T, Class>());
    static_assert(test_is_nothrow_swappable_with<false, T, const Class&>());
    static_assert(test_is_nothrow_swappable_with<false, const T, Class>());
    static_assert(test_is_nothrow_swappable_with<false, const T, const Class&>());
    static_assert(test_is_nothrow_swappable_with<false, volatile T, Class>());
    static_assert(test_is_nothrow_swappable_with<false, volatile T, const Class&>());
    static_assert(test_is_nothrow_swappable_with<false, const volatile T, Class>());
    static_assert(test_is_nothrow_swappable_with<false, const volatile T, const Class&>());
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
static_assert(test_is_nothrow_swappable_with<false, int (*)(int), void (*)(long, int)>());
static_assert(test_scalar<Class*>());
static_assert(test_scalar<int Class::*>());
static_assert(test_is_nothrow_swappable_with<false, int Class::*, Class Class::*>());
static_assert(test_scalar<Class Class::*>());
static_assert(test_scalar<Class * Class::*>());
static_assert(test_scalar<int (Class::*)(int, int)>());
static_assert(test_scalar<Class (Class::*)(int, Class Class::*)>());
static_assert(test_scalar<Class Class::* (Class::*)(int, int)>());
static_assert(test_is_nothrow_swappable_with<false, int (Class::*)(int, int), Class Class::* (Class::*)(int, int)>());
static_assert(test_scalar<Enum>());
static_assert(test_scalar<EnumClass>());
static_assert(test_is_nothrow_swappable_with<false, Enum, EnumClass>());
static_assert(test_is_nothrow_swappable_with<false, EnumClass, Enum>());
// endregion

// region array
static_assert(test_is_nothrow_swappable_with<false, int[10]>());
static_assert(test_is_nothrow_swappable_with<false, int[10][10]>());
static_assert(test_is_nothrow_swappable_with<false, int[10][10][10]>());
static_assert(test_is_nothrow_swappable_with<false, Class[10]>());
static_assert(test_is_nothrow_swappable_with<false, Class[10][10]>());
static_assert(test_is_nothrow_swappable_with<false, Class[10][10][10]>());
static_assert(test_is_nothrow_swappable_with<false, int[1], int>());
static_assert(test_is_nothrow_swappable_with<false, int[10], int>());
static_assert(test_is_nothrow_swappable_with<false, Class[1], Class>());
static_assert(test_is_nothrow_swappable_with<false, Class[10], Class>());
static_assert(test_is_nothrow_swappable_with<false, int[]>());
static_assert(test_is_nothrow_swappable_with<false, int[][10]>());
static_assert(test_is_nothrow_swappable_with<false, int[][10][10]>());
static_assert(test_is_nothrow_swappable_with<false, int[], int>());
static_assert(test_is_nothrow_swappable_with<false, int[][10], int>());
static_assert(test_is_nothrow_swappable_with<false, int[][1], int>());
// endregion

// region lvalue reference
static_assert(test_is_nothrow_swappable_with<true, int&>());
static_assert(test_is_nothrow_swappable_with<false, int&, const int&>());
static_assert(test_is_nothrow_swappable_with<false, int&, volatile int&>());
static_assert(test_is_nothrow_swappable_with<false, int&, const volatile int&>());
static_assert(test_is_nothrow_swappable_with<false, int&, int&&>());
static_assert(test_is_nothrow_swappable_with<false, int&, const int&&>());
static_assert(test_is_nothrow_swappable_with<false, int&, volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, int&, const volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, int&, int>());
static_assert(test_is_nothrow_swappable_with<false, int&, const int>());
static_assert(test_is_nothrow_swappable_with<false, int&, volatile int>());
static_assert(test_is_nothrow_swappable_with<false, int&, const volatile int>());

static_assert(test_is_nothrow_swappable_with<false, const int&>());
static_assert(test_is_nothrow_swappable_with<false, const int&, int&>());
static_assert(test_is_nothrow_swappable_with<false, const int&, const int&>());
static_assert(test_is_nothrow_swappable_with<false, const int&, volatile int&>());
static_assert(test_is_nothrow_swappable_with<false, const int&, const volatile int&>());
static_assert(test_is_nothrow_swappable_with<false, const int&, int&&>());
static_assert(test_is_nothrow_swappable_with<false, const int&, const int&&>());
static_assert(test_is_nothrow_swappable_with<false, const int&, volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, const int&, const volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, const int&, int>());
static_assert(test_is_nothrow_swappable_with<false, const int&, const int>());
static_assert(test_is_nothrow_swappable_with<false, const int&, volatile int>());
static_assert(test_is_nothrow_swappable_with<false, const int&, const volatile int>());

static_assert(test_is_nothrow_swappable_with<true, volatile int&>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&, int&>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&, const int&>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&, const volatile int&>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&, int&&>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&, const int&&>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&, volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&, const volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&, int>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&, const int>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&, volatile int>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&, const volatile int>());

static_assert(test_is_nothrow_swappable_with<false, const volatile int&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&, int&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&, const int&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&, volatile int&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&, const volatile int&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&, int&&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&, const int&&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&, volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&, const volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&, int>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&, const int>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&, volatile int>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&, const volatile int>());

static_assert(test_is_nothrow_swappable_with<false, int (&)()>());
static_assert(test_is_nothrow_swappable_with<false, int (&)(), int()>());
static_assert(test_is_nothrow_swappable_with<false, int (&)(), int(int)>());
static_assert(test_is_nothrow_swappable_with<false, int (&)(), int (&)()>());
static_assert(test_is_nothrow_swappable_with<false, int (&)(), int (&)(int)>());
static_assert(test_is_nothrow_swappable_with<false, int (&)(), int (&&)()>());
static_assert(test_is_nothrow_swappable_with<false, int (&)(), int (&&)(int)>());
// endregion

// region rvalue reference
static_assert(test_is_nothrow_swappable_with<false, int&&>());
static_assert(test_is_nothrow_swappable_with<false, int&&, int&>());
static_assert(test_is_nothrow_swappable_with<false, int&&, const int&>());
static_assert(test_is_nothrow_swappable_with<false, int&&, volatile int&>());
static_assert(test_is_nothrow_swappable_with<false, int&&, const volatile int&>());
static_assert(test_is_nothrow_swappable_with<false, int&&, int&&>());
static_assert(test_is_nothrow_swappable_with<false, int&&, const int&&>());
static_assert(test_is_nothrow_swappable_with<false, int&&, volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, int&&, const volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, int&&, int>());
static_assert(test_is_nothrow_swappable_with<false, int&&, const int>());
static_assert(test_is_nothrow_swappable_with<false, int&&, volatile int>());
static_assert(test_is_nothrow_swappable_with<false, int&&, const volatile int>());

static_assert(test_is_nothrow_swappable_with<false, const int&&>());
static_assert(test_is_nothrow_swappable_with<false, const int&&, int&>());
static_assert(test_is_nothrow_swappable_with<false, const int&&, const int&>());
static_assert(test_is_nothrow_swappable_with<false, const int&&, volatile int&>());
static_assert(test_is_nothrow_swappable_with<false, const int&&, const volatile int&>());
static_assert(test_is_nothrow_swappable_with<false, const int&&, int&&>());
static_assert(test_is_nothrow_swappable_with<false, const int&&, const int&&>());
static_assert(test_is_nothrow_swappable_with<false, const int&&, volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, const int&&, const volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, const int&&, int>());
static_assert(test_is_nothrow_swappable_with<false, const int&&, const int>());
static_assert(test_is_nothrow_swappable_with<false, const int&&, volatile int>());
static_assert(test_is_nothrow_swappable_with<false, const int&&, const volatile int>());

static_assert(test_is_nothrow_swappable_with<false, volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&&, int&>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&&, const int&>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&&, volatile int&>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&&, const volatile int&>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&&, int&&>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&&, const int&&>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&&, volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&&, const volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&&, int>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&&, const int>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&&, volatile int>());
static_assert(test_is_nothrow_swappable_with<false, volatile int&&, const volatile int>());

static_assert(test_is_nothrow_swappable_with<false, const volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&&, int&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&&, const int&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&&, volatile int&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&&, const volatile int&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&&, int&&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&&, const int&&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&&, volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&&, const volatile int&&>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&&, int>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&&, const int>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&&, volatile int>());
static_assert(test_is_nothrow_swappable_with<false, const volatile int&&, const volatile int>());

static_assert(test_is_nothrow_swappable_with<false, int (&&)()>());
static_assert(test_is_nothrow_swappable_with<false, int (&&)(), int()>());
static_assert(test_is_nothrow_swappable_with<false, int (&&)(), int(int)>());
static_assert(test_is_nothrow_swappable_with<false, int (&&)(), int (&)()>());
static_assert(test_is_nothrow_swappable_with<false, int (&&)(), int (&)(int)>());
static_assert(test_is_nothrow_swappable_with<false, int (&&)(), int (&&)()>());
static_assert(test_is_nothrow_swappable_with<false, int (&&)(), int (&&)(int)>());
// endregion

// region union
static_assert(test_is_nothrow_swappable_with<false, Union, Union>());
// endregion

// region class
static_assert(test_is_nothrow_swappable_with<false, Class, Class>());
// endregion

// region function
static_assert(test_is_nothrow_swappable_with<false, int(), int()>());
static_assert(test_is_nothrow_swappable_with<false, int(), int (&)()>());
static_assert(test_is_nothrow_swappable_with<false, int(), int (&&)()>());
static_assert(test_is_nothrow_swappable_with<false, int(), int(int, int)>());
static_assert(test_is_nothrow_swappable_with<false, int(), int (&)(int, int)>());
static_assert(test_is_nothrow_swappable_with<false, int(), int (&&)(int, int)>());
// endregion