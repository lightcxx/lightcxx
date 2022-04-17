#include <exception>

#include "testing.h"

TEST(default_constructor_with_no_current_exception) {
    std::nested_exception exc;
    expect(exc.nested_ptr() == nullptr);
}

TEST(default_constructor_with_current_exception) {
    try {
        throw 5;
    } catch (...) {
        std::nested_exception exc;
        expect(exc.nested_ptr() != nullptr);
    }
}

TEST(copy_constructor_with_no_current_exception) {
    std::nested_exception exc;
    expect(exc.nested_ptr() == nullptr);

    std::nested_exception exc_copy(exc);
    expect(exc_copy.nested_ptr() == nullptr);
}

TEST(copy_constructor_with_current_exception) {
    try {
        throw 5;
    } catch (...) {
        std::nested_exception exc;
        expect(exc.nested_ptr() != nullptr);

        std::nested_exception exc_copy(exc);
        expect(exc_copy.nested_ptr() != nullptr);
    }
}

TEST(copy_assignment_with_no_current_exception) {
    std::nested_exception exc;
    expect(exc.nested_ptr() == nullptr);

    std::nested_exception exc_copy;
    exc_copy = exc;
    expect(exc_copy.nested_ptr() == nullptr);
}

TEST(copy_assignment_with_current_exception) {
    try {
        throw 5;
    } catch (...) {
        std::nested_exception exc;
        expect(exc.nested_ptr() != nullptr);

        std::nested_exception exc_copy;
        exc_copy = exc;
        expect(exc_copy.nested_ptr() != nullptr);
    }
}

TEST(manual_rethrow_nested_ptr) {
    try {
        throw 5;
    } catch (...) {
        std::nested_exception exc;
        expect(exc.nested_ptr() != nullptr);

        try {
            std::rethrow_exception(exc.nested_ptr());
        } catch (int& v) {
            expect(v == 5);
        } catch (...) {
            fail();
        }
    }
}

TEST(rethrow_nested_from_default_constructed) {
    try {
        throw 5;
    } catch (...) {
        std::nested_exception exc;
        expect(exc.nested_ptr() != nullptr);

        try {
            exc.rethrow_nested();
        } catch (int& v) {
            expect(v == 5);
        } catch (...) {
            fail();
        }
    }
}

TEST(rethrow_nested_from_copy_assigned) {
    std::nested_exception exc_copy;
    try {
        throw 5;
    } catch (...) {
        std::nested_exception exc;
        expect(exc.nested_ptr() != nullptr);

        exc_copy = exc;

        try {
            exc_copy.rethrow_nested();
        } catch (int& v) {
            expect(v == 5);
        } catch (...) {
            fail();
        }
    }
}

TEST(rethrow_nested_from_copy_constructed) {
    try {
        throw 5;
    } catch (...) {
        std::nested_exception exc;
        expect(exc.nested_ptr() != nullptr);
        std::nested_exception exc_copy(exc);
        expect(exc_copy.nested_ptr() != nullptr);

        try {
            exc_copy.rethrow_nested();
        } catch (int& v) {
            expect(v == 5);
        } catch (...) {
            fail();
        }
    }
}
