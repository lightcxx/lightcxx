#include <typeinfo>

#include <string.h>

#include "testing/test.h"

void Testing::run() {
    std::bad_exception default_constructed;
    expect(::strcmp(default_constructed.what(), "bad_exception") == 0,
           "NTBS is implemented to be 'bad_exception'");

    std::bad_exception copy_constructed{default_constructed};
    expect(default_constructed.what() == copy_constructed.what(),
           "should be same NTBS pointer for copy-constructed instance");

    std::bad_exception copy_assigned;
    copy_assigned = default_constructed;
    expect(default_constructed.what() == copy_assigned.what(),
           "should be same NTBS pointer for copy-assigned instance");

    std::bad_exception move_constructed{static_cast<std::bad_exception&&>(copy_constructed)};
    expect(default_constructed.what() == move_constructed.what(),
           "should be same NTBS pointer for move-constructed instance");

    std::bad_exception move_assigned;
    move_assigned = static_cast<std::bad_exception&&>(copy_assigned);
    expect(default_constructed.what() == move_assigned.what(),
           "should be same NTBS pointer for move-assigned instance");

    try {
        throw default_constructed;
    } catch (std::bad_exception& thrown) {
        expect(default_constructed.what() == thrown.what(),
               "should be same NTBS pointer for thrown instance");
    } catch (...) {
        fail("Could not catch thrown std::bad_exception by catching std::bad_exception&");
    }

    // TODO: Test that bad_exception is polymorphic and extends std::exception (requires
    //  <type_traits>).
}
