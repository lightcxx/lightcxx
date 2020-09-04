// REQUEST:NO_TEST_LIB "The testing library depends on <source_location>."

#include <source_location>

#include <stdio.h>
#include <stdlib.h>

void expect(bool b, const char* msg) {
    if (!b) {
        fprintf(stderr, "EXPECTATION FAILED: %s\n", msg);
        abort();
    }
}

void test_copy_construct() {
    std::source_location loc = std::source_location::current();
    std::source_location loc2(loc);
    expect(loc.line() == loc2.line(), "copy_construct line");
    expect(loc.column() == loc2.column(), "copy_construct column");
    expect(loc.file_name() == loc2.file_name(), "copy_construct file_name");
    expect(loc.function_name() == loc2.function_name(), "copy_construct function_name");
}

void test_move_construct() {
    std::source_location loc = std::source_location::current();
    std::source_location loc2(static_cast<std::source_location&&>(loc));

    // Since the implementation of std::source_location makes the move operations trivial, we can
    // still use "loc" even if it is now moved-from.
    expect(loc.line() == loc2.line(), "move_construct line");
    expect(loc.column() == loc2.column(), "move_construct column");
    expect(loc.file_name() == loc2.file_name(), "move_construct file_name");
    expect(loc.function_name() == loc2.function_name(), "move_construct function_name");
}

void test_copy_assign() {
    std::source_location loc = std::source_location::current();
    std::source_location loc2;
    loc2 = loc;
    expect(loc.line() == loc2.line(), "copy_assign line");
    expect(loc.column() == loc2.column(), "copy_assign column");
    expect(loc.file_name() == loc2.file_name(), "copy_assign file_name");
    expect(loc.function_name() == loc2.function_name(), "copy_assign function_name");
}

void test_move_assign() {
    std::source_location loc = std::source_location::current();
    std::source_location loc2;
    loc2 = static_cast<std::source_location&&>(loc);

    // Since the implementation of std::source_location makes the move operations trivial, we can
    // still use "loc" even if it is now moved-from.
    expect(loc.line() == loc2.line(), "move_assign line");
    expect(loc.column() == loc2.column(), "move_assign column");
    expect(loc.file_name() == loc2.file_name(), "move_assign file_name");
    expect(loc.function_name() == loc2.function_name(), "move_assign function_name");
}

int main() {
    test_copy_construct();
    test_move_construct();
    test_copy_assign();
    test_move_assign();
    return 0;
}
