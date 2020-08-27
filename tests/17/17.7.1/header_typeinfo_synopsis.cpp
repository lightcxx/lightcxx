#include <typeinfo>

#include "testing/test.h"

TEST() {
    expectType<const std::type_info&>(typeid(int));

    [[maybe_unused]] std::bad_cast bad_c;
    [[maybe_unused]] std::bad_typeid bad_tp;
}
