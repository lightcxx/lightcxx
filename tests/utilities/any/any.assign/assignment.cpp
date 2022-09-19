#include <any>

#include "counted_type.h"
#include "testing.h"

struct large_cnttype {
    Testing::cnttype nested;
    [[maybe_unused]] char padding[4096];  // Clearly not SBO-friendly type.

    large_cnttype() = default;
    large_cnttype(int source)
            : nested(source) {}
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

TEST(copy_assign_no_val_to_no_val) {
    std::any source;

    std::any target;
    std::any& result = (target = source);
    expect(&result == &target);
    expect(!target.has_value());
}

TEST(copy_assign_small_val_to_no_val) {
    cnttype::reset();
    std::any source(std::in_place_type<cnttype>);

    std::any target;
    std::any& result = (target = source);
    expect(&result == &target);
    expect(cnttype::copy_ctor_count == 1);
    expect(target.has_value());
    expect(target.type() == typeid(cnttype));
    expect(any_cast<cnttype>(&target) != nullptr);
    expect(source.has_value());
    expect(source.type() == typeid(cnttype));
    expect(any_cast<cnttype>(&source) != nullptr);
}

TEST(copy_assign_large_val_to_no_val) {
    cnttype::reset();
    std::any source(std::in_place_type<large_cnttype>);

    std::any target;
    std::any& result = (target = source);
    expect(&result == &target);
    expect(cnttype::copy_ctor_count == 1);
    expect(target.has_value());
    expect(target.type() == typeid(large_cnttype));
    expect(any_cast<large_cnttype>(&target) != nullptr);
    expect(source.has_value());
    expect(source.type() == typeid(large_cnttype));
    expect(any_cast<large_cnttype>(&source) != nullptr);
}

TEST(copy_assign_exception_to_no_val) {
    std::any source(std::in_place_type<throwing_ctor>);

    std::any target;
    try {
        std::any& result = (target = source);
        expect(&result == &target);
        fail();
    } catch (const throwing_ctor::copy_exc&) {
    }
    expect(!target.has_value());
    expect(source.has_value());
    expect(source.type() == typeid(throwing_ctor));
    expect(any_cast<throwing_ctor>(&source) != nullptr);
}

TEST(copy_assign_no_val_to_small_val) {
    std::any source;

    std::any target(std::in_place_type<cnttype>);
    cnttype::reset();
    std::any& result = (target = source);
    expect(&result == &target);
    expect(!target.has_value());
    expect(!source.has_value());
    expect(cnttype::dtor_count == 1);
}

TEST(copy_assign_small_val_to_small_val) {
    std::any source(std::in_place_type<cnttype>, 345);

    cnttype::reset();
    std::any target(std::in_place_type<cnttype>, 777);
    std::any& result = (target = source);
    expect(&result == &target);
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 1);
    expect(target.has_value());
    expect(target.type() == typeid(cnttype));
    expect(any_cast<cnttype>(&target) != nullptr);
    expect(any_cast<cnttype>(&target)->val == 345);
    expect(source.has_value());
    expect(source.type() == typeid(cnttype));
    expect(any_cast<cnttype>(&source) != nullptr);
    expect(any_cast<cnttype>(&source)->val == 345);
}

TEST(copy_assign_large_val_to_small_val) {
    std::any source(std::in_place_type<large_cnttype>, 345);

    cnttype::reset();
    std::any target(std::in_place_type<cnttype>, 777);
    std::any& result = (target = source);
    expect(&result == &target);
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 1);
    expect(target.has_value());
    expect(target.type() == typeid(large_cnttype));
    expect(any_cast<large_cnttype>(&target) != nullptr);
    expect(any_cast<large_cnttype>(&target)->nested.val == 345);
    expect(source.has_value());
    expect(source.type() == typeid(large_cnttype));
    expect(any_cast<large_cnttype>(&source) != nullptr);
    expect(any_cast<large_cnttype>(&source)->nested.val == 345);
}

