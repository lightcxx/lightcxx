// REQUEST:ARGUMENTS "-1;1"

#include <new>

#include "testing.h"

namespace __cxxabiv1 {

extern "C" void __cxa_throw_bad_array_new_length();

}

TEST() {
    int argc = get_argc();
    char** argv = get_argv();

    expect(argc >= 3);

    // We receive these as runtime arguments so clang cannot optimize them away.
    int minus_one = atoi(argv[1]);
    expect(minus_one == -1);

    int one = atoi(argv[2]);
    expect(one == 1);

    std::bad_array_new_length default_constructed;

    try {
        // TODO: Remove this when clang fixes its codegen to actually call this function when it
        //  should.
        __cxxabiv1::__cxa_throw_bad_array_new_length();
        new int[minus_one];     // negative size: bad_array_new_length
        new int[one]{1, 2, 3};  // too many initializers: bad_array_new_length
        fail();
    } catch (const std::bad_array_new_length& e) {
        expect(default_constructed.what() == e.what());
    } catch (std::bad_alloc& e) { fail(); } catch (...) {
        fail();
    }
}
