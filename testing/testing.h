#ifndef TESTING_TESTING_H
#define TESTING_TESTING_H

#include "new"

extern "C" void step(const char* msg);

extern "C" void testing_fail_impl(const char* func, const char* file, int line);

extern "C" void testing_expect_impl(int cnd, const char* func, const char* file, int line);

extern "C" void testing_register_test(void (*test)(), const char* name);

namespace Testing {

template<class, class>
inline constexpr bool same_type = false;

template<class T>
inline constexpr bool same_type<T, T> = true;

void compiler_forget(auto& value) {
    asm volatile(""
                 : "+m,r"(value)
                 :
                 : "memory");
}

}  // namespace Testing

namespace tests_namespace {

using namespace ::Testing;

}  // namespace tests_namespace

#define fail() testing_fail_impl(__func__, __FILE__, __LINE__)

#define expect(cnd) testing_expect_impl(cnd, __func__, __FILE__, __LINE__)

#define expect_ct_and_rt(...)                                       \
    testing_expect_impl(__VA_ARGS__, __func__, __FILE__, __LINE__); \
    static_assert(__VA_ARGS__)

#define expect_is_noexcept(...) static_assert(noexcept(__VA_ARGS__))
#define expect_is_not_noexcept(...) static_assert(!noexcept(__VA_ARGS__))

#define expect_same_type(...) static_assert(::Testing::same_type<__VA_ARGS__>)

#define expect_type(expected_type, expr) static_assert(::Testing::same_type<expected_type, decltype((expr))>)

#define expect_type_and_value(expr, type, value)                    \
    expect_ct_and_rt(::Testing::same_type<type, decltype((expr))>); \
    expect((expr) == value)

#define TEST(name)                                                        \
    namespace tests_namespace {                                           \
    static void test_##name();                                            \
    __attribute__((__constructor__)) static void test_register_##name() { \
        testing_register_test(test_##name, #name);                        \
    }                                                                     \
    }                                                                     \
    static void tests_namespace::test_##name()

#endif
