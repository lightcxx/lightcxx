#include <source_location>

#include "testing.h"

#include <string.h>

struct A {
    std::source_location loc = std::source_location::current();

    A() = default;
    A(int)
            : A() {}
};

struct B {
    A a;

    B() = default;
    explicit B(int)
            : a(3) {}
};

void function_with_default_parameter(std::source_location loc = std::source_location::current()) {
    ASSERT(loc.line() == 43);
    ASSERT(loc.column() > 0);
    ASSERT(strcmp(loc.function_name(), "test") == 0);
    ASSERT(strstr(loc.file_name(), "construction.cpp") != nullptr);
}

TEST() {
    std::source_location loc;
    ASSERT(loc.line() == 0);
    ASSERT(loc.column() == 0);
    ASSERT(strcmp(loc.function_name(), "") == 0);
    ASSERT(strcmp(loc.file_name(), "") == 0);

    std::source_location current = std::source_location::current();
    ASSERT(current.line() == 37);
    ASSERT(current.column() > 0);
    ASSERT(strcmp(current.function_name(), "test") == 0);
    ASSERT(strstr(current.file_name(), "construction.cpp") != nullptr);

    function_with_default_parameter();

    A a1;
    ASSERT(a1.loc.line() == 10);
    ASSERT(a1.loc.column() > 0);
    ASSERT(strcmp(a1.loc.function_name(), "A") == 0);
    ASSERT(strstr(a1.loc.file_name(), "construction.cpp") != nullptr);

    A a2(3);
    ASSERT(a2.loc.line() == 10);
    ASSERT(a2.loc.column() > 0);
    ASSERT(strcmp(a2.loc.function_name(), "A") == 0);
    ASSERT(strstr(a2.loc.file_name(), "construction.cpp") != nullptr);

    B b1;
    ASSERT(b1.a.loc.line() == 10);
    ASSERT(b1.a.loc.column() > 0);
    ASSERT(strcmp(b1.a.loc.function_name(), "A") == 0);
    ASSERT(strstr(b1.a.loc.file_name(), "construction.cpp") != nullptr);

    B b2(3);
    ASSERT(b2.a.loc.line() == 10);
    ASSERT(b2.a.loc.column() > 0);
    ASSERT(strcmp(b2.a.loc.function_name(), "A") == 0);
    ASSERT(strstr(b2.a.loc.file_name(), "construction.cpp") != nullptr);
}
