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

TEST(default_ctor_constexpr) {
    static constinit std::any constexpr_ctor_any{};
    ASSERT_NOEXCEPT(std::any{});
}

TEST(default_ctor) {
    std::any default_ctor{};
    ASSERT(!default_ctor.has_value());
}

TEST(default_ctor_implicit) {
    [](std::any a) {
        ASSERT(!a.has_value());
    }({});
}

TEST(copy_ctor_no_value) {
    std::any no_val;
    std::any no_val_cpy(no_val);
    ASSERT(!no_val_cpy.has_value());
}

TEST(copy_ctor_small) {
    std::any counted_type_val(std::in_place_type<cnttype>);
    cnttype::reset();
    std::any counted_type_val_cpy(counted_type_val);
    ASSERT(cnttype::copy_ctor_count == 1);
    ASSERT(counted_type_val_cpy.has_value());
    ASSERT(counted_type_val_cpy.type() == typeid(cnttype));
    ASSERT(any_cast<cnttype>(&counted_type_val_cpy) != nullptr);
    ASSERT(counted_type_val.has_value());
    ASSERT(counted_type_val.type() == typeid(cnttype));
    ASSERT(any_cast<cnttype>(&counted_type_val) != nullptr);
}

TEST(copy_ctor_small_nonmoveable) {
    std::any counted_type_val(std::in_place_type<cnttype_copy>);
    cnttype_copy::reset();
    std::any counted_type_val_cpy(counted_type_val);
    ASSERT(cnttype_copy::copy_ctor_count == 1);
    ASSERT(counted_type_val_cpy.has_value());
    ASSERT(counted_type_val_cpy.type() == typeid(cnttype_copy));
    ASSERT(any_cast<cnttype_copy>(&counted_type_val_cpy) != nullptr);
    ASSERT(counted_type_val.has_value());
    ASSERT(counted_type_val.type() == typeid(cnttype_copy));
    ASSERT(any_cast<cnttype_copy>(&counted_type_val) != nullptr);
}

TEST(copy_ctor_large) {
    std::any large_val(std::in_place_type<large_object>);
    std::any large_val_cpy(large_val);
    ASSERT(large_val_cpy.has_value());
    ASSERT(large_val_cpy.type() == typeid(large_object));
    ASSERT(any_cast<large_object>(&large_val_cpy) != nullptr);
    ASSERT(large_val.has_value());
    ASSERT(large_val.type() == typeid(large_object));
    ASSERT(any_cast<large_object>(&large_val) != nullptr);
}

TEST(copy_ctor_throw) {
    std::any throwing_type_val(std::in_place_type<throwing_ctor>);
    try {
        std::any throwing_type_val_cpy(throwing_type_val);
        FAIL();
    } catch (const throwing_ctor::copy_exc&) {
    }
    ASSERT(throwing_type_val.has_value());
    ASSERT(throwing_type_val.type() == typeid(throwing_ctor));
    ASSERT(std::any_cast<throwing_ctor>(&throwing_type_val) != nullptr);
}

TEST(move_ctor_no_value) {
    std::any no_val;
    std::any no_val_mv(std::move(no_val));
    ASSERT(!no_val_mv.has_value());
}

TEST(move_ctor_small_value) {
    std::any counted_type_val(std::in_place_type<cnttype>);
    cnttype::reset();
    std::any counted_type_val_mv(std::move(counted_type_val));
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count <= 1);  // not necessarily called
    ASSERT(counted_type_val_mv.has_value());
    ASSERT(counted_type_val_mv.type() == typeid(cnttype));
    ASSERT(any_cast<cnttype>(&counted_type_val_mv) != nullptr);
}

TEST(move_ctor_copy_only_value) {
    std::any counted_type_val(std::in_place_type<cnttype_copy>);
    cnttype_copy::reset();
    std::any counted_type_val_mv(std::move(counted_type_val));
    ASSERT(cnttype_copy::copy_ctor_count == 0);
    ASSERT(counted_type_val_mv.has_value());
    ASSERT(counted_type_val_mv.type() == typeid(cnttype_copy));
    ASSERT(any_cast<cnttype_copy>(&counted_type_val_mv) != nullptr);
}

TEST(move_ctor_large_value) {
    std::any large_object_val(std::in_place_type<large_object>);
    std::any large_object_val_mv(std::move(large_object_val));
    ASSERT(large_object_val_mv.has_value());
    ASSERT(large_object_val_mv.type() == typeid(large_object));
    ASSERT(any_cast<large_object>(&large_object_val_mv) != nullptr);
}

TEST(move_ctor_throwing_value) {
    std::any throwing_type_val(std::in_place_type<throwing_ctor>);
    std::any throwing_type_val_mv(std::move(throwing_type_val));  // never calls move constructor since it's not noexcept.
    ASSERT(throwing_type_val_mv.has_value());
    ASSERT(std::any_cast<throwing_ctor>(&throwing_type_val_mv) != nullptr);
}

