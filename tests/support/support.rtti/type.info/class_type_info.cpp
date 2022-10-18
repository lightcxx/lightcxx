#include <typeinfo>

#include "testing.h"
#include <string.h>

struct Type {
    int x;
};

TEST() {
    ASSERT_TYPE(const std::type_info&, typeid(int));

    ASSERT(typeid(int) == typeid(int));
    ASSERT(typeid(volatile int) == typeid(const int));
    ASSERT(typeid(Type) == typeid(Type));
    const auto x = Type();
    ASSERT_TYPE(const Type&, x);
    ASSERT(typeid(Type) == typeid(x));

    ASSERT(!(typeid(int) == typeid(Type)));
    ASSERT(typeid(int).hash_code() != typeid(Type).hash_code());
    ASSERT(typeid(int).name() != typeid(Type).name());
    ASSERT(strcmp(typeid(int).name(), typeid(Type).name()) != 0);
    ASSERT(typeid(int).before(typeid(Type)) || typeid(Type).before(typeid(int)));

    ASSERT_TYPE(size_t, typeid(int).hash_code());
    ASSERT_TYPE(const char*, typeid(int).name());
    ASSERT_TYPE(bool, typeid(int).before(typeid(Type)));
}
