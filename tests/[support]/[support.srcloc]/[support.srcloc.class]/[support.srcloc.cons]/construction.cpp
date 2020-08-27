// REQUEST:NO_TEST_LIB "The testing library depends on <source_location>."

#include <source_location>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void expect(bool b, const char* msg) {
    if (!b) {
        fprintf(stderr, "EXPECTATION FAILED: %s\n", msg);
        abort();
    }
}

struct A {
    std::source_location loc = std::source_location::current();

    A() = default;
    A(int): A() {}
};

struct B {
    A a;

    B() = default;
    explicit B(int): a(3) {}
};

void function_with_default_parameter(std::source_location loc = std::source_location::current()) {
    expect(loc.line() == 52, "function default argument, line()");
    expect(loc.column() > 0, "function default argument, column()");
    expect(strcmp(loc.function_name(), "main") == 0, "function default argument, function_name()");
    expect(strstr(loc.file_name(), "construction.cpp") != nullptr,
           "function default argument, file_name()");
}

int main() {
    std::source_location loc;
    expect(loc.line() == 0, "default constructor");
    expect(loc.column() == 0, "default constructor");
    expect(strcmp(loc.function_name(), "") == 0, "default constructor, function_name()");
    expect(strcmp(loc.file_name(), "") == 0, "default constructor, file_name()");

    std::source_location current = std::source_location::current();
    expect(current.line() == 45, "inline current, line()");
    expect(current.column() > 0, "inline current, column()");
    expect(strcmp(current.function_name(), "main") == 0, "inline current, function_name()");
    expect(strstr(current.file_name(), "construction.cpp") != nullptr,
           "inline current, file_name()");

    function_with_default_parameter();

    A a1;
    expect(a1.loc.line() == 19, "default member initializer, line()");
    expect(a1.loc.column() > 0, "default member initializer, column()");
    expect(strcmp(a1.loc.function_name(), "A") == 0, "default member initializer, function_name()");
    expect(strstr(a1.loc.file_name(), "construction.cpp") != nullptr,
           "default member initializer, file_name()");

    A a2(3);
    expect(a2.loc.line() == 19, "indirect default member initializer, line()");
    expect(a2.loc.column() > 0, "indirect default member initializer, column()");
    expect(strcmp(a2.loc.function_name(), "A") == 0,
           "indirect default member initializer, function_name()");
    expect(strstr(a2.loc.file_name(), "construction.cpp") != nullptr,
           "indirect default member initializer, file_name()");

    B b1;
    expect(b1.a.loc.line() == 19, "indirect x2 default member initializer, line()");
    expect(b1.a.loc.column() > 0, "indirect x2 default member initializer, column()");
    expect(strcmp(b1.a.loc.function_name(), "A") == 0,
           "indirect x2 default member initializer, function_name()");
    expect(strstr(b1.a.loc.file_name(), "construction.cpp") != nullptr,
           "indirect x2 default member initializer, file_name()");

    B b2(3);
    expect(b2.a.loc.line() == 19, "indirect x4 default member initializer, line()");
    expect(b2.a.loc.column() > 0, "indirect x4 default member initializer, column()");
    expect(strcmp(b2.a.loc.function_name(), "A") == 0,
           "indirect x4 default member initializer, function_name()");
    expect(strstr(b2.a.loc.file_name(), "construction.cpp") != nullptr,
           "indirect x4 default member initializer, file_name()");
}
