#include <source_location>

#include "testing/test.h"
#include <string.h>

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
    Testing::expect(loc.line() == 43, "function default argument, line()");
    Testing::expect(loc.column() > 0, "function default argument, column()");
    Testing::expect(strcmp(loc.function_name(), "run") == 0,
                    "function default argument, function_name()");
    Testing::expect(strstr(loc.file_name(), "construction.cpp") != nullptr,
                    "function default argument, file_name()");
}

void Testing::run() {
    std::source_location loc;
    Testing::expect(loc.line() == 0, "default constructor");
    Testing::expect(loc.column() == 0, "default constructor");
    Testing::expect(strcmp(loc.function_name(), "") == 0, "default constructor, function_name()");
    Testing::expect(strcmp(loc.file_name(), "") == 0, "default constructor, file_name()");

    std::source_location current = std::source_location::current();
    Testing::expect(current.line() == 36, "inline current, line()");
    Testing::expect(current.column() > 0, "inline current, column()");
    Testing::expect(strcmp(current.function_name(), "run") == 0, "inline current, function_name()");
    Testing::expect(strstr(current.file_name(), "construction.cpp") != nullptr,
                    "inline current, file_name()");

    function_with_default_parameter();

    A a1;
    Testing::expect(a1.loc.line() == 9, "default member initializer, line()");
    Testing::expect(a1.loc.column() > 0, "default member initializer, column()");
    Testing::expect(strcmp(a1.loc.function_name(), "A") == 0,
                    "default member initializer, function_name()");
    Testing::expect(strstr(a1.loc.file_name(), "construction.cpp") != nullptr,
                    "default member initializer, file_name()");

    A a2(3);
    Testing::expect(a2.loc.line() == 9, "indirect default member initializer, line()");
    Testing::expect(a2.loc.column() > 0, "indirect default member initializer, column()");
    Testing::expect(strcmp(a2.loc.function_name(), "A") == 0,
                    "indirect default member initializer, function_name()");
    Testing::expect(strstr(a2.loc.file_name(), "construction.cpp") != nullptr,
                    "indirect default member initializer, file_name()");

    B b1;
    Testing::expect(b1.a.loc.line() == 9, "indirect x2 default member initializer, line()");
    Testing::expect(b1.a.loc.column() > 0, "indirect x2 default member initializer, column()");
    Testing::expect(strcmp(b1.a.loc.function_name(), "A") == 0,
                    "indirect x2 default member initializer, function_name()");
    Testing::expect(strstr(b1.a.loc.file_name(), "construction.cpp") != nullptr,
                    "indirect x2 default member initializer, file_name()");

    B b2(3);
    Testing::expect(b2.a.loc.line() == 9, "indirect x4 default member initializer, line()");
    Testing::expect(b2.a.loc.column() > 0, "indirect x4 default member initializer, column()");
    Testing::expect(strcmp(b2.a.loc.function_name(), "A") == 0,
                    "indirect x4 default member initializer, function_name()");
    Testing::expect(strstr(b2.a.loc.file_name(), "construction.cpp") != nullptr,
                    "indirect x4 default member initializer, file_name()");
}
