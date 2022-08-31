#include <typeinfo>

#include "testing.h"

struct S {
    virtual ~S() = default;
};

TEST() {
    std::bad_typeid default_constructed;
    S* p{};
    try {
        typeid(*p).name();
        fail();
    } catch (const std::bad_typeid& e) {
        expect(default_constructed.what() == e.what());
    } catch (...) {
        fail();
    }
}
