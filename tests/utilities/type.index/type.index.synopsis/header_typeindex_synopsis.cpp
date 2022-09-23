#include <typeindex>

#include "testing.h"

TEST() {
    [[maybe_unused]] std::type_index index = typeid(int);
    [[maybe_unused]] std::hash<std::type_index> h{};
}
