#include <exception>

#include "testing/test.h"

TEST(int_) {
    auto exc = std::make_exception_ptr(4);
    expectType<std::exception_ptr&>(exc);
    expect(exc != nullptr);

    try {
        std::rethrow_exception(exc);
    } catch (int& v) { expect(v == 4); } catch (...) {
        fail();
    }
}

TEST(exception_) {
    auto exc = std::make_exception_ptr(std::exception());
    expectType<std::exception_ptr&>(exc);
    expect(exc != nullptr);

    try {
        std::rethrow_exception(exc);
    } catch (std::exception&) {
    } catch (...) { fail(); }
}

TEST(catch_by_base_class) {
    auto exc = std::make_exception_ptr(std::bad_exception());
    expectType<std::exception_ptr&>(exc);
    expect(exc != nullptr);

    try {
        std::rethrow_exception(exc);
    } catch (std::exception&) {
    } catch (...) { fail(); }
}

TEST(current_exception_is_equal_to_initial) {
    auto exc = std::make_exception_ptr(4);
    expectType<std::exception_ptr&>(exc);
    expect(exc != nullptr);

    try {
        std::rethrow_exception(exc);
    } catch (...) {
        expect(std::current_exception() == exc);
    }
}
