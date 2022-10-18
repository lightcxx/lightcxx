#include <any>

#include "counted_type.h"
#include "testing.h"

struct large_cnttype {
    struct exc {};

    Testing::cnttype nested;
    [[maybe_unused]] char padding[4096];  // Clearly not SBO-friendly type.

    large_cnttype() = default;
    large_cnttype(int source)
            : nested(source) {}
    large_cnttype(std::initializer_list<int>)
            : nested(-777) {}
    large_cnttype(std::initializer_list<int>, int, int)
            : nested(-777) {
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

TEST(emplace_to_no_val) {
    cnttype::reset();
    std::any target;
    auto& result = target.emplace<cnttype>(7);
    ASSERT_TYPE(cnttype&, result);
    ASSERT(result.val == 7);
    ASSERT(target.has_value());
    ASSERT(any_cast<cnttype>(&target)->val == 7);
    ASSERT(target.type() == typeid(cnttype));
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_initlist_to_no_val) {
    cnttype::reset();
    std::any target;
    auto& result = target.emplace<large_cnttype>({1, 2, 3});
    ASSERT_TYPE(large_cnttype&, result);
    ASSERT(result.nested.val == -777);
    ASSERT(target.has_value());
    ASSERT(any_cast<large_cnttype>(&target)->nested.val == -777);
    ASSERT(target.type() == typeid(large_cnttype));
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_non_const_array_to_no_val) {
    cnttype source[3]{};
    cnttype::reset();
    std::any target;
    auto& result = (target.emplace<cnttype[3]>(source));
    ASSERT(result == source);
    ASSERT(target.has_value());
    ASSERT(target.type() == typeid(cnttype*));
    ASSERT(any_cast<cnttype*>(target) == source);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_const_array_to_no_val) {
    const cnttype source[3]{};
    cnttype::reset();
    std::any target;
    auto& result = (target.emplace<const cnttype[3]>(source));
    ASSERT(result == source);
    ASSERT(target.has_value());
    ASSERT(target.type() == typeid(const cnttype*));
    ASSERT(any_cast<const cnttype*>(target) == source);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_function_to_no_val) {
    std::any target;
    auto& result = (target.emplace<int(int, int)>(func));
    ASSERT(result == func);
    ASSERT(target.has_value());
    ASSERT(target.type() == typeid(int (*)(int, int)));
    ASSERT(any_cast<int (*)(int, int)>(target) == &func);
}

TEST(emplace_exception_copy_to_no_val) {
    throwing_ctor source{};
    std::any target;
    try {
        target.emplace<throwing_ctor>(source);
        FAIL();
    } catch (const throwing_ctor::copy_exc&) {
    }
    ASSERT(!target.has_value());
}

TEST(emplace_exception_move_to_no_val) {
    throwing_ctor source{};
    std::any target;
    try {
        target.emplace<throwing_ctor>(std::move(source));
        FAIL();
    } catch (const throwing_ctor::move_exc&) {
    }
    ASSERT(!target.has_value());
}

TEST(emplace_initlist_exception_to_no_val) {
    std::any target;
    try {
        target.emplace<large_cnttype>({1, 2, 3}, 1, 2);
        FAIL();
    } catch (const large_cnttype::exc&) {
    }
    ASSERT(!target.has_value());
}

TEST(emplace_to_small_val) {
    std::any target{std::in_place_type<cnttype>};
    cnttype::reset();
    auto& result = target.emplace<cnttype>(7);
    ASSERT_TYPE(cnttype&, result);
    ASSERT(result.val == 7);
    ASSERT(target.has_value());
    ASSERT(any_cast<cnttype>(&target)->val == 7);
    ASSERT(target.type() == typeid(cnttype));
    ASSERT(cnttype::dtor_count == 1);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_initlist_to_small_val) {
    std::any target{std::in_place_type<cnttype>};
    cnttype::reset();
    auto& result = target.emplace<large_cnttype>({1, 2, 3});
    ASSERT_TYPE(large_cnttype&, result);
    ASSERT(result.nested.val == -777);
    ASSERT(target.has_value());
    ASSERT(any_cast<large_cnttype>(&target)->nested.val == -777);
    ASSERT(target.type() == typeid(large_cnttype));
    ASSERT(cnttype::dtor_count == 1);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_non_const_array_to_small_val) {
    cnttype source[3]{};
    std::any target{std::in_place_type<cnttype>};
    cnttype::reset();
    auto& result = (target.emplace<cnttype[3]>(source));
    ASSERT_TYPE(cnttype*&, result);
    ASSERT(result == source);
    ASSERT(target.has_value());
    ASSERT(target.type() == typeid(cnttype*));
    ASSERT(any_cast<cnttype*>(target) == source);
    ASSERT(cnttype::dtor_count == 1);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_const_array_to_small_val) {
    const cnttype source[3]{};
    std::any target{std::in_place_type<cnttype>};
    cnttype::reset();
    auto& result = target.emplace<const cnttype[3]>(source);
    ASSERT_TYPE(const cnttype*&, result);
    ASSERT(result == source);
    ASSERT(target.has_value());
    ASSERT(target.type() == typeid(const cnttype*));
    ASSERT(any_cast<const cnttype*>(target) == source);
    ASSERT(cnttype::dtor_count == 1);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_function_to_small_val) {
    std::any target{std::in_place_type<cnttype>};
    cnttype::reset();
    auto& result = target.emplace<int(int, int)>(func);
    ASSERT(result == func);
    ASSERT(target.has_value());
    ASSERT(target.type() == typeid(int (*)(int, int)));
    ASSERT(any_cast<int (*)(int, int)>(target) == &func);
    ASSERT(cnttype::dtor_count == 1);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_exception_copy_to_small_val) {
    throwing_ctor source{};
    cnttype::reset();
    std::any target{std::in_place_type<cnttype>};
    try {
        target.emplace<throwing_ctor>(source);
        compiler_forget(target);
        FAIL();
    } catch (const throwing_ctor::copy_exc&) {
    }
    ASSERT(!target.has_value());
    ASSERT(cnttype::dtor_count == 1);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_exception_move_to_small_val) {
    throwing_ctor source{};
    cnttype::reset();
    std::any target{std::in_place_type<cnttype>};
    try {
        target.emplace<throwing_ctor>(std::move(source));
        compiler_forget(target);
        FAIL();
    } catch (const throwing_ctor::move_exc&) {
    }
    ASSERT(!target.has_value());
    ASSERT(cnttype::dtor_count == 1);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_initlist_exception_to_small_val) {
    std::any target{std::in_place_type<cnttype>};
    cnttype::reset();
    try {
        target.emplace<large_cnttype>({1, 2, 3}, 1, 2);
        compiler_forget(target);
        FAIL();
    } catch (const large_cnttype::exc&) {
    }
    ASSERT(!target.has_value());
    // the throw is inside the body, after full construction finished for the
    // cnttype nested field of large_cnttype, so ~cnttype() gets called in the constructor of large_cnttype
    ASSERT(cnttype::dtor_count == 2);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_to_large_val) {
    std::any target{std::in_place_type<large_cnttype>};
    cnttype::reset();
    auto& result = target.emplace<cnttype>(7);
    ASSERT_TYPE(cnttype&, result);
    ASSERT(result.val == 7);
    ASSERT(target.has_value());
    ASSERT(any_cast<cnttype>(&target)->val == 7);
    ASSERT(target.type() == typeid(cnttype));
    ASSERT(cnttype::dtor_count == 1);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_initlist_to_large_val) {
    std::any target{std::in_place_type<large_cnttype>};
    cnttype::reset();
    auto& result = target.emplace<large_cnttype>({1, 2, 3});
    ASSERT_TYPE(large_cnttype&, result);
    ASSERT(result.nested.val == -777);
    ASSERT(target.has_value());
    ASSERT(any_cast<large_cnttype>(&target)->nested.val == -777);
    ASSERT(target.type() == typeid(large_cnttype));
    ASSERT(cnttype::dtor_count == 1);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_non_const_array_to_large_val) {
    cnttype source[3]{};
    std::any target{std::in_place_type<large_cnttype>};
    cnttype::reset();
    auto& result = (target.emplace<cnttype[3]>(source));
    ASSERT_TYPE(cnttype*&, result);
    ASSERT(result == source);
    ASSERT(target.has_value());
    ASSERT(target.type() == typeid(cnttype*));
    ASSERT(any_cast<cnttype*>(target) == source);
    ASSERT(cnttype::dtor_count == 1);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_const_array_to_large_val) {
    const cnttype source[3]{};
    std::any target{std::in_place_type<large_cnttype>};
    cnttype::reset();
    auto& result = target.emplace<const cnttype[3]>(source);
    ASSERT_TYPE(const cnttype*&, result);
    ASSERT(result == source);
    ASSERT(target.has_value());
    ASSERT(target.type() == typeid(const cnttype*));
    ASSERT(any_cast<const cnttype*>(target) == source);
    ASSERT(cnttype::dtor_count == 1);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_function_to_large_val) {
    std::any target{std::in_place_type<large_cnttype>};
    cnttype::reset();
    auto& result = target.emplace<int(int, int)>(func);
    ASSERT(result == func);
    ASSERT(target.has_value());
    ASSERT(target.type() == typeid(int (*)(int, int)));
    ASSERT(any_cast<int (*)(int, int)>(target) == &func);
    ASSERT(cnttype::dtor_count == 1);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_exception_copy_to_large_val) {
    throwing_ctor source{};
    cnttype::reset();
    std::any target{std::in_place_type<large_cnttype>};
    try {
        target.emplace<throwing_ctor>(source);
        compiler_forget(target);
        FAIL();
    } catch (const throwing_ctor::copy_exc&) {
    }
    ASSERT(!target.has_value());
    ASSERT(cnttype::dtor_count == 1);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_exception_move_to_large_val) {
    throwing_ctor source{};
    cnttype::reset();
    std::any target{std::in_place_type<large_cnttype>};
    try {
        target.emplace<throwing_ctor>(std::move(source));
        compiler_forget(target);
        FAIL();
    } catch (const throwing_ctor::move_exc&) {
    }
    ASSERT(!target.has_value());
    ASSERT(cnttype::dtor_count == 1);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}

TEST(emplace_initlist_exception_to_large_val) {
    cnttype::reset();
    std::any target{std::in_place_type<large_cnttype>};
    try {
        target.emplace<large_cnttype>({1, 2, 3}, 1, 2);
        compiler_forget(target);
        FAIL();
    } catch (const large_cnttype::exc&) {
    }
    ASSERT(!target.has_value());
    // the throw is inside the body, after full construction finished for the
    // cnttype nested field of large_cnttype, so ~cnttype() gets called in the constructor of large_cnttype
    ASSERT(cnttype::dtor_count == 2);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
}
