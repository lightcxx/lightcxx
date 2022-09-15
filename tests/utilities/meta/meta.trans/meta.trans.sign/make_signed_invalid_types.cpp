// EXPECT:NO_COMPILE 12

#include <type_traits>

#if NEGATIVE_COMPILE_ITERATION == 0
using T = std::make_signed_t<void>;
#elif NEGATIVE_COMPILE_ITERATION == 1
using T = std::make_signed_t<std::nullptr_t>;
#elif NEGATIVE_COMPILE_ITERATION == 2
using T = std::make_signed_t<float>;
#elif NEGATIVE_COMPILE_ITERATION == 3
using T = std::make_signed_t<int[10]>;
#elif NEGATIVE_COMPILE_ITERATION == 4
using T = make_signed_t<void*>;
#elif NEGATIVE_COMPILE_ITERATION == 5
using T = make_signed_t<int&>;
#elif NEGATIVE_COMPILE_ITERATION == 6
using T = make_signed_t<int&&>;
#elif NEGATIVE_COMPILE_ITERATION == 7
struct S {
    int f;
};
using T = make_signed_t<decltype(&S::f)>;
#elif NEGATIVE_COMPILE_ITERATION == 8
struct S {
    int f();
};
using T = make_signed_t<decltype(&S::f)>;
#elif NEGATIVE_COMPILE_ITERATION == 9
union S {
    int x;
    long y;
};
using T = make_signed_t<S>;
#elif NEGATIVE_COMPILE_ITERATION == 10
struct TypedInt {
    int x;
};
using T = make_signed_t<TypedInt>;
#elif NEGATIVE_COMPILE_ITERATION == 11
using T = make_signed_t<int(int, int)>;
#endif
