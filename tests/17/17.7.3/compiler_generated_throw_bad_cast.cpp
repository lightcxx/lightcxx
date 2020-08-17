#include <typeinfo>

#include "testing/test.h"

struct Foo {
    virtual ~Foo() {}
};
struct Bar {
    virtual ~Bar() {}
};

void Testing::run() {
    std::bad_cast default_constructed;

    Bar b;
    try {
        Foo& f = dynamic_cast<Foo&>(b);
        fail("Bad reference-based dynamic_cast did not throw std::bad_cast");
    } catch (const std::bad_cast& e) {
        expect(default_constructed.what() == e.what(),
               "should be same NTBS pointer for thrown instance");
    } catch (...) { fail("Could not catch thrown std::bad_cast by catching const std::bad_cast&"); }
}
