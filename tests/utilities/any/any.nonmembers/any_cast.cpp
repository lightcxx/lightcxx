#include <any>

#include "counted_type.h"
#include "testing.h"

TEST(any_cast_const_ptr_no_value) {
    const std::any a;
    expect_is_noexcept(any_cast<int>(&a));
    expect_type(const int*, any_cast<int>(&a));
    expect_type(const int*, any_cast<const int>(&a));
    expect(any_cast<int>(&a) == nullptr);
    expect(any_cast<const int>(&a) == nullptr);
}

TEST(any_cast_const_ptr_with_incorrect_value) {
    const std::any a(7.0);
    expect(any_cast<const int>(&a) == nullptr);
}

TEST(any_cast_const_ptr_with_correct_value) {
    const std::any a(7);
    expect(any_cast<const int>(&a) != nullptr);
    expect(*any_cast<const int>(&a) == 7);
}

TEST(any_cast_nonconst_ptr_no_value) {
    std::any a;
    expect_is_noexcept(any_cast<int>(&a));
    expect_type(int*, any_cast<int>(&a));
    expect_type(const int*, any_cast<const int>(&a));
    expect(any_cast<int>(&a) == nullptr);
}

TEST(any_cast_nonconst_ptr_with_incorrect_value) {
    std::any a(7.0);
    expect(any_cast<int>(&a) == nullptr);
    expect(any_cast<const int>(&a) == nullptr);
}

TEST(any_cast_nonconst_ptr_with_correct_value) {
    std::any a(7);
    expect(any_cast<int>(&a) != nullptr);
    expect(*any_cast<int>(&a) == 7);
    expect(any_cast<const int>(&a) != nullptr);
    expect(*any_cast<const int>(&a) == 7);
}

