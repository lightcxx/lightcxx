#include <exception>

#include "testing.h"
#include <string.h>

TEST() {
    // Default constructor
    std::exception default_constructed;
    ASSERT_NOEXCEPT(std::exception());
    ASSERT(strcmp(default_constructed.what(), "exception") == 0);

    // Copy constructor
    std::exception copy_constructed(default_constructed);
    ASSERT_NOEXCEPT(std::exception{default_constructed});
    ASSERT(strcmp(copy_constructed.what(), default_constructed.what()) == 0);
    ASSERT(copy_constructed.what() == default_constructed.what());
    ASSERT(strcmp(copy_constructed.what(), "exception") == 0);

    // Copy assignment operator
    std::exception copy_assigned;
    copy_assigned = default_constructed;
    ASSERT_NOEXCEPT(copy_assigned = default_constructed);
    ASSERT(strcmp(copy_assigned.what(), default_constructed.what()) == 0);
    ASSERT(copy_assigned.what() == default_constructed.what());
    ASSERT(strcmp(copy_assigned.what(), "exception") == 0);

    // Thrown
    try {
        throw default_constructed;
    } catch (std::exception& thrown) {
        ASSERT(strcmp(thrown.what(), default_constructed.what()) == 0);
        ASSERT(thrown.what() == default_constructed.what());
        ASSERT(strcmp(thrown.what(), "exception") == 0);
    }

    static_assert(std::is_polymorphic_v<std::exception>);
}
