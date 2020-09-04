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

int main() {
    std::source_location loc;
    expect(loc.line() == 0, "default constructor");
    expect(loc.column() == 0, "default constructor");
    expect(strcmp(loc.function_name(), "") == 0, "default constructor, function_name()");
    expect(strcmp(loc.file_name(), "") == 0, "default constructor, file_name()");

    std::source_location current = std::source_location::current();
    expect(current.line() == 23, "inline current, line()");
    expect(current.column() > 0, "inline current, column()");
    expect(strcmp(current.function_name(), "main") == 0, "inline current, function_name()");
    expect(strstr(current.file_name(), "observers.cpp") != nullptr, "inline current, file_name()");
}