TEST(copy_assign_exception_to_small_val) {
    std::any source(std::in_place_type<throwing_ctor>);

    cnttype::reset();
    std::any target(std::in_place_type<cnttype>, 777);
    try {
        std::any& result = (target = source);
        expect(&result == &target);
        fail();
    } catch (const throwing_ctor::copy_exc&) {
    }
    expect(cnttype::dtor_count == 0);
    expect(target.has_value());
    expect(target.type() == typeid(cnttype));
    expect(any_cast<cnttype>(&target) != nullptr);
    expect(any_cast<cnttype>(&target)->val == 777);
    expect(source.has_value());
    expect(source.type() == typeid(throwing_ctor));
    expect(any_cast<throwing_ctor>(&source) != nullptr);
}

TEST(copy_assign_no_val_to_large_val) {
    std::any source;

    std::any target(std::in_place_type<large_cnttype>);
    cnttype::reset();
    std::any& result = (target = source);
    expect(&result == &target);
    expect(!target.has_value());
    expect(!source.has_value());
    expect(cnttype::dtor_count == 1);
}

TEST(copy_assign_small_val_to_large_val) {
    std::any source(std::in_place_type<cnttype>, 345);

    cnttype::reset();
    std::any target(std::in_place_type<large_cnttype>, 777);
    std::any& result = (target = source);
    expect(&result == &target);
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 1);
    expect(target.has_value());
    expect(target.type() == typeid(cnttype));
    expect(any_cast<cnttype>(&target) != nullptr);
    expect(any_cast<cnttype>(&target)->val == 345);
    expect(source.has_value());
    expect(source.type() == typeid(cnttype));
    expect(any_cast<cnttype>(&source) != nullptr);
    expect(any_cast<cnttype>(&source)->val == 345);
}

TEST(copy_assign_large_val_to_large_val) {
    std::any source(std::in_place_type<large_cnttype>, 345);

    cnttype::reset();
    std::any target(std::in_place_type<large_cnttype>, 777);
    std::any& result = (target = source);
    expect(&result == &target);
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 1);
    expect(target.has_value());
    expect(target.type() == typeid(large_cnttype));
    expect(any_cast<large_cnttype>(&target) != nullptr);
    expect(any_cast<large_cnttype>(&target)->nested.val == 345);
    expect(source.has_value());
    expect(source.type() == typeid(large_cnttype));
    expect(any_cast<large_cnttype>(&source) != nullptr);
    expect(any_cast<large_cnttype>(&source)->nested.val == 345);
}

TEST(copy_assign_exception_to_large_val) {
    std::any source(std::in_place_type<throwing_ctor>);

    cnttype::reset();
    std::any target(std::in_place_type<large_cnttype>, 777);
    try {
        std::any& result = (target = source);
        expect(&result == &target);
        fail();
    } catch (const throwing_ctor::copy_exc&) {
    }
    expect(cnttype::dtor_count == 0);
    expect(target.has_value());
    expect(target.type() == typeid(large_cnttype));
    expect(any_cast<large_cnttype>(&target) != nullptr);
    expect(any_cast<large_cnttype>(&target)->nested.val == 777);
    expect(source.has_value());
    expect(source.type() == typeid(throwing_ctor));
    expect(any_cast<throwing_ctor>(&source) != nullptr);
}

TEST(copy_assign_self_assign) {
    std::any source(std::in_place_type<large_cnttype>, 345);
    cnttype::reset();
    auto& source_ref = source;
    compiler_forget(source_ref);
    auto& result = (source = source_ref);
    expect(&result == &source);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::copy_assign_count == 0);
    expect(cnttype::move_ctor_count == 0);
    expect(cnttype::move_assign_count == 0);
    expect(cnttype::dtor_count == 0);
    expect(source.has_value());
    expect(source.type() == typeid(large_cnttype));
    expect(any_cast<large_cnttype>(&source) != nullptr);
    expect(any_cast<large_cnttype>(&source)->nested.val == 345);
}

TEST(move_assign_no_val_to_no_val) {
    std::any source;

    std::any target;
    auto& result = (target = std::move(source));
    expect(&result == &target);
    expect(!target.has_value());
}

TEST(move_assign_small_val_to_no_val) {
    cnttype::reset();
    std::any source(std::in_place_type<cnttype>);

    std::any target;
    auto& result = (target = std::move(source));
    expect(&result == &target);
    expect(cnttype::dtor_count == 0);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count <= 1);
    expect(target.has_value());
    expect(target.type() == typeid(cnttype));
    expect(any_cast<cnttype>(&target) != nullptr);
    expect(!source.has_value());
}

