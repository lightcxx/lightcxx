// EXPECT:NO_COMPILE "is_copy_constructible_v"

#include <any>

#include "testing.h"

struct non_copy {
    non_copy() = default;
    non_copy(const non_copy&) = delete;
};

TEST() {
    std::any a(std::in_place_type<non_copy>);
}
