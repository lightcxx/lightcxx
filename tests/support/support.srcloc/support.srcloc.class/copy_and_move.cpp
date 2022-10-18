#include "testing.h"

#include <source_location>

TEST(copy_construct) {
    std::source_location loc = std::source_location::current();
    std::source_location loc2(loc);
    ASSERT(loc.line() == loc2.line());
    ASSERT(loc.column() == loc2.column());
    ASSERT(loc.file_name() == loc2.file_name());
    ASSERT(loc.function_name() == loc2.function_name());
}

TEST(move_construct) {
    std::source_location loc = std::source_location::current();
    std::source_location loc2(static_cast<std::source_location&&>(loc));

    // Since the implementation of std::source_location makes the move operations trivial, we can
    // still use "loc" even if it is now moved-from.
    ASSERT(loc.line() == loc2.line());
    ASSERT(loc.column() == loc2.column());
    ASSERT(loc.file_name() == loc2.file_name());
    ASSERT(loc.function_name() == loc2.function_name());
}

TEST(copy_assign) {
    std::source_location loc = std::source_location::current();
    std::source_location loc2;
    loc2 = loc;
    ASSERT(loc.line() == loc2.line());
    ASSERT(loc.column() == loc2.column());
    ASSERT(loc.file_name() == loc2.file_name());
    ASSERT(loc.function_name() == loc2.function_name());
}

TEST(move_assign) {
    std::source_location loc = std::source_location::current();
    std::source_location loc2;
    loc2 = static_cast<std::source_location&&>(loc);

    // Since the implementation of std::source_location makes the move operations trivial, we can
    // still use "loc" even if it is now moved-from.
    ASSERT(loc.line() == loc2.line());
    ASSERT(loc.column() == loc2.column());
    ASSERT(loc.file_name() == loc2.file_name());
    ASSERT(loc.function_name() == loc2.function_name());
}
