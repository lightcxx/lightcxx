#include <exception>

#include "testing.h"

TEST() {
    // Note 2
    // TODO: Check Cpp17NullablePointer named requirement.

    // Note 4
    std::exception_ptr exc_1;
    expect(exc_1 == nullptr);

    // Note 3
    try {
        throw 3;
    } catch (...) {
        exc_1 = std::current_exception();
    }

    std::exception_ptr exc_2;
    try {
        throw 3;
    } catch (...) {
        exc_2 = std::current_exception();
    }
    expect(exc_1 != exc_2);
    exc_2 = exc_1;
    expect(exc_1 == exc_2);
}
