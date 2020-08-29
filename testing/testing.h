#ifndef TESTING_TESTING_H
#define TESTING_TESTING_H

#include "meta.h"
#include <stdlib.h>

#include <source_location>

namespace Testing {

void step(const char* msg, ...) noexcept;

[[noreturn]] void fail(std::source_location loc = std::source_location::current()) noexcept;

void expect(bool cnd, std::source_location loc = std::source_location::current()) noexcept;

#define expect_ct_and_rt(...)                                                                      \
    ::Testing::expect(__VA_ARGS__);                                                                \
    static_assert(__VA_ARGS__)

#define expect_is_noexcept(...) static_assert(noexcept(__VA_ARGS__))

#define expect_same_type(...) static_assert(::std::is_same_v<__VA_ARGS__>)

#define expect_type(expected_type, expr)                                                           \
    static_assert(::std::is_same_v<expected_type, decltype((expr))>)

template<class T, class U, class V>
void expect_type_and_value(U&& val,
                           V&& expected,
                           std::source_location loc = std::source_location::current()) noexcept {
    expect_ct_and_rt(std::is_same_v<T, decltype(val)>);
    expect(val == expected, loc);
}

int get_argc();
char** get_argv();

struct Test {
    static Test* head;
    static Test* tail;

    void (*test)();
    const char* name;
    Test* next;

    explicit Test(void (*test)(), const char* name) noexcept;
};

}  // namespace Testing

#define TEST(name)                                                                                 \
    namespace Testing {                                                                            \
    static void name##_();                                                                         \
    static ::Testing::Test test_##name{name##_, #name};                                            \
    }                                                                                              \
    static void Testing::name##_()

#endif
