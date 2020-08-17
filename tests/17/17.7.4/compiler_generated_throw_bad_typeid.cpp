#include <typeinfo>

#include "testing/test.h"

struct S {
    virtual ~S() = default;
};

void Testing::run() {
    std::bad_typeid default_constructed;
    S* p = nullptr;
    try {
        [[maybe_unused]] const char* name = typeid(*p).name();
        fail("Bad typeid expression did not throw std::bad_typeid");
    } catch (const std::bad_typeid& e) {
        expect(default_constructed.what() == e.what(),
               "should be same NTBS pointer for thrown instance");
    } catch (...) {
        fail("Could not catch thrown std::bad_typeid by catching const std::bad_typeid&");
    }
}
