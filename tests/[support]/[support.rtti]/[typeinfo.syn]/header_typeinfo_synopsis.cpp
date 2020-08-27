#include <typeinfo>

#include "testing.h"

TEST() {
    expect_type<const std::type_info&>(typeid(int));

    [[maybe_unused]] std::bad_cast bad_c;
    [[maybe_unused]] std::bad_typeid bad_tp;
}
