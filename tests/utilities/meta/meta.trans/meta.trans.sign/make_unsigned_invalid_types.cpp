// EXPECT:NO_COMPILE 11

#include <type_traits>

#if NC_TEST_ID == 0
using T = std::make_unsigned_t<void>;
#elif NC_TEST_ID == 1
using T = std::make_unsigned_t<std::nullptr_t>;
#elif NC_TEST_ID == 2
using T = std::make_unsigned_t<float>;
#elif NC_TEST_ID == 3
using T = std::make_unsigned_t<int[10]>;
#elif NC_TEST_ID == 4
using T = make_unsigned_t<void*>;
#elif NC_TEST_ID == 5
using T = make_unsigned_t<int&>;
#elif NC_TEST_ID == 6
using T = make_unsigned_t<int&&>;
#elif NC_TEST_ID == 7
struct S {
    int f;
};
using T = make_unsigned_t<decltype(&S::f)>;
#elif NC_TEST_ID == 8
struct S {
    int f();
};
using T = make_unsigned_t<decltype(&S::f)>;
#elif NC_TEST_ID == 9
union S {
    int x;
    long y;
};
using T = make_unsigned_t<S>;
#elif NC_TEST_ID == 10
struct TypedInt {
    int x;
};
using T = make_unsigned_t<TypedInt>;
#elif NC_TEST_ID == 11
using T = make_unsigned_t<int(int, int)>;
#endif
