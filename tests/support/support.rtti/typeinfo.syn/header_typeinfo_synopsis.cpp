#include <typeinfo>

#include "testing.h"

TEST() {
    expect_type(const std::type_info&, typeid(int));

    std::bad_cast bad_c;
    std::bad_typeid bad_tp;
}
