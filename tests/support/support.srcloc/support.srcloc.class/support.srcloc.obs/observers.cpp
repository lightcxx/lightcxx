#include "testing.h"

#include <source_location>

#include <string.h>

TEST() {
    std::source_location loc;
    ASSERT(loc.line() == 0);
    ASSERT(loc.column() == 0);
    ASSERT(strcmp(loc.function_name(), "") == 0);
    ASSERT(strcmp(loc.file_name(), "") == 0);

    std::source_location current = std::source_location::current();
    ASSERT(current.line() == 14);
    ASSERT(current.column() > 0);
    ASSERT(strcmp(current.function_name(), "test") == 0);
    ASSERT(strstr(current.file_name(), "observers.cpp") != nullptr);
}
