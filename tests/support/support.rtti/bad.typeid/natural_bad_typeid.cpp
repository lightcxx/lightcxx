#include <typeinfo>

#include "testing.h"

struct S {
    virtual ~S() = default;
};

TEST() {
    std::bad_typeid default_constructed;
    [[maybe_unused]] S* p{};
    try {
        [[maybe_unused]] const char* name = typeid(*p).name();
        fail();
    } catch (const std::bad_typeid& e) {
        expect(default_constructed.what() == e.what());
    } catch (...) {
        fail();
    }
}
