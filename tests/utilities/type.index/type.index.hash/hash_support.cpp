#include <typeindex>

#include "testing.h"

TEST() {
    ASSERT_NOEXCEPT(std::hash<std::type_index>{});

    const std::hash<std::type_index> h{};
    ASSERT_NOEXCEPT(h(std::type_index(typeid(int))));
    ASSERT(h(std::type_index(typeid(void))) == std::type_index(typeid(void)).hash_code());
    ASSERT(h(std::type_index(typeid(int))) == std::type_index(typeid(int)).hash_code());
    ASSERT(h(typeid(int)) == std::type_index(typeid(int)).hash_code());
}
