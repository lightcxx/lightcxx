#include <typeinfo>

#include "testing/test.h"
#include <string.h>

struct Type {
    [[maybe_unused]] int x;
};

TEST() {
    expectType<const std::type_info&>(typeid(int));

    expect(typeid(int) == typeid(int), "equality");
    expect(typeid(volatile int) == typeid(const int), "equality for CV type");
    expect(typeid(Type) == typeid(Type), "equality for custom type");
    const auto x = Type();
    expectType<const Type&>(x);
    expect(typeid(Type) == typeid(x), "equality for type and instance");

    expect(!(typeid(int) == typeid(Type)), "inequality");
    expect(typeid(int).hash_code() != typeid(Type).hash_code(), "hash_code() inequality");
    expect(typeid(int).name() != typeid(Type).name(), "name() inequality");
    expect(strcmp(typeid(int).name(), typeid(Type).name()) != 0, "strcmp(name()) inequality");
    expect(typeid(int).before(typeid(Type)) || typeid(Type).before(typeid(int)),
           "Different type_info-s' relative order.");

    expectType<size_t&&>(typeid(int).hash_code());
    expectType<const char*&&>(typeid(int).name());
    expectType<bool&&>(typeid(int).before(typeid(Type)));
}
