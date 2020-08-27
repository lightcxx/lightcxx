// REQUEST:ARGUMENTS "-1;1"

#include <new>

#include "testing/test.h"

namespace __cxxabiv1 {

extern "C" void __cxa_throw_bad_array_new_length();

}

TEST() {
    int argc = get_argc();
    char** argv = get_argv();

    expect(argc >= 3, "Not enough arguments provided.");

    // We receive these as runtime arguments so clang cannot optimize them away.
    int minus_one = atoi(argv[1]);
    expect(minus_one == -1, "First argument is not -1.");

    int one = atoi(argv[2]);
    expect(one == 1, "Second argument is not 1.");

    std::bad_array_new_length default_constructed;

    try {
        // TODO: Remove this when clang fixes its codegen to actually call this function when it
        //  should.
        __cxxabiv1::__cxa_throw_bad_array_new_length();
        new int[minus_one];        // negative size: bad_array_new_length
        new int[one]{1, 2, 3};  // too many initializers: bad_array_new_length
        fail("Bad array new length did not throw std::bad_array_new_length");
    } catch (const std::bad_array_new_length& e) {
        expect(default_constructed.what() == e.what(),
               "should be same NTBS pointer for thrown instance");
    } catch (std::bad_alloc& e) { fail("Caught std::bad_alloc"); } catch (...) {
        fail("Could not catch thrown std::bad_array_new_length by catching const "
             "std::bad_array_new_length&");
    }
}
