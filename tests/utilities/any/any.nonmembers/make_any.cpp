#include <any>

#include "counted_type.h"
#include "testing.h"

struct large_object {
    [[maybe_unused]] char data[4096];  // Clearly not SBO-friendly type.
};

struct init_list_ctor {
    struct exc {};

    init_list_ctor(std::initializer_list<int>) {}
    init_list_ctor(std::initializer_list<int>, int) {}
    init_list_ctor(std::initializer_list<int>, int, int) {
        throw exc{};
    }
};

struct throwing_ctor {
    struct copy_exc {};
    struct move_exc {};

    throwing_ctor() = default;
    throwing_ctor(const throwing_ctor&) {
        throw copy_exc{};
    }
    throwing_ctor(throwing_ctor&&) {
        throw move_exc{};
    }
};

int func(int a, int b) {
    return a + b;
}

TEST(make_any_small) {
    cnttype::reset();
    std::any any_val = std::make_any<cnttype>(7);
    expect(any_val.has_value());
    expect(any_cast<cnttype>(&any_val)->val == 7);
    expect(any_val.type() == typeid(cnttype));
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
}

TEST(make_any_non_const_array) {
    cnttype val[3]{};
    cnttype::reset();
    std::any any_val = std::make_any<cnttype[3]>(val);
    expect(any_val.has_value());
    expect(any_val.type() == typeid(cnttype*));
    expect(any_cast<cnttype*>(any_val) == val);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
}

TEST(make_any_const_array) {
    const cnttype val[3]{};
    cnttype::reset();
    std::any any_val = std::make_any<const cnttype[3]>(val);
    expect(any_val.has_value());
    expect(any_val.type() == typeid(const cnttype*));
    expect(any_cast<const cnttype*>(any_val) == val);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
}

TEST(make_any_function) {
    std::any any_val = std::make_any<int(int, int)>(func);
    expect(any_val.has_value());
    expect(any_val.type() == typeid(int (*)(int, int)));
    expect(any_cast<int (*)(int, int)>(any_val) == &func);
}

TEST(make_any_exception) {
    throwing_ctor val{};
    try {
        std::any any_val = std::make_any<throwing_ctor>(val);
        fail();
    } catch (const throwing_ctor::copy_exc&) {
    }
    try {
        std::any any_val = std::make_any<throwing_ctor>(std::move(val));
        fail();
    } catch (const throwing_ctor::move_exc&) {
    }
}

TEST(make_any_initlist_ctor) {
    std::any any_val = std::make_any<init_list_ctor>({1, 2, 3});
    expect(any_val.has_value());
    expect(any_cast<init_list_ctor>(&any_val) != nullptr);
    expect(any_val.type() == typeid(init_list_ctor));
}

TEST(make_any_initlist_ctor_extra_arg) {
    std::any any_val = std::make_any<init_list_ctor>({1, 2, 3}, 1);
    expect(any_val.has_value());
    expect(any_cast<init_list_ctor>(&any_val) != nullptr);
    expect(any_val.type() == typeid(init_list_ctor));
}

TEST(make_any_initlist_ctor_exception) {
    try {
        std::any any_val = std::make_any<init_list_ctor>({1, 2, 3}, 1, 2);
        fail();
    } catch (const init_list_ctor::exc&) {
    }
}
