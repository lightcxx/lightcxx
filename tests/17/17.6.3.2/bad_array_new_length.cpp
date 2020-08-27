#include <new>

#include <string.h>

#include "testing/test.h"

TEST() {
    std::bad_array_new_length default_constructed;
    expect(::strcmp(default_constructed.what(), "bad_array_new_length") == 0,
           "NTBS is implemented to be 'bad_array_new_length'");

    std::bad_array_new_length copy_constructed{default_constructed};
    expect(default_constructed.what() == copy_constructed.what(),
           "should be same NTBS pointer for copy-constructed instance");

    std::bad_array_new_length copy_assigned;
    copy_assigned = default_constructed;
    expect(default_constructed.what() == copy_assigned.what(),
           "should be same NTBS pointer for copy-assigned instance");

    std::bad_array_new_length move_constructed{
      static_cast<std::bad_array_new_length&&>(copy_constructed)};
    expect(default_constructed.what() == move_constructed.what(),
           "should be same NTBS pointer for move-constructed instance");

    std::bad_array_new_length move_assigned;
    move_assigned = static_cast<std::bad_array_new_length&&>(copy_assigned);
    expect(default_constructed.what() == move_assigned.what(),
           "should be same NTBS pointer for move-assigned instance");

    try {
        throw default_constructed;
    } catch (std::bad_array_new_length& thrown) {
        expect(default_constructed.what() == thrown.what(),
               "should be same NTBS pointer for thrown instance");
    } catch (...) {
        fail("Could not catch thrown std::bad_array_new_length by catching "
             "std::bad_array_new_length&");
    }

    // TODO: Test that bad_array_new_length is polymorphic and extends std::exception (requires
    //  <type_traits>).
}
