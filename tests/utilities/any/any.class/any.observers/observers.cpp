#include <any>

#include "testing.h"

TEST(observers_noexcept) {
    const std::any a;
    ASSERT_NOEXCEPT(a.has_value());
    ASSERT_NOEXCEPT(a.type());
}

TEST(observers_empty) {
    const std::any a;
    ASSERT(!a.has_value());
    ASSERT(a.type() == typeid(void));
}

TEST(observers_nonempty) {
    const std::any a(3);
    ASSERT(a.has_value());
    ASSERT(a.type() == typeid(int));
}
