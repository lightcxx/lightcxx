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

template<class T, class U>
constexpr void expect_type(U&& val) noexcept {
    static_assert(std::is_same_v<T, decltype(val)>, "Invalid type.");
}

template<class T, class U, class V>
void expect_type_and_value(U&& val,
                           V&& expected,
                           std::source_location loc = std::source_location::current()) noexcept {
    static_assert(std::is_same_v<T, decltype(val)>, "Invalid type.");
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
    void name##_();                                                                                \
    ::Testing::Test test_##name{name##_, #name};                                                   \
    }                                                                                              \
    void Testing::name##_()

#endif
