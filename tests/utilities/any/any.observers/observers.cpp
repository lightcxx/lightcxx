#include <any>

#include "testing.h"

TEST(observers_noexcept) {
    const std::any a;
    expect_is_noexcept(a.has_value());
    expect_is_noexcept(a.type());
}

TEST(observers_empty) {
    const std::any a;
    expect(!a.has_value());
    expect(a.type() == typeid(void));
}

TEST(observers_nonempty) {
    const std::any a(3);
    expect(a.has_value());
    expect(a.type() == typeid(int));
}
