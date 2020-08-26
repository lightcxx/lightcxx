#ifndef _LIGHTCXX_GUARD_TESTING_TEST_H
#define _LIGHTCXX_GUARD_TESTING_TEST_H

#include "testing/interceptor.h"
#include "testing/meta.h"

#include <source_location>

namespace Testing {

void fail(std::source_location loc = std::source_location::current()) noexcept;

void fail(const char* msg, ...) noexcept;

void expect(bool cnd, std::source_location loc = std::source_location::current()) noexcept;

void expect(bool cnd, const char* msg, ...) noexcept;

void step(const char* msg, ...) noexcept;

#define STATIC_EXPECT(...)                                                                         \
    ::Testing::expect(__VA_ARGS__);                                                                \
    static_assert(__VA_ARGS__)

template<class T, class U>
constexpr void expectType(U&& val) noexcept {
    static_assert(IsSameType<T, decltype(val)>::value, "Invalid type.");
}

template<class T, class U, class V>
void expectTypeAndValue(U&& val,
                        V&& expected,
                        std::source_location loc = std::source_location::current()) noexcept {
    static_assert(IsSameType<T, decltype(val)>::value, "Invalid type.");
    expect(val == expected, loc);
}

template<class T, class U, class V>
void expectTypeAndValue(U&& val, V&& expected, const char* msg) noexcept {
    static_assert(IsSameType<T, decltype(val)>::value, "Invalid type.");
    expect(val == expected, msg);
}

void run();
void runWithArgs(int argc, char** argv);

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
    void name();                                                                                   \
    ::Testing::Test test_##name{name, #name};                                                      \
    }                                                                                              \
    void Testing::name()

#endif
