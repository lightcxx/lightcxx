#include <typeinfo>

#include <string.h>

#include "testing.h"

TEST() {
    std::bad_typeid default_constructed;
    ASSERT(::strcmp(default_constructed.what(), "bad_typeid") == 0);

    std::bad_typeid copy_constructed{default_constructed};
    ASSERT(default_constructed.what() == copy_constructed.what());

    std::bad_typeid copy_assigned;
    copy_assigned = default_constructed;
    ASSERT(default_constructed.what() == copy_assigned.what());

    std::bad_typeid move_constructed{static_cast<std::bad_typeid&&>(copy_constructed)};
    ASSERT(default_constructed.what() == move_constructed.what());

    std::bad_typeid move_assigned;
    move_assigned = static_cast<std::bad_typeid&&>(copy_assigned);
    ASSERT(default_constructed.what() == move_assigned.what());

    try {
        throw default_constructed;
    } catch (std::bad_typeid& thrown) {
        ASSERT(default_constructed.what() == thrown.what());
    } catch (...) {
        FAIL();
    }

    static_assert(std::is_polymorphic_v<std::bad_typeid>);

    static_assert(std::is_base_of_v<std::exception, std::bad_typeid>);
}
