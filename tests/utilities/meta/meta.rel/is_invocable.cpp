#include <type_traits>

#include "testing.h"

// TODO: Test with std::reference_wrapper once implemented.

template<bool e, class... T>
constexpr void expect_is_invocable() {
    static_assert(std::is_invocable<T...>::value == e);
    static_assert(std::is_base_of_v<std::bool_constant<e>, std::is_invocable<T...>>);
    static_assert(std::is_same_v<typename std::is_invocable<T...>::value_type, bool>);
    static_assert(std::is_invocable<T...>{} == e);
    static_assert((bool)std::is_invocable<T...>{} == e);
    static_assert(noexcept((bool)std::is_invocable<T...>{}));
    static_assert(std::is_invocable<T...>{}() == e);
    static_assert(noexcept(std::is_invocable<T...>{}()));
    static_assert(std::is_same_v<bool, decltype(std::is_invocable<T...>{}())>);
    static_assert(std::is_same_v<typename std::is_invocable<T...>::type, std::bool_constant<e>>);
    static_assert(std::is_same_v<decltype(std::is_invocable_v<T...>), const bool>);
    static_assert(std::is_invocable_v<T...> == e);
}

TEST(function) {
    using Func = int(int, long);
    expect_is_invocable<true, Func, int, long>();
    expect_is_invocable<true, Func*, int, long>();
    expect_is_invocable<true, Func* const, int, long>();
    expect_is_invocable<true, Func&, int, long>();
    expect_is_invocable<true, Func&&, int, long>();
    // implicit conversions
    expect_is_invocable<true, Func, long, int>();
    expect_is_invocable<true, Func, long, double>();
    // Invalid calls
    expect_is_invocable<false, Func, int>();
    expect_is_invocable<false, Func, int, long, double>();
    expect_is_invocable<false, Func, Func, Func>();

    using NoexceptFunc = int(int, long) noexcept;
    expect_is_invocable<true, NoexceptFunc, int, long>();
    expect_is_invocable<true, NoexceptFunc*, int, long>();
    expect_is_invocable<true, NoexceptFunc* const, int, long>();
    expect_is_invocable<true, NoexceptFunc&, int, long>();
    expect_is_invocable<true, NoexceptFunc&&, int, long>();
    // implicit conversions
    expect_is_invocable<true, NoexceptFunc, long, int>();
    expect_is_invocable<true, NoexceptFunc, long, double>();
    // Invalid calls
    expect_is_invocable<false, NoexceptFunc, int>();
    expect_is_invocable<false, NoexceptFunc, int, long, double>();
    expect_is_invocable<false, NoexceptFunc, NoexceptFunc, Func>();
}

