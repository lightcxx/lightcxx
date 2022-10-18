#include <any>

#include "counted_type.h"
#include "testing.h"

TEST(any_cast_const_ptr_no_value) {
    const std::any a;
    ASSERT_NOEXCEPT(any_cast<int>(&a));
    ASSERT_TYPE(const int*, any_cast<int>(&a));
    ASSERT_TYPE(const int*, any_cast<const int>(&a));
    ASSERT(any_cast<int>(&a) == nullptr);
    ASSERT(any_cast<const int>(&a) == nullptr);
}

TEST(any_cast_const_ptr_with_incorrect_value) {
    const std::any a(7.0);
    ASSERT(any_cast<const int>(&a) == nullptr);
}

TEST(any_cast_const_ptr_with_correct_value) {
    const std::any a(7);
    ASSERT(any_cast<const int>(&a) != nullptr);
    ASSERT(*any_cast<const int>(&a) == 7);
}

TEST(any_cast_nonconst_ptr_no_value) {
    std::any a;
    ASSERT_NOEXCEPT(any_cast<int>(&a));
    ASSERT_TYPE(int*, any_cast<int>(&a));
    ASSERT_TYPE(const int*, any_cast<const int>(&a));
    ASSERT(any_cast<int>(&a) == nullptr);
}

TEST(any_cast_nonconst_ptr_with_incorrect_value) {
    std::any a(7.0);
    ASSERT(any_cast<int>(&a) == nullptr);
    ASSERT(any_cast<const int>(&a) == nullptr);
}

TEST(any_cast_nonconst_ptr_with_correct_value) {
    std::any a(7);
    ASSERT(any_cast<int>(&a) != nullptr);
    ASSERT(*any_cast<int>(&a) == 7);
    ASSERT(any_cast<const int>(&a) != nullptr);
    ASSERT(*any_cast<const int>(&a) == 7);
}

