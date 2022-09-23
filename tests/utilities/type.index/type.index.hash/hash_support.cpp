#include <typeindex>

#include "testing.h"

TEST() {
    expect_is_noexcept(std::hash<std::type_index>{});

    const std::hash<std::type_index> h{};
    expect_is_noexcept(h(std::type_index(typeid(int))));
    expect(h(std::type_index(typeid(void))) == std::type_index(typeid(void)).hash_code());
    expect(h(std::type_index(typeid(int))) == std::type_index(typeid(int)).hash_code());
    expect(h(typeid(int)) == std::type_index(typeid(int)).hash_code());
}