TEST(value_ctor_lvalue) {
    cnttype val{7};
    cnttype::reset();
    std::any any_val(val);
    ASSERT(any_val.has_value());
    ASSERT(any_cast<cnttype&>(any_val).val == 7);
    ASSERT(any_val.type() == typeid(cnttype));
    ASSERT(cnttype::copy_ctor_count == 1);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(value_ctor_rvalue_move) {
    cnttype val{7};
    cnttype::reset();
    std::any any_val(std::move(val));
    ASSERT(any_val.has_value());
    ASSERT(any_cast<cnttype&>(any_val).val == 7);
    ASSERT(any_val.type() == typeid(cnttype));
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 1);
}

TEST(value_ctor_rvalue_temporary) {
    cnttype::reset();
    std::any any_val(cnttype{7});
    ASSERT(any_val.has_value());
    ASSERT(any_cast<cnttype&>(any_val).val == 7);
    ASSERT(any_val.type() == typeid(cnttype));
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 1);
}

TEST(value_ctor_non_const_array) {
    cnttype val[3]{};
    cnttype::reset();
    std::any any_val(val);
    ASSERT(any_val.has_value());
    ASSERT(any_val.type() == typeid(cnttype*));
    ASSERT(any_cast<cnttype*>(any_val) == val);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(value_ctor_const_array) {
    const cnttype val[3]{};
    cnttype::reset();
    std::any any_val(val);
    ASSERT(any_val.has_value());
    ASSERT(any_val.type() == typeid(const cnttype*));
    ASSERT(any_cast<const cnttype*>(any_val) == val);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(value_ctor_function) {
    std::any any_val(func);
    ASSERT(any_val.has_value());
    ASSERT(any_val.type() == typeid(int (*)(int, int)));
    ASSERT(any_cast<int (*)(int, int)>(any_val) == &func);
}

TEST(value_ctor_exception) {
    throwing_ctor val{};
    try {
        std::any any_val(val);
        FAIL();
    } catch (const throwing_ctor::copy_exc&) {
    }
    try {
        std::any any_val(std::move(val));
        FAIL();
    } catch (const throwing_ctor::move_exc&) {
    }
}

TEST(value_ctor_implicit) {
    cnttype::reset();
    [](std::any any_val) {
        ASSERT(any_val.has_value());
        ASSERT(any_cast<cnttype&>(any_val).val == 7);
        ASSERT(any_val.type() == typeid(cnttype));
    }(cnttype{7});
    ASSERT(cnttype::move_ctor_count <= 1);
}

TEST(in_place_ctor_small) {
    cnttype::reset();
    std::any any_val(std::in_place_type<cnttype>, 7);
    ASSERT(any_val.has_value());
    ASSERT(any_cast<cnttype&>(any_val).val == 7);
    ASSERT(any_val.type() == typeid(cnttype));
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(in_place_ctor_non_const_array) {
    cnttype val[3]{};
    cnttype::reset();
    std::any any_val(std::in_place_type<cnttype[3]>, val);
    ASSERT(any_val.has_value());
    ASSERT(any_val.type() == typeid(cnttype*));
    ASSERT(any_cast<cnttype*>(any_val) == val);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(in_place_ctor_const_array) {
    const cnttype val[3]{};
    cnttype::reset();
    std::any any_val(std::in_place_type<const cnttype[3]>, val);
    ASSERT(any_val.has_value());
    ASSERT(any_val.type() == typeid(const cnttype*));
    ASSERT(any_cast<const cnttype*>(any_val) == val);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(in_place_ctor_function) {
    std::any any_val(std::in_place_type<int(int, int)>, func);
    ASSERT(any_val.has_value());
    ASSERT(any_val.type() == typeid(int (*)(int, int)));
    ASSERT(any_cast<int (*)(int, int)>(any_val) == &func);
}

TEST(in_place_ctor_exception) {
    throwing_ctor val{};
    try {
        std::any any_val(std::in_place_type<throwing_ctor>, val);
        FAIL();
    } catch (const throwing_ctor::copy_exc&) {
    }
    try {
        std::any any_val(std::in_place_type<throwing_ctor>, std::move(val));
        FAIL();
    } catch (const throwing_ctor::move_exc&) {
    }
}

TEST(in_place_initlist_ctor) {
    std::any any_val(std::in_place_type<init_list_ctor>, {1, 2, 3});
    ASSERT(any_val.has_value());
    ASSERT(any_cast<init_list_ctor>(&any_val) != nullptr);
    ASSERT(any_val.type() == typeid(init_list_ctor));
}

TEST(in_place_initlist_ctor_extra_arg) {
    std::any any_val(std::in_place_type<init_list_ctor>, {1, 2, 3}, 1);
    ASSERT(any_val.has_value());
    ASSERT(any_cast<init_list_ctor>(&any_val) != nullptr);
    ASSERT(any_val.type() == typeid(init_list_ctor));
}

TEST(in_place_initlist_ctor_exception) {
    try {
        std::any any_val(std::in_place_type<init_list_ctor>, {1, 2, 3}, 1, 2);
        FAIL();
    } catch (const init_list_ctor::exc&) {
    }
}

TEST(dtor) {
    cnttype::reset();
    {
        std::any val(std::in_place_type<cnttype>);
        {
            std::any val_cpy(val);
        }
        ASSERT(cnttype::dtor_count == 1);
        {
            std::any val_mv(std::move(val));
        }
        ASSERT(cnttype::dtor_count == 2);
    }
    ASSERT(cnttype::dtor_count == 2);  // deleted moved-from instance
}