TEST(any_cast_const_ref_no_value) {
    const std::any a;
    ASSERT_TYPE(int, any_cast<int>(a));
    ASSERT_TYPE(int, any_cast<const int>(a));
    ASSERT_TYPE(const int&, any_cast<const int&>(a));
    ASSERT_TYPE(const volatile int&, any_cast<const volatile int&>(a));
    try {
        auto result = any_cast<int>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const int>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<volatile int>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const volatile int>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const int&>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const volatile int&>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
}

TEST(any_cast_const_ref_invalid_value) {
    const std::any a(1.0);
    try {
        auto result = any_cast<int>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const int>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<volatile int>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const volatile int>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const int&>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const volatile int&>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
}

TEST(any_cast_const_ref_valid_value) {
    const std::any a(7);
    ASSERT(any_cast<int>(a) == 7);
    ASSERT(any_cast<const int>(a) == 7);
    ASSERT(any_cast<volatile int>(a) == 7);
    ASSERT(any_cast<const volatile int>(a) == 7);
    ASSERT(any_cast<const int&>(a) == 7);
    ASSERT(any_cast<const volatile int&>(a) == 7);
}

TEST(any_cast_nonconst_ref_no_value) {
    std::any a;
    ASSERT_TYPE(int, any_cast<int>(a));
    ASSERT_TYPE(int, any_cast<const int>(a));
    ASSERT_TYPE(int, any_cast<volatile int>(a));
    ASSERT_TYPE(int, any_cast<const volatile int>(a));
    ASSERT_TYPE(int&, any_cast<int&>(a));
    ASSERT_TYPE(const int&, any_cast<const int&>(a));
    ASSERT_TYPE(volatile int&, any_cast<volatile int&>(a));
    ASSERT_TYPE(const volatile int&, any_cast<const volatile int&>(a));
    try {
        auto result = any_cast<int>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const int>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<volatile int>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const volatile int>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<int&>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const int&>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<volatile int&>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const volatile int&>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
}

TEST(any_cast_nonconst_ref_invalid_value) {
    std::any a(1.0);
    try {
        auto result = any_cast<int>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const int>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<volatile int>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const volatile int>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<int&>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const int&>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<volatile int&>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const volatile int&>(a);
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
}

TEST(any_cast_nonconst_ref_valid_value) {
    std::any a(std::in_place_type<cnttype>, 7);
    ASSERT(any_cast<cnttype>(a).val == 7);
    ASSERT(any_cast<const cnttype>(a).val == 7);
    ASSERT(any_cast<volatile cnttype>(a).val == 7);
    ASSERT(any_cast<const volatile cnttype>(a).val == 7);
    ASSERT(any_cast<cnttype&>(a).val == 7);
    ASSERT(any_cast<const cnttype&>(a).val == 7);
    ASSERT(any_cast<volatile cnttype&>(a).val == 7);
    ASSERT(any_cast<const volatile cnttype&>(a).val == 7);

    // Actually modify.
    cnttype::reset();
    any_cast<cnttype&>(a).val = 13;
    ASSERT(cnttype::default_ctor_count == 0);
    ASSERT(cnttype::value_ctor_count == 0);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 0);
    ASSERT(cnttype::copy_assign_count == 0);
    ASSERT(cnttype::move_assign_count == 0);
    ASSERT(cnttype::dtor_count == 0);

    ASSERT(any_cast<cnttype&>(a).val == 13);
    ASSERT(any_cast<const cnttype&>(a).val == 13);
    ASSERT(any_cast<volatile cnttype&>(a).val == 13);
    ASSERT(any_cast<const volatile cnttype&>(a).val == 13);
}

TEST(any_cast_rvalue_ref_no_value) {
    std::any a;
    ASSERT_TYPE(int, any_cast<int>(std::move(a)));
    ASSERT_TYPE(int, any_cast<const int>(std::move(a)));
    ASSERT_TYPE(int, any_cast<volatile int>(std::move(a)));
    ASSERT_TYPE(int, any_cast<const volatile int>(std::move(a)));
    ASSERT_TYPE(int&&, any_cast<int&&>(std::move(a)));
    ASSERT_TYPE(const int&&, any_cast<const int&&>(std::move(a)));
    ASSERT_TYPE(volatile int&&, any_cast<volatile int&&>(std::move(a)));
    ASSERT_TYPE(const volatile int&&, any_cast<const volatile int&&>(std::move(a)));
    try {
        auto result = any_cast<int>(std::move(a));
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const int>(std::move(a));
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<volatile int>(std::move(a));
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const volatile int>(std::move(a));
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<int&&>(std::move(a));
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const int&&>(std::move(a));
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<volatile int&&>(std::move(a));
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const volatile int&&>(std::move(a));
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
}

TEST(any_cast_rvalue_ref_invalid_value) {
    std::any a(1.0);
    try {
        auto result = any_cast<int>(std::move(a));
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const int>(std::move(a));
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<volatile int>(std::move(a));
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const volatile int>(std::move(a));
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<int&&>(std::move(a));
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const int&&>(std::move(a));
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<volatile int&&>(std::move(a));
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
    try {
        auto result = any_cast<const volatile int&&>(std::move(a));
        compiler_forget(result);
        FAIL();
    } catch (const std::bad_any_cast&) {}
}

TEST(any_cast_rvalue_ref_valid_value) {
    std::any a(std::in_place_type<cnttype>, 7);
    ASSERT(any_cast<cnttype>(std::move(a)).val == 7);
    ASSERT(any_cast<const cnttype>(std::move(a)).val == 7);
    ASSERT(any_cast<volatile cnttype>(std::move(a)).val == 7);
    ASSERT(any_cast<const volatile cnttype>(std::move(a)).val == 7);
    ASSERT(any_cast<cnttype&&>(std::move(a)).val == 7);
    ASSERT(any_cast<const cnttype&&>(std::move(a)).val == 7);
    ASSERT(any_cast<volatile cnttype&&>(std::move(a)).val == 7);
    ASSERT(any_cast<const volatile cnttype&&>(std::move(a)).val == 7);

    // Actually take the rvalue
    cnttype::reset();
    auto take_1 = any_cast<cnttype&&>(std::move(a));
    compiler_forget(take_1);
    auto take_2 = any_cast<cnttype>(std::move(a));
    compiler_forget(take_2);
    ASSERT(cnttype::default_ctor_count == 0);
    ASSERT(cnttype::value_ctor_count == 0);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::move_ctor_count == 2);
    ASSERT(cnttype::copy_assign_count == 0);
    ASSERT(cnttype::move_assign_count == 0);
    ASSERT(cnttype::dtor_count == 0);
}
