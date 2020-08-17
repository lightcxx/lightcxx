#include <source_location>

#include "testing/test.h"

void test_copy_construct() {
    std::source_location loc = std::source_location::current();
    std::source_location loc2(loc);
    Testing::expect(loc.line() == loc2.line(), "copy_construct line");
    Testing::expect(loc.column() == loc2.column(), "copy_construct column");
    Testing::expect(loc.file_name() == loc2.file_name(), "copy_construct file_name");
    Testing::expect(loc.function_name() == loc2.function_name(), "copy_construct function_name");
}

void test_move_construct() {
    std::source_location loc = std::source_location::current();
    std::source_location loc2(static_cast<std::source_location&&>(loc));

    // Since the implementation of std::source_location makes the move operations trivial, we can
    // still use "loc" even if it is now moved-from.
    Testing::expect(loc.line() == loc2.line(), "move_construct line");
    Testing::expect(loc.column() == loc2.column(), "move_construct column");
    Testing::expect(loc.file_name() == loc2.file_name(), "move_construct file_name");
    Testing::expect(loc.function_name() == loc2.function_name(), "move_construct function_name");
}

void test_copy_assign() {
    std::source_location loc = std::source_location::current();
    std::source_location loc2;
    loc2 = loc;
    Testing::expect(loc.line() == loc2.line(), "copy_assign line");
    Testing::expect(loc.column() == loc2.column(), "copy_assign column");
    Testing::expect(loc.file_name() == loc2.file_name(), "copy_assign file_name");
    Testing::expect(loc.function_name() == loc2.function_name(), "copy_assign function_name");
}

void test_move_assign() {
    std::source_location loc = std::source_location::current();
    std::source_location loc2;
    loc2 = static_cast<std::source_location&&>(loc);

    // Since the implementation of std::source_location makes the move operations trivial, we can
    // still use "loc" even if it is now moved-from.
    Testing::expect(loc.line() == loc2.line(), "move_assign line");
    Testing::expect(loc.column() == loc2.column(), "move_assign column");
    Testing::expect(loc.file_name() == loc2.file_name(), "move_assign file_name");
    Testing::expect(loc.function_name() == loc2.function_name(), "move_assign function_name");
}

void Testing::run() {
    test_copy_construct();
    test_move_construct();
    test_copy_assign();
    test_move_assign();
}
