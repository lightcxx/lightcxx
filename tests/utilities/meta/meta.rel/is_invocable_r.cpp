#include <type_traits>

#include "testing.h"

// TODO: Test with std::reference_wrapper once implemented.

template<bool e, class... T>
constexpr void expect_is_invocable_r() {
    static_assert(std::is_invocable_r<T...>::value == e);
    static_assert(std::is_base_of_v<std::bool_constant<e>, std::is_invocable_r<T...>>);
    static_assert(std::is_same_v<typename std::is_invocable_r<T...>::value_type, bool>);
    static_assert(std::is_invocable_r<T...>{} == e);
    static_assert(static_cast<bool>(std::is_invocable_r<T...>{}) == e);
    static_assert(noexcept(static_cast<bool>(std::is_invocable_r<T...>{})));
    static_assert(std::is_invocable_r<T...>{}() == e);
    static_assert(noexcept(std::is_invocable_r<T...>{}()));
    static_assert(std::is_same_v<bool, decltype(std::is_invocable_r<T...>{}())>);
    static_assert(std::is_same_v<typename std::is_invocable_r<T...>::type, std::bool_constant<e>>);
    static_assert(std::is_same_v<decltype(std::is_invocable_r_v<T...>), const bool>);
    static_assert(std::is_invocable_r_v<T...> == e);
}

TEST(function) {
    using Func = int(int, long);
    expect_is_invocable_r<true, int, Func, int, long>();
    expect_is_invocable_r<true, int, Func*, int, long>();
    expect_is_invocable_r<true, int, Func* const, int, long>();
    expect_is_invocable_r<true, int, Func&, int, long>();
    expect_is_invocable_r<true, int, Func&&, int, long>();
    // implicit conversions
    expect_is_invocable_r<true, int, Func, long, int>();
    expect_is_invocable_r<true, int, Func, long, double>();
    expect_is_invocable_r<true, long, Func, int, long>();
    expect_is_invocable_r<true, void, Func, int, long>();
    expect_is_invocable_r<true, const void, Func, int, long>();
    expect_is_invocable_r<true, volatile void, Func, int, long>();
    expect_is_invocable_r<true, const volatile void, Func, int, long>();
    // Invalid calls
    expect_is_invocable_r<false, int, Func, int>();
    expect_is_invocable_r<false, int, Func, int, long, double>();
    expect_is_invocable_r<false, int, Func, Func, Func>();

    using NoexceptFunc = int(int, long) noexcept;
    expect_is_invocable_r<true, int, NoexceptFunc, int, long>();
    expect_is_invocable_r<true, int, NoexceptFunc*, int, long>();
    expect_is_invocable_r<true, int, NoexceptFunc* const, int, long>();
    expect_is_invocable_r<true, int, NoexceptFunc&, int, long>();
    expect_is_invocable_r<true, int, NoexceptFunc&&, int, long>();
    // implicit conversions
    expect_is_invocable_r<true, int, NoexceptFunc, long, int>();
    expect_is_invocable_r<true, int, NoexceptFunc, long, double>();
    expect_is_invocable_r<true, long, NoexceptFunc, int, long>();
    expect_is_invocable_r<true, void, NoexceptFunc, int, long>();
    expect_is_invocable_r<true, const void, NoexceptFunc, int, long>();
    expect_is_invocable_r<true, volatile void, NoexceptFunc, int, long>();
    expect_is_invocable_r<true, const volatile void, NoexceptFunc, int, long>();
    // Invalid calls
    expect_is_invocable_r<false, int, NoexceptFunc, int>();
    expect_is_invocable_r<false, int, NoexceptFunc, int, long, double>();
    expect_is_invocable_r<false, int, NoexceptFunc, NoexceptFunc, Func>();
}

