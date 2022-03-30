#include <utility>

#include "testing.h"

struct Struct {
    int i;

    bool operator==(const Struct&) const = default;
    bool operator==(const volatile Struct& other) const volatile {
        return i == other.i;
    }
};

template<class T>
void test_as_const(T& t) {
    static_assert(std::is_const_v<std::remove_reference_t<decltype(std::as_const(t))>>);
    expect(std::as_const(t) == t);

    static_assert(std::is_const_v<std::remove_reference_t<decltype(std::as_const<T>(t))>>);
    expect(std::as_const<T>(t) == t);

    static_assert(std::is_const_v<std::remove_reference_t<decltype(std::as_const<const T>(t))>>);
    expect(std::as_const<const T>(t) == t);

    static_assert(std::is_const_v<std::remove_reference_t<decltype(std::as_const<volatile T>(t))>>);
    expect(std::as_const<volatile T>(t) == t);

    static_assert(std::is_const_v<std::remove_reference_t<decltype(std::as_const<const volatile T>(t))>>);
    expect(std::as_const<const volatile T>(t) == t);
}

TEST() {
    int i = 3;
    double d = 4.0;
    Struct s{2};
    test_as_const(i);
    test_as_const(d);
    test_as_const(s);
}
