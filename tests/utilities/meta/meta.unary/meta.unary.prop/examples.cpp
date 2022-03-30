#include <type_traits>

// Examples provided in the standard draft

// #unary.prop-5
static_assert(std::is_const_v<const volatile int>);
static_assert(!std::is_const_v<const int*>);
static_assert(!std::is_const_v<const int&>);
static_assert(!std::is_const_v<int[3]>);
static_assert(std::is_const_v<const int[3]>);

// #unary.prop-7
// Given:
struct P final {};
union U1 {};
union U2 final {};

// the following assertions hold:
static_assert(!std::is_final_v<int>);
static_assert(std::is_final_v<P>);
static_assert(!std::is_final_v<U1>);
static_assert(std::is_final_v<U2>);
