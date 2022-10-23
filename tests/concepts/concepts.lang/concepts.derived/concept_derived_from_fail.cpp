// EXPECT:NO_COMPILE 4

#include <concepts>

#include "testing.h"

struct Base {
    constexpr int f() {
        return 14;
    }
};

struct PrivateDerived : private Base {
    constexpr int f() {
        return 17;
    }
};

template<std::derived_from<Base> T>
constexpr int call_f(T&& obj) {
    return obj.f();
}

struct BaseVirtual {
    virtual ~BaseVirtual() {}
    virtual int f() = 0;
};

struct PrivateDerivedVirtual : private BaseVirtual {
    ~PrivateDerivedVirtual() override {}
    int f() override {
        return 19;
    }
};

template<std::derived_from<BaseVirtual> T>
int call_f_2(T* obj) {
    return obj->f();
}

TEST() {
#if NEGATIVE_COMPILE_ITERATION == 0
    int i = 7;
    expect(call_f(i) == 14);
#elif NEGATIVE_COMPILE_ITERATION == 1
    PrivateDerived x;
    expect(call_f(x) == 17);
#elif NEGATIVE_COMPILE_ITERATION == 2
    int j = 7;
    expect(call_f_2(&j) == 19);
#elif NEGATIVE_COMPILE_ITERATION == 3
    PrivateDerivedVirtual obj;
    expect(call_f_2(&obj) == 19);
#endif
}
