#include <exception>

#include "testing.h"

struct WithoutNested {
    int x;

    explicit WithoutNested(int x)
            : x(x) {}

    virtual ~WithoutNested() = default;
};

struct WithNested : std::nested_exception {
    int x;

    explicit WithNested(int x)
            : x(x) {}

    ~WithNested() override = default;
};

struct Final final {
    virtual ~Final() = default;
};

TEST(int_) {
    try {
        int i = 7;
        std::throw_with_nested(i);
    } catch (int i) {
        ASSERT(i == 7);
    } catch (...) {
        FAIL();
    }
}

TEST(nullptr_t) {
    try {
        std::throw_with_nested(nullptr);
    } catch (std::nullptr_t) {
    } catch (...) {
        FAIL();
    }
}

TEST(final_class) {
    try {
        std::throw_with_nested(Final());
    } catch (Final& f) {
        ASSERT(dynamic_cast<const std::nested_exception*>(&f) == nullptr);
    } catch (...) {
        FAIL();
    }
}

TEST(catch_by_original_type) {
    try {
        WithoutNested t{3};
        std::throw_with_nested(t);
    } catch (const WithoutNested& t) {
        ASSERT(t.x == 3);
        ASSERT(dynamic_cast<const std::nested_exception&>(t).nested_ptr() == nullptr);
    } catch (...) {
        FAIL();
    }
}

TEST(catch_by_std_nested_exception) {
    try {
        WithoutNested t{3};
        std::throw_with_nested(t);
    } catch (const std::nested_exception& t) {
        ASSERT(t.nested_ptr() == nullptr);
        ASSERT(dynamic_cast<const WithoutNested&>(t).x == 3);
    } catch (...) {
        FAIL();
    }
}

TEST(throw_instance_of_WithNested_catch_by_WithNested) {
    try {
        WithNested t{5};
        std::throw_with_nested(t);
    } catch (const WithNested& t) {
        ASSERT(t.x == 5);
        ASSERT(dynamic_cast<const std::nested_exception&>(t).nested_ptr() == nullptr);
    } catch (...) {
        FAIL();
    }
}

TEST(throw_instance_of_WithNested_catch_by_std_nested_exception) {
    try {
        WithNested t{5};
        std::throw_with_nested(t);
    } catch (const std::nested_exception& t) {
        ASSERT(t.nested_ptr() == nullptr);
        ASSERT(dynamic_cast<const WithNested&>(t).x == 5);
    } catch (...) {
        FAIL();
    }
}
