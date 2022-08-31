#include <exception>

#include "testing.h"
#include <string.h>

TEST() {
    // Default constructor
    std::exception default_constructed;
    expect_is_noexcept(std::exception());
    expect(strcmp(default_constructed.what(), "exception") == 0);

    // Copy constructor
    std::exception copy_constructed(default_constructed);
    expect_is_noexcept(std::exception{default_constructed});
    expect(strcmp(copy_constructed.what(), default_constructed.what()) == 0);
    expect(copy_constructed.what() == default_constructed.what());
    expect(strcmp(copy_constructed.what(), "exception") == 0);

    // Copy assignment operator
    std::exception copy_assigned;
    copy_assigned = default_constructed;
    expect_is_noexcept(copy_assigned = default_constructed);
    expect(strcmp(copy_assigned.what(), default_constructed.what()) == 0);
    expect(copy_assigned.what() == default_constructed.what());
    expect(strcmp(copy_assigned.what(), "exception") == 0);

    // Thrown
    try {
        throw default_constructed;
    } catch (std::exception& thrown) {
        expect(strcmp(thrown.what(), default_constructed.what()) == 0);
        expect(thrown.what() == default_constructed.what());
        expect(strcmp(thrown.what(), "exception") == 0);
    }

    static_assert(std::is_polymorphic_v<std::exception>);
}
