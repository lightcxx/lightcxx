#include <exception>

#include "testing.h"

TEST(int_) {
    std::rethrow_if_nested(5);  // should do nothing
}

TEST(pointer) {
    std::rethrow_if_nested(nullptr);  // should do nothing
}

struct Basic {};
TEST(basic_class) {
    std::rethrow_if_nested(Basic());  // should do nothing
}

struct Polymorphic : public std::exception {
    ~Polymorphic() override = default;
};
TEST(polymorphic_class) {
    std::rethrow_if_nested(Polymorphic());  // should do nothing
}

struct WithPrivateNestedException : public std::exception, private std::nested_exception {
    ~WithPrivateNestedException() override = default;
};
TEST(polymorphic_class_with_private_nested_exception) {
    std::rethrow_if_nested(WithPrivateNestedException());  // should do nothing
}

struct ConvertibleToNestedException : public std::exception {
    ~ConvertibleToNestedException() override = default;

    operator std::nested_exception() noexcept {
        return std::nested_exception();
    }
};
TEST(polymorphic_class_convertible_to_nested_exception) {
    std::rethrow_if_nested(ConvertibleToNestedException());  // should do nothing
}

class WithNestedException1 : public std::nested_exception {};
class WithNestedException2 : public std::nested_exception {};
class WithAmbiguousNestedException : public WithNestedException1, public WithNestedException2 {};
TEST(polymorphic_class_with_ambiguous_nested_exception) {
    std::rethrow_if_nested(WithAmbiguousNestedException());  // should do nothing
}

class WithOverrideForAddressOfOperator : public std::exception {
    ~WithOverrideForAddressOfOperator() override = default;

    WithOverrideForAddressOfOperator* operator&() {
        fail();
    }
};
TEST(polymorphic_class_with_override_for_address_of_operator) {
    std::rethrow_if_nested(ConvertibleToNestedException());  // should do nothing
}

TEST(rethrow_nested_exception) {
    try {
        throw 3;
    } catch (...) {
        try {
            std::rethrow_if_nested(std::nested_exception());
            fail();
        } catch (int& v) { expect(v == 3); } catch (...) {
            fail();
        }
    }
}

struct ExceptionWithNested : public std::exception, public std::nested_exception {
    ~ExceptionWithNested() override = default;

    const char* what() const noexcept override {
        return "my_exception";
    }
};
TEST(rethrow_derived_from_nested_exception) {
    try {
        throw 3;
    } catch (...) {
        try {
            std::rethrow_if_nested(ExceptionWithNested());
            fail();
        } catch (int& v) { expect(v == 3); } catch (...) {
            fail();
        }
    }
}

TEST(rethrow_value_with_dynamic_type_derived_from_nested_exception) {
    try {
        throw 3;
    } catch (...) {
        try {
            auto exc = ExceptionWithNested();
            std::exception& e = exc;
            std::rethrow_if_nested(e);
            fail();
        } catch (int& v) { expect(v == 3); } catch (...) {
            fail();
        }
    }
}
