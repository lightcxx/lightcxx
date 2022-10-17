#include <new>

#include "testing.h"
#include "warnings.h"

extern "C" void __cxa_throw_bad_array_new_length();

TEST() {
    int minus_one = -1;
    int one = 1;
    // Force clang to forget these variables, so it cannot optimize them away.
    compiler_forget(minus_one);
    compiler_forget(one);

    std::bad_array_new_length default_constructed;

    try {
        // TODO: Remove this when clang fixes its codegen to actually call this function when it
        //  should.
        __cxa_throw_bad_array_new_length();
        GCC_DIAGNOSTIC_PUSH("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
        CLANG_DIAGNOSTIC_PUSH("clang diagnostic ignored \"-Wsign-conversion\"")
        new int[minus_one];     // negative size: bad_array_new_length
        new int[one]{1, 2, 3};  // too many initializers: bad_array_new_length
        CLANG_DIAGNOSTIC_POP()
        GCC_DIAGNOSTIC_POP()
        fail();
    } catch (const std::bad_array_new_length& e) {
        expect(default_constructed.what() == e.what());
    } catch (std::bad_alloc& e) {
        fail();
    } catch (...) {
        fail();
    }
}
