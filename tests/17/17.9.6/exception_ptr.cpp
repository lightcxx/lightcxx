#include <exception>

#include "testing/test.h"

TEST() {
    // Note 2
    // TODO: Check Cpp17NullablePointer named requirement.


    // Note 4
    std::exception_ptr exc_1;
    expect(exc_1 == nullptr, "default constructed is equal to nullptr");

    // Note 3
    try {
        throw 3;
    } catch (...) { exc_1 = std::current_exception(); }

    std::exception_ptr exc_2;
    try {
        throw 3;
    } catch (...) { exc_2 = std::current_exception(); }
    expect(
      exc_1 != exc_2,
      "2 instances referring to different exceptions that would compare equal don't compare equal");
    exc_2 = exc_1;
    expect(exc_1 == exc_2, "2 instances referring to the same exception compare equal");
}
