#include <cstddef>

#include "testing/test.h"

struct Aggregate {
    [[maybe_unused]] int x;
};

void Testing::run() {
    ::std::byte b{3};
    const char* str;
    Aggregate ag;
#if NC_TEST_ID == 0
    b << str;
#elif NC_TEST_ID == 1
    b <<= str;
#elif NC_TEST_ID == 2
    b >> str;
#elif NC_TEST_ID == 3
    b >>= str;
#elif NC_TEST_ID == 4
    ::std::to_integer<const char*>(b);
#elif NC_TEST_ID == 5
    b << ag;
#elif NC_TEST_ID == 6
    b <<= ag;
#elif NC_TEST_ID == 7
    b >> ag;
#elif NC_TEST_ID == 8
    b >>= ag;
#elif NC_TEST_ID == 9
    ::std::to_integer<Aggregate>(b);
#endif
}
