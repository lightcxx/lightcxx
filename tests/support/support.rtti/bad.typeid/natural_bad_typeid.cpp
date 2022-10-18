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
        FAIL();
    } catch (const std::bad_typeid& e) {
        ASSERT(default_constructed.what() == e.what());
    } catch (...) {
        FAIL();
    }
}
