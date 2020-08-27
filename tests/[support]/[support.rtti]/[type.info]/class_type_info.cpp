#include <typeinfo>

#include "testing.h"
#include <string.h>

struct Type {
    [[maybe_unused]] int x;
};

TEST() {
    expect_type<const std::type_info&>(typeid(int));

    expect(typeid(int) == typeid(int));
    expect(typeid(volatile int) == typeid(const int));
    expect(typeid(Type) == typeid(Type));
    const auto x = Type();
    expect_type<const Type&>(x);
    expect(typeid(Type) == typeid(x));

    expect(!(typeid(int) == typeid(Type)));
    expect(typeid(int).hash_code() != typeid(Type).hash_code());
    expect(typeid(int).name() != typeid(Type).name());
    expect(strcmp(typeid(int).name(), typeid(Type).name()) != 0);
    expect(typeid(int).before(typeid(Type)) || typeid(Type).before(typeid(int)));

    expect_type<size_t&&>(typeid(int).hash_code());
    expect_type<const char*&&>(typeid(int).name());
    expect_type<bool&&>(typeid(int).before(typeid(Type)));
}