TEST(functor) {
    struct Ftor {
        int operator()(int, long) {
            return 0;
        }
    };
    expect_is_invocable<true, Ftor, int, long>();
    expect_is_invocable<false, const Ftor, int, long>();
    expect_is_invocable<false, Ftor*, int, long>();
    expect_is_invocable<false, Ftor* const, int, long>();
    expect_is_invocable<false, const Ftor*, int, long>();
    expect_is_invocable<false, const Ftor* const, int, long>();
    expect_is_invocable<true, Ftor&, int, long>();
    expect_is_invocable<false, const Ftor&, int, long>();
    expect_is_invocable<true, Ftor&&, int, long>();
    expect_is_invocable<false, const Ftor&&, int, long>();
    // implicit conversions
    expect_is_invocable<true, Ftor, long, int>();
    expect_is_invocable<true, Ftor, long, double>();
    // Invalid calls
    expect_is_invocable<false, Ftor, int>();
    expect_is_invocable<false, Ftor, int, long, double>();
    expect_is_invocable<false, Ftor, Ftor, Ftor>();

    struct ConstFtor {
        int operator()(int, long) const {
            return 0;
        }
    };
    expect_is_invocable<true, ConstFtor, int, long>();
    expect_is_invocable<true, const ConstFtor, int, long>();
    expect_is_invocable<false, ConstFtor*, int, long>();
    expect_is_invocable<false, ConstFtor* const, int, long>();
    expect_is_invocable<false, const ConstFtor*, int, long>();
    expect_is_invocable<false, const ConstFtor* const, int, long>();
    expect_is_invocable<true, ConstFtor&, int, long>();
    expect_is_invocable<true, const ConstFtor&, int, long>();
    expect_is_invocable<true, ConstFtor&&, int, long>();
    expect_is_invocable<true, const ConstFtor&&, int, long>();
    // implicit conversions
    expect_is_invocable<true, ConstFtor, long, int>();
    expect_is_invocable<true, ConstFtor, long, double>();
    // Invalid calls
    expect_is_invocable<false, ConstFtor, int>();
    expect_is_invocable<false, ConstFtor, int, long, double>();
    expect_is_invocable<false, ConstFtor, ConstFtor, ConstFtor>();

    constexpr auto lambda = [](int, long) noexcept -> int { return 0; };
    using Lambda = decltype(lambda);
    expect_is_invocable<true, Lambda, int, long>();
    expect_is_invocable<true, const Lambda, int, long>();
    expect_is_invocable<false, Lambda*, int, long>();
    expect_is_invocable<false, Lambda* const, int, long>();
    expect_is_invocable<false, const Lambda*, int, long>();
    expect_is_invocable<false, const Lambda* const, int, long>();
    expect_is_invocable<true, Lambda&, int, long>();
    expect_is_invocable<true, const Lambda&, int, long>();
    expect_is_invocable<true, Lambda&&, int, long>();
    expect_is_invocable<true, const Lambda&&, int, long>();
    // implicit conversions
    expect_is_invocable<true, Lambda, long, int>();
    expect_is_invocable<true, Lambda, long, double>();
    // Invalid calls
    expect_is_invocable<false, Lambda, int>();
    expect_is_invocable<false, Lambda, int, long, double>();
    expect_is_invocable<false, Lambda, Lambda, Lambda>();
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

    expect_is_invocable<true, MemFPtr, A, int, long>();
    expect_is_invocable<false, MemFPtr, const A, int, long>();
    expect_is_invocable<true, MemFPtr, A&, int, long>();
    expect_is_invocable<false, MemFPtr, const A&, int, long>();
    expect_is_invocable<true, MemFPtr, A&&, int, long>();
    expect_is_invocable<false, MemFPtr, const A&&, int, long>();
    // implicit conversions
    expect_is_invocable<true, MemFPtr, A, long, int>();
    expect_is_invocable<true, MemFPtr, A, long, double>();
    // Invalid calls
    expect_is_invocable<false, MemFPtr, A, int>();
    expect_is_invocable<false, MemFPtr, A, int, long, double>();
    expect_is_invocable<false, MemFPtr, A, MemFPtr, MemFPtr>();

    expect_is_invocable<true, ConstMemFPtr, A, int, long>();
    expect_is_invocable<true, ConstMemFPtr, const A, int, long>();
    expect_is_invocable<true, ConstMemFPtr, A&, int, long>();
    expect_is_invocable<true, ConstMemFPtr, const A&, int, long>();
    expect_is_invocable<true, ConstMemFPtr, A&&, int, long>();
    expect_is_invocable<true, ConstMemFPtr, const A&&, int, long>();
    // implicit conversions
    expect_is_invocable<true, ConstMemFPtr, A, long, int>();
    expect_is_invocable<true, ConstMemFPtr, A, long, double>();
    // Invalid calls
    expect_is_invocable<false, ConstMemFPtr, A, int>();
    expect_is_invocable<false, ConstMemFPtr, A, int, long, double>();
    expect_is_invocable<false, ConstMemFPtr, A, MemFPtr, MemFPtr>();

    expect_is_invocable<true, NothrowMemFPtr, A, int, long>();
    expect_is_invocable<false, NothrowMemFPtr, const A, int, long>();
    expect_is_invocable<true, NothrowMemFPtr, A&, int, long>();
    expect_is_invocable<false, NothrowMemFPtr, const A&, int, long>();
    expect_is_invocable<true, NothrowMemFPtr, A&&, int, long>();
    expect_is_invocable<false, NothrowMemFPtr, const A&&, int, long>();
    // implicit conversions
    expect_is_invocable<true, NothrowMemFPtr, A, long, int>();
    expect_is_invocable<true, NothrowMemFPtr, A, long, double>();
    // Invalid calls
    expect_is_invocable<false, NothrowMemFPtr, A, int>();
    expect_is_invocable<false, NothrowMemFPtr, A, int, long, double>();
    expect_is_invocable<false, NothrowMemFPtr, A, MemFPtr, MemFPtr>();

    expect_is_invocable<true, NothrowConstMemFPtr, A, int, long>();
    expect_is_invocable<true, NothrowConstMemFPtr, const A, int, long>();
    expect_is_invocable<true, NothrowConstMemFPtr, A&, int, long>();
    expect_is_invocable<true, NothrowConstMemFPtr, const A&, int, long>();
    expect_is_invocable<true, NothrowConstMemFPtr, A&&, int, long>();
    expect_is_invocable<true, NothrowConstMemFPtr, const A&&, int, long>();
    // implicit conversions
    expect_is_invocable<true, NothrowConstMemFPtr, A, long, int>();
    expect_is_invocable<true, NothrowConstMemFPtr, A, long, double>();
    // Invalid calls
    expect_is_invocable<false, NothrowConstMemFPtr, A, int>();
    expect_is_invocable<false, NothrowConstMemFPtr, A, int, long, double>();
    expect_is_invocable<false, NothrowConstMemFPtr, A, MemFPtr, MemFPtr>();

    // With subclass
    struct B : A {};

    expect_is_invocable<true, MemFPtr, B, int, long>();
    expect_is_invocable<false, MemFPtr, const B, int, long>();
    expect_is_invocable<true, MemFPtr, B&, int, long>();
    expect_is_invocable<false, MemFPtr, const B&, int, long>();
    expect_is_invocable<true, MemFPtr, B&&, int, long>();
    expect_is_invocable<false, MemFPtr, const B&&, int, long>();
    // implicit conversions
    expect_is_invocable<true, MemFPtr, B, long, int>();
    expect_is_invocable<true, MemFPtr, B, long, double>();
    // Invalid calls
    expect_is_invocable<false, MemFPtr, B, int>();
    expect_is_invocable<false, MemFPtr, B, int, long, double>();
    expect_is_invocable<false, MemFPtr, B, MemFPtr, MemFPtr>();

    expect_is_invocable<true, ConstMemFPtr, B, int, long>();
    expect_is_invocable<true, ConstMemFPtr, const B, int, long>();
    expect_is_invocable<true, ConstMemFPtr, B&, int, long>();
    expect_is_invocable<true, ConstMemFPtr, const B&, int, long>();
    expect_is_invocable<true, ConstMemFPtr, B&&, int, long>();
    expect_is_invocable<true, ConstMemFPtr, const B&&, int, long>();
    // implicit conversions
    expect_is_invocable<true, ConstMemFPtr, B, long, int>();
    expect_is_invocable<true, ConstMemFPtr, B, long, double>();
    // Invalid calls
    expect_is_invocable<false, ConstMemFPtr, B, int>();
    expect_is_invocable<false, ConstMemFPtr, B, int, long, double>();
    expect_is_invocable<false, ConstMemFPtr, B, MemFPtr, MemFPtr>();

    expect_is_invocable<true, NothrowMemFPtr, B, int, long>();
    expect_is_invocable<false, NothrowMemFPtr, const B, int, long>();
    expect_is_invocable<true, NothrowMemFPtr, B&, int, long>();
    expect_is_invocable<false, NothrowMemFPtr, const B&, int, long>();
    expect_is_invocable<true, NothrowMemFPtr, B&&, int, long>();
    expect_is_invocable<false, NothrowMemFPtr, const B&&, int, long>();
    // implicit conversions
    expect_is_invocable<true, NothrowMemFPtr, B, long, int>();
    expect_is_invocable<true, NothrowMemFPtr, B, long, double>();
    // Invalid calls
    expect_is_invocable<false, NothrowMemFPtr, B, int>();
    expect_is_invocable<false, NothrowMemFPtr, B, int, long, double>();
    expect_is_invocable<false, NothrowMemFPtr, B, MemFPtr, MemFPtr>();

    expect_is_invocable<true, NothrowConstMemFPtr, B, int, long>();
    expect_is_invocable<true, NothrowConstMemFPtr, const B, int, long>();
    expect_is_invocable<true, NothrowConstMemFPtr, B&, int, long>();
    expect_is_invocable<true, NothrowConstMemFPtr, const B&, int, long>();
    expect_is_invocable<true, NothrowConstMemFPtr, B&&, int, long>();
    expect_is_invocable<true, NothrowConstMemFPtr, const B&&, int, long>();
    // implicit conversions
    expect_is_invocable<true, NothrowConstMemFPtr, B, long, int>();
    expect_is_invocable<true, NothrowConstMemFPtr, B, long, double>();
    // Invalid calls
    expect_is_invocable<false, NothrowConstMemFPtr, B, int>();
    expect_is_invocable<false, NothrowConstMemFPtr, B, int, long, double>();
    expect_is_invocable<false, NothrowConstMemFPtr, B, MemFPtr, MemFPtr>();
}

