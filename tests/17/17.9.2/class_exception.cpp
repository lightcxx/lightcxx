#include <exception>

#include "testing/test.h"
#include <string.h>

void Testing::run() {
    // Default constructor
    std::exception default_constructed;
    STATIC_EXPECT(noexcept(std::exception()), "std::exception default constructor is noexcept");
    expect(strcmp(default_constructed.what(), "exception") == 0,
           "default constructed std::exception what() message");

    // Copy constructor
    std::exception copy_constructed(default_constructed);
    STATIC_EXPECT(noexcept(std::exception(default_constructed)),
                  "std::exception copy constructor is noexcept");
    expect(strcmp(copy_constructed.what(), default_constructed.what()) == 0,
           "what() is the same for copy constructor of std::exception");
    expect(copy_constructed.what() == default_constructed.what(),
           "what() returns same pointer for copy constructor of std::exception");
    expect(strcmp(copy_constructed.what(), "exception") == 0,
           "copy constructed std::exception what() message");

    // Copy assignment operator
    std::exception copy_assigned;
    copy_assigned = default_constructed;
    STATIC_EXPECT(noexcept(copy_assigned = default_constructed),
                  "std::exception copy assignment operator is noexcept");
    expect(strcmp(copy_assigned.what(), default_constructed.what()) == 0,
           "what() is the same for copy assignment of std::exception");
    expect(copy_assigned.what() == default_constructed.what(),
           "what() returns same pointer for copy assignment of std::exception");
    expect(strcmp(copy_assigned.what(), "exception") == 0,
           "copy assigned std::exception what() message");

    // Thrown
    try {
        throw default_constructed;
    } catch (std::exception& thrown) {
        expect(strcmp(thrown.what(), default_constructed.what()) == 0,
               "what() is the same for thrown std::exception");
        expect(thrown.what() == default_constructed.what(),
               "what() returns same pointer for thrown std::exception");
        expect(strcmp(thrown.what(), "exception") == 0,
               "copy assigned std::exception what() message");
    }
}
