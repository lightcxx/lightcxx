#include <exception>

#include "testing.h"

TEST(int_) {
    auto exc = std::make_exception_ptr(4);
    expect_type(std::exception_ptr&, exc);
    expect(exc != nullptr);

    try {
        std::rethrow_exception(exc);
    } catch (int& v) { expect(v == 4); } catch (...) {
        fail();
    }
}

TEST(exception_) {
    auto exc = std::make_exception_ptr(std::exception());
    expect_type(std::exception_ptr&, exc);
    expect(exc != nullptr);

    try {
        std::rethrow_exception(exc);
    } catch (std::exception&) {
    } catch (...) { fail(); }
}

TEST(catch_by_base_class) {
    auto exc = std::make_exception_ptr(std::bad_exception());
    expect_type(std::exception_ptr&, exc);
    expect(exc != nullptr);

    try {
        std::rethrow_exception(exc);
    } catch (std::exception&) {
    } catch (...) { fail(); }
}

TEST(current_exception_is_equal_to_initial) {
    auto exc = std::make_exception_ptr(4);
    expect_type(std::exception_ptr&, exc);
    expect(exc != nullptr);

    try {
        std::rethrow_exception(exc);
    } catch (...) { expect(std::current_exception() == exc); }
}