#ifndef _LIGHTCXX_BUILTINS_DONT_USE_ANY
TEST(member_data_pointer) {
    struct A {
        int f;
    };
    using MemDPtr = decltype(&A::f);

    expect_is_invocable<true, MemDPtr, A>();
    expect_is_invocable<true, MemDPtr, const A>();
    expect_is_invocable<true, MemDPtr, A&>();
    expect_is_invocable<true, MemDPtr, const A&>();
    expect_is_invocable<true, MemDPtr, A&&>();
    expect_is_invocable<true, MemDPtr, const A&&>();
    // Invalid calls
    expect_is_invocable<false, MemDPtr, A, int, long, double>();  // Too many args
    expect_is_invocable<false, MemDPtr, int>();                   // Invalid argument type

    // With subclass
    struct B : A {};

    expect_is_invocable<true, MemDPtr, B>();
    expect_is_invocable<true, MemDPtr, const B>();
    expect_is_invocable<true, MemDPtr, B&>();
    expect_is_invocable<true, MemDPtr, const B&>();
    expect_is_invocable<true, MemDPtr, B&&>();
    expect_is_invocable<true, MemDPtr, const B&&>();
    // Invalid calls
    expect_is_invocable<false, MemDPtr, B, int, long, double>();  // Too many args
    expect_is_invocable<false, MemDPtr, int>();                   // Invalid argument type
}
#endif
