#include <any>

#include "counted_type.h"
#include "testing.h"

TEST(swap_adl_noexcept) {
    std::any a, b;
    expect_is_noexcept(a.swap(b));
    swap(a, b);
}

TEST(swap_no_val_no_val) {
    std::any a;
    std::any b;
    std::swap(a, b);
    expect(!a.has_value());
    expect(!b.has_value());
}

TEST(swap_no_val_small_val) {
    std::any a;
    std::any b(cnttype{5});
    cnttype::reset();
    std::swap(a, b);
    expect(a.has_value());
    expect(a.type() == typeid(cnttype));
    expect(any_cast<cnttype>(&a)->val == 5);
    expect(!b.has_value());
    expect(cnttype::copy_assign_count == 0);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::dtor_count == 0);
}

TEST(swap_small_val_no_val) {
    std::any a;
    std::any b(cnttype{5});
    cnttype::reset();
    std::swap(b, a);
    expect(a.has_value());
    expect(a.type() == typeid(cnttype));
    expect(any_cast<cnttype>(&a)->val == 5);
    expect(!b.has_value());
    expect(cnttype::copy_assign_count == 0);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::dtor_count == 0);
}

TEST(swap_small_val_small_val) {
    std::any a(cnttype{7});
    std::any b(cnttype{5});
    cnttype::reset();
    std::swap(a, b);
    expect(a.has_value());
    expect(a.type() == typeid(cnttype));
    expect(any_cast<cnttype>(&a)->val == 5);
    expect(b.has_value());
    expect(b.type() == typeid(cnttype));
    expect(any_cast<cnttype>(&b)->val == 7);
    expect(cnttype::copy_assign_count == 0);
    expect(cnttype::copy_ctor_count == 0);
    expect(cnttype::dtor_count == 0);
}
