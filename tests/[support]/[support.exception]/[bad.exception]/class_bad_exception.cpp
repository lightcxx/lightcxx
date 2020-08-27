#include <typeinfo>

#include <string.h>

#include "testing.h"

TEST() {
    std::bad_exception default_constructed;
    expect(::strcmp(default_constructed.what(), "bad_exception") == 0);

    std::bad_exception copy_constructed{default_constructed};
    expect(default_constructed.what() == copy_constructed.what());

    std::bad_exception copy_assigned;
    copy_assigned = default_constructed;
    expect(default_constructed.what() == copy_assigned.what());

    std::bad_exception move_constructed{static_cast<std::bad_exception&&>(copy_constructed)};
    expect(default_constructed.what() == move_constructed.what());

    std::bad_exception move_assigned;
    move_assigned = static_cast<std::bad_exception&&>(copy_assigned);
    expect(default_constructed.what() == move_assigned.what());

    try {
        throw default_constructed;
    } catch (std::bad_exception& thrown) {
        expect(default_constructed.what() == thrown.what());
    } catch (...) { fail(); }

    static_assert(std::is_polymorphic_v<std::bad_exception>);

    static_assert(std::is_base_of_v<std::exception, std::bad_exception>);
}
