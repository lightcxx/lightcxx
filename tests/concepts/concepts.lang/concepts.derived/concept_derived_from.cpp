#include <concepts>

#include "testing.h"

struct Base {
    constexpr int f() {
        return 14;
    }
};

template<std::derived_from<Base> T>
constexpr int call_f(T&& obj) {
    return obj.f();
}

static_assert(call_f(Base{}) == 14);

struct Derived : Base {
    constexpr int f() {
        return 17;
    }
};

struct PrivateDerived : private Base {
    constexpr int f() {
        return 17;
    }
};

static_assert(call_f(Derived{}) == 17);

struct BaseVirtual {
    virtual ~BaseVirtual() {}
    virtual int f() = 0;
};

template<std::derived_from<BaseVirtual> T>
int call_f_2(T* obj) {
    return obj->f();
}

struct DerivedVirtual : BaseVirtual {
    ~DerivedVirtual() override {}
    int f() override {
        return 19;
    }
};

struct PrivateDerivedVirtual : private BaseVirtual {
    ~PrivateDerivedVirtual() override {}
    int f() override {
        return 19;
    }
};

static_assert(std::derived_from<Base, Base>);
static_assert(std::derived_from<Base, const Base>);
static_assert(std::derived_from<const Base, const Base>);
static_assert(std::derived_from<const Base, const volatile Base>);
static_assert(std::derived_from<Derived, Base>);
static_assert(std::derived_from<Derived, const Base>);
static_assert(std::derived_from<const Derived, const Base>);
static_assert(std::derived_from<const Derived, const volatile Base>);
static_assert(!std::derived_from<PrivateDerived, Base>);
static_assert(!std::derived_from<PrivateDerived, const Base>);
static_assert(!std::derived_from<const PrivateDerived, const Base>);
static_assert(!std::derived_from<const PrivateDerived, const volatile Base>);


static_assert(std::derived_from<BaseVirtual, BaseVirtual>);
static_assert(std::derived_from<BaseVirtual, const BaseVirtual>);
static_assert(std::derived_from<const BaseVirtual, const BaseVirtual>);
static_assert(std::derived_from<const BaseVirtual, const volatile BaseVirtual>);
static_assert(std::derived_from<DerivedVirtual, BaseVirtual>);
static_assert(std::derived_from<DerivedVirtual, const BaseVirtual>);
static_assert(std::derived_from<const DerivedVirtual, const BaseVirtual>);
static_assert(std::derived_from<const DerivedVirtual, const volatile BaseVirtual>);
static_assert(!std::derived_from<PrivateDerivedVirtual, BaseVirtual>);
static_assert(!std::derived_from<PrivateDerivedVirtual, const BaseVirtual>);
static_assert(!std::derived_from<const PrivateDerivedVirtual, const BaseVirtual>);
static_assert(!std::derived_from<const PrivateDerivedVirtual, const volatile BaseVirtual>);

TEST() {
    DerivedVirtual obj;
    expect(call_f_2(&obj) == 19);
    BaseVirtual* ptr = &obj;
    expect(call_f_2(ptr) == 19);
}
