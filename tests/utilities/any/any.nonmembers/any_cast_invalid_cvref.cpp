// EXPECT:NO_COMPILE 17

#include <any>

#include "testing.h"

struct non_copyable {
    non_copyable() = default;
    non_copyable(non_copyable&&) = default;
    non_copyable(const non_copyable&) = delete;
};

struct non_movable {
    non_movable() = default;
    non_movable(non_movable&&) = delete;
    non_movable(const non_movable&) = delete;
};

TEST() {
    std::any nonconst_any;
    const std::any const_any;
#if NEGATIVE_COMPILE_ITERATION == 0
    any_cast<int&>(const_any);
#elif NEGATIVE_COMPILE_ITERATION == 1
    any_cast<volatile int&>(const_any);
#elif NEGATIVE_COMPILE_ITERATION == 2
    any_cast<int&&>(const_any);
#elif NEGATIVE_COMPILE_ITERATION == 3
    any_cast<const int&&>(const_any);
#elif NEGATIVE_COMPILE_ITERATION == 4
    any_cast<volatile int&&>(const_any);
#elif NEGATIVE_COMPILE_ITERATION == 5
    any_cast<const volatile int&&>(const_any);
#elif NEGATIVE_COMPILE_ITERATION == 6
    any_cast<int&&>(nonconst_any);
#elif NEGATIVE_COMPILE_ITERATION == 7
    any_cast<const int&&>(nonconst_any);
#elif NEGATIVE_COMPILE_ITERATION == 8
    any_cast<volatile int&&>(nonconst_any);
#elif NEGATIVE_COMPILE_ITERATION == 9
    any_cast<const volatile int&&>(nonconst_any);
#elif NEGATIVE_COMPILE_ITERATION == 10
    any_cast<int&>(std::move(nonconst_any));
#elif NEGATIVE_COMPILE_ITERATION == 11
    any_cast<const int&>(std::move(nonconst_any));
#elif NEGATIVE_COMPILE_ITERATION == 12
    any_cast<volatile int&>(std::move(nonconst_any));
#elif NEGATIVE_COMPILE_ITERATION == 13
    any_cast<const volatile int&>(std::move(nonconst_any));
#elif NEGATIVE_COMPILE_ITERATION == 14
    any_cast<non_copyable>(nonconst_any);
#elif NEGATIVE_COMPILE_ITERATION == 15
    any_cast<non_movable>(nonconst_any);
#elif NEGATIVE_COMPILE_ITERATION == 16
    any_cast<non_movable>(std::move(nonconst_any));
#endif
}
