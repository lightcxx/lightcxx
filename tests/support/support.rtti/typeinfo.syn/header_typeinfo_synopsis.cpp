#include <typeinfo>

#include "testing.h"

TEST() {
    ASSERT_TYPE(const std::type_info&, typeid(int));

    std::bad_cast bad_c;
    std::bad_typeid bad_tp;
}
