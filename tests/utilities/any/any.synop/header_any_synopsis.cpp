#include <any>

#include "testing.h"

struct type_from_init_list {
    type_from_init_list(std::initializer_list<int>, int, int) {}
};

TEST() {
    [[maybe_unused]] std::bad_any_cast err;
    std::any a;
    std::any b;
    std::swap(a, b);
    swap(a, b);
    a = std::make_any<int>(3);
    b = std::make_any<type_from_init_list>({1, 2, 3}, 4, 5);
    [[maybe_unused]] int a_value = any_cast<int>(a);
    [[maybe_unused]] int* a_value_ptr = any_cast<int>(&a);
    const std::any c = a;
    [[maybe_unused]] int c_value = any_cast<int>(c);
    [[maybe_unused]] const int* c_value_ptr = any_cast<int>(&c);
}