TEST(functor) {
    struct Ftor {
        int operator()(int, long) {
            return 0;
        }
    };
    expect_is_invocable_r<true, int, Ftor, int, long>();
    expect_is_invocable_r<false, int, const Ftor, int, long>();
    expect_is_invocable_r<false, int, Ftor*, int, long>();
    expect_is_invocable_r<false, int, Ftor* const, int, long>();
    expect_is_invocable_r<false, int, const Ftor*, int, long>();
    expect_is_invocable_r<false, int, const Ftor* const, int, long>();
    expect_is_invocable_r<true, int, Ftor&, int, long>();
    expect_is_invocable_r<false, int, const Ftor&, int, long>();
    expect_is_invocable_r<true, int, Ftor&&, int, long>();
    expect_is_invocable_r<false, int, const Ftor&&, int, long>();
    // implicit conversions
    expect_is_invocable_r<true, int, Ftor, long, int>();
    expect_is_invocable_r<true, int, Ftor, long, double>();
    expect_is_invocable_r<true, long, Ftor, int, long>();
    expect_is_invocable_r<true, void, Ftor, int, long>();
    expect_is_invocable_r<true, const void, Ftor, int, long>();
    expect_is_invocable_r<true, volatile void, Ftor, int, long>();
    expect_is_invocable_r<true, const volatile void, Ftor, int, long>();
    // Invalid calls
    expect_is_invocable_r<false, int, Ftor, int>();
    expect_is_invocable_r<false, int, Ftor, int, long, double>();
    expect_is_invocable_r<false, int, Ftor, Ftor, Ftor>();

    struct ConstFtor {
        int operator()(int, long) const {
            return 0;
        }
    };
    expect_is_invocable_r<true, int, ConstFtor, int, long>();
    expect_is_invocable_r<true, int, const ConstFtor, int, long>();
    expect_is_invocable_r<false, int, ConstFtor*, int, long>();
    expect_is_invocable_r<false, int, ConstFtor* const, int, long>();
    expect_is_invocable_r<false, int, const ConstFtor*, int, long>();
    expect_is_invocable_r<false, int, const ConstFtor* const, int, long>();
    expect_is_invocable_r<true, int, ConstFtor&, int, long>();
    expect_is_invocable_r<true, int, const ConstFtor&, int, long>();
    expect_is_invocable_r<true, int, ConstFtor&&, int, long>();
    expect_is_invocable_r<true, int, const ConstFtor&&, int, long>();
    // implicit conversions
    expect_is_invocable_r<true, int, ConstFtor, long, int>();
    expect_is_invocable_r<true, int, ConstFtor, long, double>();
    expect_is_invocable_r<true, long, ConstFtor, int, long>();
    expect_is_invocable_r<true, void, ConstFtor, int, long>();
    expect_is_invocable_r<true, const void, ConstFtor, int, long>();
    expect_is_invocable_r<true, volatile void, ConstFtor, int, long>();
    expect_is_invocable_r<true, const volatile void, ConstFtor, int, long>();
    // Invalid calls
    expect_is_invocable_r<false, int, ConstFtor, int>();
    expect_is_invocable_r<false, int, ConstFtor, int, long, double>();
    expect_is_invocable_r<false, int, ConstFtor, ConstFtor, ConstFtor>();

    constexpr auto lambda = [](int, long) noexcept -> int { return 0; };
    using Lambda = decltype(lambda);
    expect_is_invocable_r<true, int, Lambda, int, long>();
    expect_is_invocable_r<true, int, const Lambda, int, long>();
    expect_is_invocable_r<false, int, Lambda*, int, long>();
    expect_is_invocable_r<false, int, Lambda* const, int, long>();
    expect_is_invocable_r<false, int, const Lambda*, int, long>();
    expect_is_invocable_r<false, int, const Lambda* const, int, long>();
    expect_is_invocable_r<true, int, Lambda&, int, long>();
    expect_is_invocable_r<true, int, const Lambda&, int, long>();
    expect_is_invocable_r<true, int, Lambda&&, int, long>();
    expect_is_invocable_r<true, int, const Lambda&&, int, long>();
    // implicit conversions
    expect_is_invocable_r<true, int, Lambda, long, int>();
    expect_is_invocable_r<true, int, Lambda, long, double>();
    expect_is_invocable_r<true, long, Lambda, int, long>();
    expect_is_invocable_r<true, void, Lambda, int, long>();
    expect_is_invocable_r<true, const void, Lambda, int, long>();
    expect_is_invocable_r<true, volatile void, Lambda, int, long>();
    expect_is_invocable_r<true, const volatile void, Lambda, int, long>();
    // Invalid calls
    expect_is_invocable_r<false, int, Lambda, int>();
    expect_is_invocable_r<false, int, Lambda, int, long, double>();
    expect_is_invocable_r<false, int, Lambda, Lambda, Lambda>();
}

