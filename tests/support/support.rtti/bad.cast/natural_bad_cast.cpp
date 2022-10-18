#include <typeinfo>

#include "testing.h"

struct Foo {
    virtual ~Foo() {}
};
struct Bar {
    virtual ~Bar() {}
};

TEST() {
    std::bad_cast default_constructed;

    Bar b;
    try {
        (void)dynamic_cast<Foo&>(b);
        FAIL();
    } catch (const std::bad_cast& e) {
        ASSERT(default_constructed.what() == e.what());
    } catch (...) {
        FAIL();
    }
}
