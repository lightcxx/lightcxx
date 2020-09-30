#include <source_location>

#include "testing.h"

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
    expect(loc.line() == 41);
    expect(loc.column() > 0);
    expect(strcmp(loc.function_name(), "test_") == 0);
    expect(strstr(loc.file_name(), "construction.cpp") != nullptr);
}

TEST() {
    std::source_location loc;
    expect(loc.line() == 0);
    expect(loc.column() == 0);
    expect(strcmp(loc.function_name(), "") == 0);
    expect(strcmp(loc.file_name(), "") == 0);

    std::source_location current = std::source_location::current();
    expect(current.line() == 35);
    expect(current.column() > 0);
    expect(strcmp(current.function_name(), "test_") == 0);
    expect(strstr(current.file_name(), "construction.cpp") != nullptr);

    function_with_default_parameter();

    A a1;
    expect(a1.loc.line() == 10);
    expect(a1.loc.column() > 0);
    expect(strcmp(a1.loc.function_name(), "A") == 0);
    expect(strstr(a1.loc.file_name(), "construction.cpp") != nullptr);

    A a2(3);
    expect(a2.loc.line() == 10);
    expect(a2.loc.column() > 0);
    expect(strcmp(a2.loc.function_name(), "A") == 0);
    expect(strstr(a2.loc.file_name(), "construction.cpp") != nullptr);

    B b1;
    expect(b1.a.loc.line() == 10);
    expect(b1.a.loc.column() > 0);
    expect(strcmp(b1.a.loc.function_name(), "A") == 0);
    expect(strstr(b1.a.loc.file_name(), "construction.cpp") != nullptr);

    B b2(3);
    expect(b2.a.loc.line() == 10);
    expect(b2.a.loc.column() > 0);
    expect(strcmp(b2.a.loc.function_name(), "A") == 0);
    expect(strstr(b2.a.loc.file_name(), "construction.cpp") != nullptr);
}