TEST(member_function_pointer) {
    struct A {
        int f(int, long) {
            return 0;
        }
        int g(int, long) const {
            return 0;
        }
        int h(int, long) noexcept {
            return 0;
        }
        int i(int, long) const noexcept {
            return 0;
        }
    };
    using MemFPtr = decltype(&A::f);
    using ConstMemFPtr = decltype(&A::g);
    using NothrowMemFPtr = decltype(&A::h);
    using NothrowConstMemFPtr = decltype(&A::i);

    expect_is_invocable_r<true, int, MemFPtr, A, int, long>();
    expect_is_invocable_r<false, int, MemFPtr, const A, int, long>();
    expect_is_invocable_r<true, int, MemFPtr, A&, int, long>();
    expect_is_invocable_r<false, int, MemFPtr, const A&, int, long>();
    expect_is_invocable_r<true, int, MemFPtr, A&&, int, long>();
    expect_is_invocable_r<false, int, MemFPtr, const A&&, int, long>();
    // implicit conversions
    expect_is_invocable_r<true, int, MemFPtr, A, long, int>();
    expect_is_invocable_r<true, int, MemFPtr, A, long, double>();
    expect_is_invocable_r<true, long, MemFPtr, A, int, long>();
    expect_is_invocable_r<true, void, MemFPtr, A, int, long>();
    expect_is_invocable_r<true, const void, MemFPtr, A, int, long>();
    expect_is_invocable_r<true, volatile void, MemFPtr, A, int, long>();
    expect_is_invocable_r<true, const volatile void, MemFPtr, A, int, long>();
    // Invalid calls
    expect_is_invocable_r<false, int, MemFPtr, A, int>();
    expect_is_invocable_r<false, int, MemFPtr, A, int, long, double>();
    expect_is_invocable_r<false, int, MemFPtr, A, MemFPtr, MemFPtr>();

    expect_is_invocable_r<true, int, ConstMemFPtr, A, int, long>();
    expect_is_invocable_r<true, int, ConstMemFPtr, const A, int, long>();
    expect_is_invocable_r<true, int, ConstMemFPtr, A&, int, long>();
    expect_is_invocable_r<true, int, ConstMemFPtr, const A&, int, long>();
    expect_is_invocable_r<true, int, ConstMemFPtr, A&&, int, long>();
    expect_is_invocable_r<true, int, ConstMemFPtr, const A&&, int, long>();
    // implicit conversions
    expect_is_invocable_r<true, int, ConstMemFPtr, A, long, int>();
    expect_is_invocable_r<true, int, ConstMemFPtr, A, long, double>();
    expect_is_invocable_r<true, long, ConstMemFPtr, A, int, long>();
    expect_is_invocable_r<true, void, ConstMemFPtr, A, int, long>();
    expect_is_invocable_r<true, const void, ConstMemFPtr, A, int, long>();
    expect_is_invocable_r<true, volatile void, ConstMemFPtr, A, int, long>();
    expect_is_invocable_r<true, const volatile void, ConstMemFPtr, A, int, long>();
    // Invalid calls
    expect_is_invocable_r<false, int, ConstMemFPtr, A, int>();
    expect_is_invocable_r<false, int, ConstMemFPtr, A, int, long, double>();
    expect_is_invocable_r<false, int, ConstMemFPtr, A, MemFPtr, MemFPtr>();

    expect_is_invocable_r<true, int, NothrowMemFPtr, A, int, long>();
    expect_is_invocable_r<false, int, NothrowMemFPtr, const A, int, long>();
    expect_is_invocable_r<true, int, NothrowMemFPtr, A&, int, long>();
    expect_is_invocable_r<false, int, NothrowMemFPtr, const A&, int, long>();
    expect_is_invocable_r<true, int, NothrowMemFPtr, A&&, int, long>();
    expect_is_invocable_r<false, int, NothrowMemFPtr, const A&&, int, long>();
    // implicit conversions
    expect_is_invocable_r<true, int, NothrowMemFPtr, A, long, int>();
    expect_is_invocable_r<true, int, NothrowMemFPtr, A, long, double>();
    expect_is_invocable_r<true, long, NothrowMemFPtr, A, int, long>();
    expect_is_invocable_r<true, void, NothrowMemFPtr, A, int, long>();
    expect_is_invocable_r<true, const void, NothrowMemFPtr, A, int, long>();
    expect_is_invocable_r<true, volatile void, NothrowMemFPtr, A, int, long>();
    expect_is_invocable_r<true, const volatile void, NothrowMemFPtr, A, int, long>();
    // Invalid calls
    expect_is_invocable_r<false, int, NothrowMemFPtr, A, int>();
    expect_is_invocable_r<false, int, NothrowMemFPtr, A, int, long, double>();
    expect_is_invocable_r<false, int, NothrowMemFPtr, A, MemFPtr, MemFPtr>();

    expect_is_invocable_r<true, int, NothrowConstMemFPtr, A, int, long>();
    expect_is_invocable_r<true, int, NothrowConstMemFPtr, const A, int, long>();
    expect_is_invocable_r<true, int, NothrowConstMemFPtr, A&, int, long>();
    expect_is_invocable_r<true, int, NothrowConstMemFPtr, const A&, int, long>();
    expect_is_invocable_r<true, int, NothrowConstMemFPtr, A&&, int, long>();
    expect_is_invocable_r<true, int, NothrowConstMemFPtr, const A&&, int, long>();
    // implicit conversions
    expect_is_invocable_r<true, int, NothrowConstMemFPtr, A, long, int>();
    expect_is_invocable_r<true, int, NothrowConstMemFPtr, A, long, double>();
    expect_is_invocable_r<true, long, NothrowConstMemFPtr, A, int, long>();
    expect_is_invocable_r<true, void, NothrowConstMemFPtr, A, int, long>();
    expect_is_invocable_r<true, const void, NothrowConstMemFPtr, A, int, long>();
    expect_is_invocable_r<true, volatile void, NothrowConstMemFPtr, A, int, long>();
    expect_is_invocable_r<true, const volatile void, NothrowConstMemFPtr, A, int, long>();
    // Invalid calls
    expect_is_invocable_r<false, int, NothrowConstMemFPtr, A, int>();
    expect_is_invocable_r<false, int, NothrowConstMemFPtr, A, int, long, double>();
    expect_is_invocable_r<false, int, NothrowConstMemFPtr, A, MemFPtr, MemFPtr>();

    // With subclass
    struct B : A {};

    expect_is_invocable_r<true, int, MemFPtr, B, int, long>();
    expect_is_invocable_r<false, int, MemFPtr, const B, int, long>();
    expect_is_invocable_r<true, int, MemFPtr, B&, int, long>();
    expect_is_invocable_r<false, int, MemFPtr, const B&, int, long>();
    expect_is_invocable_r<true, int, MemFPtr, B&&, int, long>();
    expect_is_invocable_r<false, int, MemFPtr, const B&&, int, long>();
    // implicit conversions
    expect_is_invocable_r<true, int, MemFPtr, B, long, int>();
    expect_is_invocable_r<true, int, MemFPtr, B, long, double>();
    expect_is_invocable_r<true, long, MemFPtr, B, int, long>();
    expect_is_invocable_r<true, void, MemFPtr, B, int, long>();
    expect_is_invocable_r<true, const void, MemFPtr, B, int, long>();
    expect_is_invocable_r<true, volatile void, MemFPtr, B, int, long>();
    expect_is_invocable_r<true, const volatile void, MemFPtr, B, int, long>();
    // Invalid calls
    expect_is_invocable_r<false, int, MemFPtr, B, int>();
    expect_is_invocable_r<false, int, MemFPtr, B, int, long, double>();
    expect_is_invocable_r<false, int, MemFPtr, B, MemFPtr, MemFPtr>();

    expect_is_invocable_r<true, int, ConstMemFPtr, B, int, long>();
    expect_is_invocable_r<true, int, ConstMemFPtr, const B, int, long>();
    expect_is_invocable_r<true, int, ConstMemFPtr, B&, int, long>();
    expect_is_invocable_r<true, int, ConstMemFPtr, const B&, int, long>();
    expect_is_invocable_r<true, int, ConstMemFPtr, B&&, int, long>();
    expect_is_invocable_r<true, int, ConstMemFPtr, const B&&, int, long>();
    // implicit conversions
    expect_is_invocable_r<true, int, ConstMemFPtr, B, long, int>();
    expect_is_invocable_r<true, int, ConstMemFPtr, B, long, double>();
    expect_is_invocable_r<true, long, ConstMemFPtr, B, int, long>();
    expect_is_invocable_r<true, void, ConstMemFPtr, B, int, long>();
    expect_is_invocable_r<true, const void, ConstMemFPtr, B, int, long>();
    expect_is_invocable_r<true, volatile void, ConstMemFPtr, B, int, long>();
    expect_is_invocable_r<true, const volatile void, ConstMemFPtr, B, int, long>();
    // Invalid calls
    expect_is_invocable_r<false, int, ConstMemFPtr, B, int>();
    expect_is_invocable_r<false, int, ConstMemFPtr, B, int, long, double>();
    expect_is_invocable_r<false, int, ConstMemFPtr, B, MemFPtr, MemFPtr>();

    expect_is_invocable_r<true, int, NothrowMemFPtr, B, int, long>();
    expect_is_invocable_r<false, int, NothrowMemFPtr, const B, int, long>();
    expect_is_invocable_r<true, int, NothrowMemFPtr, B&, int, long>();
    expect_is_invocable_r<false, int, NothrowMemFPtr, const B&, int, long>();
    expect_is_invocable_r<true, int, NothrowMemFPtr, B&&, int, long>();
    expect_is_invocable_r<false, int, NothrowMemFPtr, const B&&, int, long>();
    // implicit conversions
    expect_is_invocable_r<true, int, NothrowMemFPtr, B, long, int>();
    expect_is_invocable_r<true, int, NothrowMemFPtr, B, long, double>();
    expect_is_invocable_r<true, long, NothrowMemFPtr, B, int, long>();
    expect_is_invocable_r<true, void, NothrowMemFPtr, B, int, long>();
    expect_is_invocable_r<true, const void, NothrowMemFPtr, B, int, long>();
    expect_is_invocable_r<true, volatile void, NothrowMemFPtr, B, int, long>();
    expect_is_invocable_r<true, const volatile void, NothrowMemFPtr, B, int, long>();
    // Invalid calls
    expect_is_invocable_r<false, int, NothrowMemFPtr, B, int>();
    expect_is_invocable_r<false, int, NothrowMemFPtr, B, int, long, double>();
    expect_is_invocable_r<false, int, NothrowMemFPtr, B, MemFPtr, MemFPtr>();

    expect_is_invocable_r<true, int, NothrowConstMemFPtr, B, int, long>();
    expect_is_invocable_r<true, int, NothrowConstMemFPtr, const B, int, long>();
    expect_is_invocable_r<true, int, NothrowConstMemFPtr, B&, int, long>();
    expect_is_invocable_r<true, int, NothrowConstMemFPtr, const B&, int, long>();
    expect_is_invocable_r<true, int, NothrowConstMemFPtr, B&&, int, long>();
    expect_is_invocable_r<true, int, NothrowConstMemFPtr, const B&&, int, long>();
    // implicit conversions
    expect_is_invocable_r<true, int, NothrowConstMemFPtr, B, long, int>();
    expect_is_invocable_r<true, int, NothrowConstMemFPtr, B, long, double>();
    expect_is_invocable_r<true, long, NothrowConstMemFPtr, B, int, long>();
    expect_is_invocable_r<true, void, NothrowConstMemFPtr, B, int, long>();
    expect_is_invocable_r<true, const void, NothrowConstMemFPtr, B, int, long>();
    expect_is_invocable_r<true, volatile void, NothrowConstMemFPtr, B, int, long>();
    expect_is_invocable_r<true, const volatile void, NothrowConstMemFPtr, B, int, long>();
    // Invalid calls
    expect_is_invocable_r<false, int, NothrowConstMemFPtr, B, int>();
    expect_is_invocable_r<false, int, NothrowConstMemFPtr, B, int, long, double>();
    expect_is_invocable_r<false, int, NothrowConstMemFPtr, B, MemFPtr, MemFPtr>();
}

