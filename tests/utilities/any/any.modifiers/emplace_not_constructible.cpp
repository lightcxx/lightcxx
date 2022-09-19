// EXPECT:NO_COMPILE "is_constructible_v"

#include <any>

#include "testing.h"

struct A {
    A() = default;
};

TEST() {
    std::any a;
    a.emplace<A>(1, 2, 3);
}
