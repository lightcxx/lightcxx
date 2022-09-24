#ifndef TESTING_TESTING_H
#define TESTING_TESTING_H

#include "new"

extern "C" __attribute__((format(printf, 1, 2))) void testing_step_impl(const char* msg, ...);

extern "C" void testing_fail_impl(const char* func, const char* file, int line);

extern "C" void testing_expect_impl(int cnd, const char* func, const char* file, int line);

extern "C" void testing_register_test(void (*test)(), const char* name);

extern "C" void testing_register_global(void* obj, void (*ctor)(void*), void (*dtor)(void*));

namespace Testing {

template<class, class>
inline constexpr bool same_type = false;

template<class T>
inline constexpr bool same_type<T, T> = true;

template<class T>
struct ForkSafeGlobal {
    bool is_initialized = false;
    union {
        T value;
    };

    ForkSafeGlobal() {
        const auto ctor = [](void* self) {
            testing_expect_impl(!static_cast<ForkSafeGlobal*>(self)->is_initialized, __func__, __FILE__, __LINE__);
            new (&static_cast<ForkSafeGlobal*>(self)->value) T();
            static_cast<ForkSafeGlobal*>(self)->is_initialized = true;
        };
        const auto dtor = [](void* self) {
            testing_expect_impl(static_cast<ForkSafeGlobal*>(self)->is_initialized, __func__, __FILE__, __LINE__);
            static_cast<ForkSafeGlobal*>(self)->value.~T();
            static_cast<ForkSafeGlobal*>(self)->is_initialized = false;
        };
        testing_register_global(this, ctor, dtor);
    }

    ~ForkSafeGlobal() {
        testing_expect_impl(!is_initialized, __func__, __FILE__, __LINE__);
    }
};

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

#define step(...) testing_step_impl(__VA_ARGS__)

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

extern "C" const char* testing_get_expected_steps() {
    return TESTING_EXPECTED_STEPS;
}

extern "C" const char* testing_get_expected_exit() {
    return TESTING_EXPECTED_EXIT;
}

#endif