#ifndef _LIGHTCXX_BUILTINS_DONT_USE_ANY
TEST(member_data_pointer) {
    struct A {
        int f;
    };
    using MemDPtr = decltype(&A::f);

    expect_is_invocable_r<true, int, MemDPtr, A>();
    expect_is_invocable_r<true, int, MemDPtr, const A>();
    expect_is_invocable_r<true, int, MemDPtr, A&>();
    expect_is_invocable_r<true, int, MemDPtr, const A&>();
    expect_is_invocable_r<true, int, MemDPtr, A&&>();
    expect_is_invocable_r<true, int, MemDPtr, const A&&>();
    // Implicit conversions
    expect_is_invocable_r<true, long, MemDPtr, A>();
    expect_is_invocable_r<true, void, MemDPtr, A>();
    expect_is_invocable_r<true, const void, MemDPtr, A>();
    expect_is_invocable_r<true, volatile void, MemDPtr, A>();
    expect_is_invocable_r<true, const volatile void, MemDPtr, A>();
    // Invalid calls
    expect_is_invocable_r<false, int, MemDPtr, A, int, long, double>();  // Too many args
    expect_is_invocable_r<false, int, MemDPtr, int>();                   // Invalid argument type

    // With subclass
    struct B : A {};

    expect_is_invocable_r<true, int, MemDPtr, B>();
    expect_is_invocable_r<true, int, MemDPtr, const B>();
    expect_is_invocable_r<true, int, MemDPtr, B&>();
    expect_is_invocable_r<true, int, MemDPtr, const B&>();
    expect_is_invocable_r<true, int, MemDPtr, B&&>();
    expect_is_invocable_r<true, int, MemDPtr, const B&&>();
    // Implicit conversions
    expect_is_invocable_r<true, long, MemDPtr, B>();
    expect_is_invocable_r<true, void, MemDPtr, B>();
    expect_is_invocable_r<true, const void, MemDPtr, B>();
    expect_is_invocable_r<true, volatile void, MemDPtr, B>();
    expect_is_invocable_r<true, const volatile void, MemDPtr, B>();
    // Invalid calls
    expect_is_invocable_r<false, int, MemDPtr, B, int, long, double>();  // Too many args
    expect_is_invocable_r<false, int, MemDPtr, int>();                   // Invalid argument type
}
#endif