TEST(move_assign_large_val_to_no_val) {
    cnttype::reset();
    std::any source(std::in_place_type<large_cnttype>);

    std::any target;
    auto& result = (target = std::move(source));
    expect(&result == &target);
    expect(cnttype::dtor_count == 0);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count <= 1);
    expect(target.has_value());
    expect(target.type() == typeid(large_cnttype));
    expect(any_cast<large_cnttype>(&target) != nullptr);
    expect(!source.has_value());
}

TEST(move_assign_no_val_to_small_val) {
    std::any source;

    std::any target(std::in_place_type<cnttype>);
    cnttype::reset();
    auto& result = (target = std::move(source));
    expect(&result == &target);
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
    expect(!target.has_value());
    expect(!source.has_value());
}

TEST(move_assign_small_val_to_small_val) {
    std::any source(std::in_place_type<cnttype>, 345);

    cnttype::reset();
    std::any target(std::in_place_type<cnttype>, 777);
    auto& result = (target = std::move(source));
    expect(&result == &target);
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
    expect(target.has_value());
    expect(target.type() == typeid(cnttype));
    expect(any_cast<cnttype>(&target) != nullptr);
    expect(any_cast<cnttype>(&target)->val == 345);
    expect(!source.has_value());
}

TEST(move_assign_large_val_to_small_val) {
    std::any source(std::in_place_type<large_cnttype>, 345);

    cnttype::reset();
    std::any target(std::in_place_type<cnttype>, 777);
    auto& result = (target = std::move(source));
    expect(&result == &target);
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
    expect(target.has_value());
    expect(target.type() == typeid(large_cnttype));
    expect(any_cast<large_cnttype>(&target) != nullptr);
    expect(any_cast<large_cnttype>(&target)->nested.val == 345);
    expect(!source.has_value());
}

TEST(move_assign_no_val_to_large_val) {
    std::any source;

    std::any target(std::in_place_type<large_cnttype>);
    cnttype::reset();
    auto& result = (target = std::move(source));
    expect(&result == &target);
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
    expect(!target.has_value());
    expect(!source.has_value());
}

TEST(move_assign_small_val_to_large_val) {
    std::any source(std::in_place_type<cnttype>, 345);

    cnttype::reset();
    std::any target(std::in_place_type<large_cnttype>, 777);
    auto& result = (target = std::move(source));
    expect(&result == &target);
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
    expect(target.has_value());
    expect(target.type() == typeid(cnttype));
    expect(any_cast<cnttype>(&target) != nullptr);
    expect(any_cast<cnttype>(&target)->val == 345);
    expect(!source.has_value());
}

TEST(move_assign_large_val_to_large_val) {
    std::any source(std::in_place_type<large_cnttype>, 345);

    cnttype::reset();
    std::any target(std::in_place_type<large_cnttype>, 777);
    auto& result = (target = std::move(source));
    expect(&result == &target);
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
    expect(target.has_value());
    expect(target.type() == typeid(large_cnttype));
    expect(any_cast<large_cnttype>(&target) != nullptr);
    expect(any_cast<large_cnttype>(&target)->nested.val == 345);
    expect(!source.has_value());
}

TEST(move_assign_self_assign) {
    std::any source(std::in_place_type<large_cnttype>, 345);
    cnttype::reset();
    auto& source_ref = source;
    compiler_forget(source_ref);
    auto& result = (source = std::move(source_ref));
    expect(&result == &source);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::copy_assign_count == 0);
    expect(cnttype::move_ctor_count == 0);
    expect(cnttype::move_assign_count == 0);
    expect(cnttype::dtor_count == 0);
    expect(source.has_value());
    expect(source.type() == typeid(large_cnttype));
    expect(any_cast<large_cnttype>(&source) != nullptr);
    expect(any_cast<large_cnttype>(&source)->nested.val == 345);
}

TEST(value_assign_lvalue_to_no_val) {
    cnttype source{7};
    cnttype::reset();
    std::any target;
    auto& result = (target = source);
    expect(&result == &target);
    expect(target.has_value());
    expect(any_cast<cnttype>(&target)->val == 7);
    expect(target.type() == typeid(cnttype));
    expect(cnttype::copy_ctor_count == 1);
    expect(cnttype::move_ctor_count == 0);
}

