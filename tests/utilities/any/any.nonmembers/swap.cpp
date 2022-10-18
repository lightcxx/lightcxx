#include <any>

#include "counted_type.h"
#include "testing.h"

TEST(swap_adl_noexcept) {
    std::any a, b;
    ASSERT_NOEXCEPT(a.swap(b));
    swap(a, b);
}

TEST(swap_no_val_no_val) {
    std::any a;
    std::any b;
    std::swap(a, b);
    ASSERT(!a.has_value());
    ASSERT(!b.has_value());
}

TEST(swap_no_val_small_val) {
    std::any a;
    std::any b(cnttype{5});
    cnttype::reset();
    std::swap(a, b);
    ASSERT(a.has_value());
    ASSERT(a.type() == typeid(cnttype));
    ASSERT(any_cast<cnttype&>(a).val == 5);
    ASSERT(!b.has_value());
    ASSERT(cnttype::copy_assign_count == 0);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::dtor_count == 0);
}

TEST(swap_small_val_no_val) {
    std::any a;
    std::any b(cnttype{5});
    cnttype::reset();
    std::swap(b, a);
    ASSERT(a.has_value());
    ASSERT(a.type() == typeid(cnttype));
    ASSERT(any_cast<cnttype&>(a).val == 5);
    ASSERT(!b.has_value());
    ASSERT(cnttype::copy_assign_count == 0);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::dtor_count == 0);
}

TEST(swap_small_val_small_val) {
    std::any a(cnttype{7});
    std::any b(cnttype{5});
    cnttype::reset();
    std::swap(a, b);
    ASSERT(a.has_value());
    ASSERT(a.type() == typeid(cnttype));
    ASSERT(any_cast<cnttype&>(a).val == 5);
    ASSERT(b.has_value());
    ASSERT(b.type() == typeid(cnttype));
    ASSERT(any_cast<cnttype&>(b).val == 7);
    ASSERT(cnttype::copy_assign_count == 0);
    ASSERT(cnttype::copy_ctor_count == 0);
    ASSERT(cnttype::dtor_count == 0);
}

