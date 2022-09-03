#include <new>

#include "testing.h"

extern "C" void __cxa_throw_bad_array_new_length();

void compiler_forget(auto& value) {
    asm volatile(""
                 : "+m,r"(value)
                 :
                 : "memory");
}

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-conversion"
        new int[minus_one];     // negative size: bad_array_new_length
        new int[one]{1, 2, 3};  // too many initializers: bad_array_new_length
#pragma clang diagnostic pop
#pragma GCC diagnostic pop
        fail();
    } catch (const std::bad_array_new_length& e) {
        expect(default_constructed.what() == e.what());
    } catch (std::bad_alloc& e) {
        fail();
    } catch (...) {
        fail();
    }
}
