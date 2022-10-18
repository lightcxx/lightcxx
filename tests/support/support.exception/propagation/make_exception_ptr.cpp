#include <exception>

#include "testing.h"

TEST(int_) {
    auto exc = std::make_exception_ptr(4);
    ASSERT_TYPE(std::exception_ptr&, exc);
    ASSERT(exc != nullptr);

    try {
        std::rethrow_exception(exc);
    } catch (int& v) {
        ASSERT(v == 4);
    } catch (...) {
        FAIL();
    }
}

TEST(exception_) {
    auto exc = std::make_exception_ptr(std::exception());
    ASSERT_TYPE(std::exception_ptr&, exc);
    ASSERT(exc != nullptr);

    try {
        std::rethrow_exception(exc);
    } catch (std::exception&) {
    } catch (...) {
        FAIL();
    }
}

TEST(catch_by_base_class) {
    auto exc = std::make_exception_ptr(std::bad_exception());
    ASSERT_TYPE(std::exception_ptr&, exc);
    ASSERT(exc != nullptr);

    try {
        std::rethrow_exception(exc);
    } catch (std::exception&) {
    } catch (...) {
        FAIL();
    }
}

TEST(current_exception_is_equal_to_initial) {
    auto exc = std::make_exception_ptr(4);
    ASSERT_TYPE(std::exception_ptr&, exc);
    ASSERT(exc != nullptr);

    try {
        std::rethrow_exception(exc);
    } catch (...) {
        ASSERT(std::current_exception() == exc);
    }
}
