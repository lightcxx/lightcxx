#include <new>

#include <string.h>

#include "testing/test.h"

void Testing::run() {
    std::bad_alloc default_constructed;
    expect(::strcmp(default_constructed.what(), "bad_alloc") == 0,
           "NTBS is implemented to be 'bad_alloc'");

    std::bad_alloc copy_constructed{default_constructed};
    expect(default_constructed.what() == copy_constructed.what(),
           "should be same NTBS pointer for copy-constructed instance");

    std::bad_alloc copy_assigned;
    copy_assigned = default_constructed;
    expect(default_constructed.what() == copy_assigned.what(),
           "should be same NTBS pointer for copy-assigned instance");

    std::bad_alloc move_constructed{static_cast<std::bad_alloc&&>(copy_constructed)};
    expect(default_constructed.what() == move_constructed.what(),
           "should be same NTBS pointer for move-constructed instance");

    std::bad_alloc move_assigned;
    move_assigned = static_cast<std::bad_alloc&&>(copy_assigned);
    expect(default_constructed.what() == move_assigned.what(),
           "should be same NTBS pointer for move-assigned instance");

    try {
        throw default_constructed;
    } catch (std::bad_alloc& thrown) {
        expect(default_constructed.what() == thrown.what(),
               "should be same NTBS pointer for thrown instance");
    } catch(...) {
        fail("Could not catch thrown std::bad_alloc by catching std::bad_alloc&");
    }
}