TEST(any_cast_const_ref_no_value) {
    const std::any a;
    expect_type(int, any_cast<int>(a));
    expect_type(int, any_cast<const int>(a));
    expect_type(const int&, any_cast<const int&>(a));
    expect_type(const volatile int&, any_cast<const volatile int&>(a));
    try {
        any_cast<int>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const int>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<volatile int>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const volatile int>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const int&>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const volatile int&>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
}

TEST(any_cast_const_ref_invalid_value) {
    const std::any a(1.0);
    try {
        any_cast<int>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const int>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<volatile int>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const volatile int>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const int&>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const volatile int&>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
}

TEST(any_cast_const_ref_valid_value) {
    const std::any a(7);
    expect(any_cast<int>(a) == 7);
    expect(any_cast<const int>(a) == 7);
    expect(any_cast<volatile int>(a) == 7);
    expect(any_cast<const volatile int>(a) == 7);
    expect(any_cast<const int&>(a) == 7);
    expect(any_cast<const volatile int&>(a) == 7);
}

TEST(any_cast_nonconst_ref_no_value) {
    std::any a;
    expect_type(int, any_cast<int>(a));
    expect_type(int, any_cast<const int>(a));
    expect_type(int, any_cast<volatile int>(a));
    expect_type(int, any_cast<const volatile int>(a));
    expect_type(int&, any_cast<int&>(a));
    expect_type(const int&, any_cast<const int&>(a));
    expect_type(volatile int&, any_cast<volatile int&>(a));
    expect_type(const volatile int&, any_cast<const volatile int&>(a));
    try {
        any_cast<int>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const int>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<volatile int>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const volatile int>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<int&>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const int&>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<volatile int&>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const volatile int&>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
}

TEST(any_cast_nonconst_ref_invalid_value) {
    std::any a(1.0);
    try {
        any_cast<int>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const int>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<volatile int>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const volatile int>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<int&>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const int&>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<volatile int&>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const volatile int&>(a);
        fail();
    } catch (const std::bad_any_cast&) {}
}

TEST(any_cast_nonconst_ref_valid_value) {
    std::any a(std::in_place_type<cnttype>, 7);
    expect(any_cast<cnttype>(a).val == 7);
    expect(any_cast<const cnttype>(a).val == 7);
    expect(any_cast<volatile cnttype>(a).val == 7);
    expect(any_cast<const volatile cnttype>(a).val == 7);
    expect(any_cast<cnttype&>(a).val == 7);
    expect(any_cast<const cnttype&>(a).val == 7);
    expect(any_cast<volatile cnttype&>(a).val == 7);
    expect(any_cast<const volatile cnttype&>(a).val == 7);

    // Actually modify.
    cnttype::reset();
    any_cast<cnttype&>(a).val = 13;
    expect(cnttype::default_ctor_count == 0);
    expect(cnttype::value_ctor_count == 0);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 0);
    expect(cnttype::copy_assign_count == 0);
    expect(cnttype::move_assign_count == 0);
    expect(cnttype::dtor_count == 0);

    expect(any_cast<cnttype&>(a).val == 13);
    expect(any_cast<const cnttype&>(a).val == 13);
    expect(any_cast<volatile cnttype&>(a).val == 13);
    expect(any_cast<const volatile cnttype&>(a).val == 13);
}

TEST(any_cast_rvalue_ref_no_value) {
    std::any a;
    expect_type(int, any_cast<int>(std::move(a)));
    expect_type(int, any_cast<const int>(std::move(a)));
    expect_type(int, any_cast<volatile int>(std::move(a)));
    expect_type(int, any_cast<const volatile int>(std::move(a)));
    expect_type(int&&, any_cast<int&&>(std::move(a)));
    expect_type(const int&&, any_cast<const int&&>(std::move(a)));
    expect_type(volatile int&&, any_cast<volatile int&&>(std::move(a)));
    expect_type(const volatile int&&, any_cast<const volatile int&&>(std::move(a)));
    try {
        any_cast<int>(std::move(a));
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const int>(std::move(a));
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<volatile int>(std::move(a));
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const volatile int>(std::move(a));
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<int&&>(std::move(a));
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const int&&>(std::move(a));
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<volatile int&&>(std::move(a));
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const volatile int&&>(std::move(a));
        fail();
    } catch (const std::bad_any_cast&) {}
}

TEST(any_cast_rvalue_ref_invalid_value) {
    std::any a(1.0);
    try {
        any_cast<int>(std::move(a));
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const int>(std::move(a));
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<volatile int>(std::move(a));
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const volatile int>(std::move(a));
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<int&&>(std::move(a));
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const int&&>(std::move(a));
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<volatile int&&>(std::move(a));
        fail();
    } catch (const std::bad_any_cast&) {}
    try {
        any_cast<const volatile int&&>(std::move(a));
        fail();
    } catch (const std::bad_any_cast&) {}
}

TEST(any_cast_rvalue_ref_valid_value) {
    std::any a(std::in_place_type<cnttype>, 7);
    expect(any_cast<cnttype>(std::move(a)).val == 7);
    expect(any_cast<const cnttype>(std::move(a)).val == 7);
    expect(any_cast<volatile cnttype>(std::move(a)).val == 7);
    expect(any_cast<const volatile cnttype>(std::move(a)).val == 7);
    expect(any_cast<cnttype&&>(std::move(a)).val == 7);
    expect(any_cast<const cnttype&&>(std::move(a)).val == 7);
    expect(any_cast<volatile cnttype&&>(std::move(a)).val == 7);
    expect(any_cast<const volatile cnttype&&>(std::move(a)).val == 7);

    // Actually take the rvalue
    cnttype::reset();
    auto take_1 = any_cast<cnttype&&>(std::move(a));
    compiler_forget(take_1);
    auto take_2 = any_cast<cnttype>(std::move(a));
    compiler_forget(take_2);
    expect(cnttype::default_ctor_count == 0);
    expect(cnttype::value_ctor_count == 0);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::move_ctor_count == 2);
    expect(cnttype::copy_assign_count == 0);
    expect(cnttype::move_assign_count == 0);
    expect(cnttype::dtor_count == 0);
}
