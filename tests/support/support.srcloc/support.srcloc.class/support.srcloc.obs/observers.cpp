#include "testing.h"

#include <source_location>

#include <string.h>

TEST() {
    std::source_location loc;
    expect(loc.line() == 0);
    expect(loc.column() == 0);
    expect(strcmp(loc.function_name(), "") == 0);
    expect(strcmp(loc.file_name(), "") == 0);

    std::source_location current = std::source_location::current();
    expect(current.line() == 14);
    expect(current.column() > 0);
    expect(strcmp(current.function_name(), "test_") == 0);
    expect(strstr(current.file_name(), "observers.cpp") != nullptr);
}
