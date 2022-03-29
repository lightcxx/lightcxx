#include <type_traits>

#include "testing.h"

template<class T, class U>
constexpr void test_decay() {
    static_assert(std::is_same_v<typename std::decay<T>::type, U>);
    static_assert(std::is_same_v<std::decay_t<T>, U>);
}

TEST() {
    test_decay<void, void>();
    test_decay<int, int>();
    test_decay<const volatile int, int>();
    test_decay<int*, int*>();
    test_decay<int[3], int*>();
    test_decay<const int[3], const int*>();
    test_decay<void(), void (*)()>();
    test_decay<int(int) const, int(int) const>();
    test_decay<int(int) volatile, int(int) volatile>();
    test_decay<int(int)&, int(int)&>();
    test_decay<int(int)&&, int(int) &&>();
}
