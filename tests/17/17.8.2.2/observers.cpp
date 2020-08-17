#include <source_location>

#include <string.h>
#include "testing/test.h"

void Testing::run() {
    std::source_location loc;
    Testing::expect(loc.line() == 0, "default constructor");
    Testing::expect(loc.column() == 0, "default constructor");
    Testing::expect(strcmp(loc.function_name(), "") == 0, "default constructor, function_name()");
    Testing::expect(strcmp(loc.file_name(), "") == 0, "default constructor, file_name()");

    std::source_location current = std::source_location::current();
    Testing::expect(current.line() == 13, "inline current, line()");
    Testing::expect(current.column() > 0, "inline current, column()");
    Testing::expect(strcmp(current.function_name(), "run") == 0, "inline current, function_name()");
    Testing::expect(strstr(current.file_name(), "observers.cpp") != nullptr,
                    "inline current, file_name()");
}