TEST(value_assign_rvalue_move_to_no_val) {
    cnttype source{7};
    cnttype::reset();
    std::any target;
    auto& result = (target = std::move(source));
    expect(&result == &target);
    expect(target.has_value());
    expect(any_cast<cnttype>(&target)->val == 7);
    expect(target.type() == typeid(cnttype));
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 1);
}

TEST(value_assign_rvalue_temporary_to_no_val) {
    cnttype::reset();
    std::any target;
    auto& result = (target = cnttype{7});
    expect(&result == &target);
    expect(target.has_value());
    expect(any_cast<cnttype>(&target)->val == 7);
    expect(target.type() == typeid(cnttype));
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 1);
}

TEST(value_assign_non_const_array_to_no_val) {
    cnttype source[3]{};
    cnttype::reset();
    std::any target;
    auto& result = (target = source);
    expect(&result == &target);
    expect(target.has_value());
    expect(target.type() == typeid(cnttype*));
    expect(any_cast<cnttype*>(target) == source);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
}

TEST(value_assign_const_array_to_no_val) {
    const cnttype source[3]{};
    cnttype::reset();
    std::any target;
    auto& result = (target = source);
    expect(&result == &target);
    expect(target.has_value());
    expect(target.type() == typeid(const cnttype*));
    expect(any_cast<const cnttype*>(target) == source);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
}

TEST(value_assign_function_to_no_val) {
    std::any target;
    auto& result = (target = func);
    expect(&result == &target);
    expect(target.has_value());
    expect(target.type() == typeid(int (*)(int, int)));
    expect(any_cast<int (*)(int, int)>(target) == &func);
}

TEST(value_assign_exception_to_no_val) {
    throwing_ctor source{};
    try {
        std::any target;
        target = source;
        compiler_forget(target);
        fail();
    } catch (const throwing_ctor::copy_exc&) {
    }
    try {
        std::any target;
        target = std::move(source);
        compiler_forget(target);
        fail();
    } catch (const throwing_ctor::move_exc&) {
    }
}

TEST(value_assign_lvalue_to_small_val) {
    cnttype source{7};
    cnttype::reset();
    std::any target{std::in_place_type<cnttype>};
    auto& result = (target = source);
    expect(&result == &target);
    expect(target.has_value());
    expect(any_cast<cnttype>(&target)->val == 7);
    expect(target.type() == typeid(cnttype));
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 1);
    expect(cnttype::move_ctor_count == 0);
}

TEST(value_assign_rvalue_move_to_small_val) {
    cnttype source{7};
    cnttype::reset();
    std::any target{std::in_place_type<cnttype>, 17};
    auto& result = (target = std::move(source));
    expect(&result == &target);
    expect(target.has_value());
    expect(any_cast<cnttype>(&target)->val == 7);
    expect(target.type() == typeid(cnttype));
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 1);
}

TEST(value_assign_rvalue_temporary_to_small_val) {
    std::any target{std::in_place_type<cnttype>, 17};
    cnttype::reset();
    auto& result = (target = cnttype{7});
    expect(&result == &target);
    expect(target.has_value());
    expect(any_cast<cnttype>(&target)->val == 7);
    expect(target.type() == typeid(cnttype));
    expect(cnttype::dtor_count == 2);  // one for the temporary variable
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 1);
}

TEST(value_assign_non_const_array_to_small_val) {
    cnttype source[3]{};
    cnttype::reset();
    std::any target{std::in_place_type<cnttype>};
    auto& result = (target = source);
    expect(&result == &target);
    expect(target.has_value());
    expect(target.type() == typeid(cnttype*));
    expect(any_cast<cnttype*>(target) == source);
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
}

TEST(value_assign_const_array_to_small_val) {
    const cnttype source[3]{};
    cnttype::reset();
    std::any target{std::in_place_type<cnttype>};
    auto& result = (target = source);
    expect(&result == &target);
    expect(target.has_value());
    expect(target.type() == typeid(const cnttype*));
    expect(any_cast<const cnttype*>(target) == source);
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
}

TEST(value_assign_function_to_small_val) {
    cnttype::reset();
    std::any target{std::in_place_type<cnttype>};
    auto& result = (target = func);
    expect(&result == &target);
    expect(target.has_value());
    expect(target.type() == typeid(int (*)(int, int)));
    expect(any_cast<int (*)(int, int)>(target) == &func);
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
}

