#ifndef TESTING_TESTING_H
#define TESTING_TESTING_H

extern "C" void step(const char* msg);

extern "C" void testing_fail_impl(const char* func, const char* file, const char* line);

extern "C" void testing_register_test(void (*test)(), void* buffer[2]);

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

#define TO_STR1(L) #L
#define TO_STR(L) TO_STR1(L)

#define FAIL()                                                   \
    do {                                                         \
        testing_fail_impl(__func__, __FILE__, TO_STR(__LINE__)); \
    } while (false)

#define ASSERT(condition)   \
    do {                    \
        if (!(condition)) { \
            FAIL();         \
        }                   \
    } while (false)

#define ASSERT_CT_RT(condition)   \
    do {                          \
        static_assert(condition); \
        ASSERT(condition);        \
    } while (false)

#define ASSERT_NOEXCEPT(expr) static_assert(noexcept(expr))
#define ASSERT_NOT_NOEXCEPT(expr) static_assert(!noexcept(expr))

#define ASSERT_TYPE(expected_type, expr) static_assert(::Testing::same_type<expected_type, decltype((expr))>)

#define ASSERT_TYPE_AND_VALUE(expr, type, value)                  \
    ASSERT_CT_RT((::Testing::same_type<type, decltype((expr))>)); \
    ASSERT((expr) == (value))

#define TEST(name)                                                       \
    namespace Testing {                                                  \
    static void test##name();                                            \
    static void* test_buffer##name[2];                                   \
    __attribute__((__constructor__)) static void test_register##name() { \
        testing_register_test(test##name, test_buffer##name);            \
    }                                                                    \
    }                                                                    \
    static void Testing::test##name()

#endif
