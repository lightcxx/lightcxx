#include "testing.h"

#include <source_location>
#include <type_traits>

TEST() {
    // TODO: Test that std::source_location is Cpp17DefaultConstructible.
    // TODO: Test that std::source_location is Cpp17CopyConstructible.
    // TODO: Test that std::source_location is Cpp17CopyAssignable.
    // TODO: Test that std::source_location is Cpp17Destructible.
    // TODO: Test that lvalues of std::source_location are swappable (requires std::swap)
    expect_ct_and_rt(std::is_nothrow_move_constructible_v<std::source_location>);
    // TODO: is_nothrow_move_assignable_v<source_location> (requires <type_traits>)
    // TODO: is_nothrow_swappable_v<source_location> (requires <type_traits>)
}