TEST(value_assign_exception_copy_to_small_val) {
    throwing_ctor source{};
    cnttype::reset();
    std::any target{std::in_place_type<cnttype>, 7};
    try {
        target = source;
        compiler_forget(target);
        fail();
    } catch (const throwing_ctor::copy_exc&) {
    }
    expect(target.has_value());
    expect(any_cast<cnttype>(&target)->val == 7);
    expect(target.type() == typeid(cnttype));
}

TEST(value_assign_exception_move_to_small_val) {
    throwing_ctor source{};
    cnttype::reset();
    std::any target{std::in_place_type<cnttype>, 7};
    try {
        target = std::move(source);
        compiler_forget(target);
        fail();
    } catch (const throwing_ctor::move_exc&) {
    }
    expect(target.has_value());
    expect(any_cast<cnttype>(&target)->val == 7);
    expect(target.type() == typeid(cnttype));
}

TEST(value_assign_lvalue_to_large_val) {
    cnttype source{7};
    cnttype::reset();
    std::any target{std::in_place_type<large_cnttype>};
    auto& result = (target = source);
    expect(&result == &target);
    expect(target.has_value());
    expect(any_cast<cnttype>(&target)->val == 7);
    expect(target.type() == typeid(cnttype));
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 1);
    expect(cnttype::move_ctor_count == 0);
}

TEST(value_assign_rvalue_move_to_large_val) {
    cnttype source{7};
    cnttype::reset();
    std::any target{std::in_place_type<large_cnttype>, 17};
    auto& result = (target = std::move(source));
    expect(&result == &target);
    expect(target.has_value());
    expect(any_cast<cnttype>(&target)->val == 7);
    expect(target.type() == typeid(cnttype));
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 1);
}

TEST(value_assign_rvalue_temporary_to_large_val) {
    std::any target{std::in_place_type<large_cnttype>, 17};
    cnttype::reset();
    auto& result = (target = cnttype{7});
    expect(&result == &target);
    expect(target.has_value());
    expect(any_cast<cnttype>(&target)->val == 7);
    expect(target.type() == typeid(cnttype));
    expect(cnttype::dtor_count == 2);  // one for the temporary variable
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 1);
}

TEST(value_assign_non_const_array_to_large_val) {
    cnttype source[3]{};
    cnttype::reset();
    std::any target{std::in_place_type<large_cnttype>};
    auto& result = (target = source);
    expect(&result == &target);
    expect(target.has_value());
    expect(target.type() == typeid(cnttype*));
    expect(any_cast<cnttype*>(target) == source);
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
}

TEST(value_assign_const_array_to_large_val) {
    const cnttype source[3]{};
    cnttype::reset();
    std::any target{std::in_place_type<large_cnttype>};
    auto& result = (target = source);
    expect(&result == &target);
    expect(target.has_value());
    expect(target.type() == typeid(const cnttype*));
    expect(any_cast<const cnttype*>(target) == source);
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
}

TEST(value_assign_function_to_large_val) {
    cnttype::reset();
    std::any target{std::in_place_type<large_cnttype>};
    auto& result = (target = func);
    expect(&result == &target);
    expect(target.has_value());
    expect(target.type() == typeid(int (*)(int, int)));
    expect(any_cast<int (*)(int, int)>(target) == &func);
    expect(cnttype::dtor_count == 1);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
}

TEST(value_assign_exception_copy_to_large_val) {
    throwing_ctor source{};
    cnttype::reset();
    std::any target{std::in_place_type<large_cnttype>, 7};
    try {
        target = source;
        compiler_forget(target);
        fail();
    } catch (const throwing_ctor::copy_exc&) {
    }
    expect(target.has_value());
    expect(any_cast<large_cnttype>(&target)->nested.val == 7);
    expect(target.type() == typeid(large_cnttype));
}

TEST(value_assign_exception_move_to_large_val) {
    throwing_ctor source{};
    cnttype::reset();
    std::any target{std::in_place_type<large_cnttype>, 7};
    try {
        target = std::move(source);
        compiler_forget(target);
        fail();
    } catch (const throwing_ctor::move_exc&) {
    }
    expect(target.has_value());
    expect(any_cast<large_cnttype>(&target)->nested.val == 7);
    expect(target.type() == typeid(large_cnttype));
}
