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
        Foo& f = dynamic_cast<Foo&>(b);
        fail();
    } catch (const std::bad_cast& e) {
        expect(default_constructed.what() == e.what());
    } catch (...) { fail(); }
}
