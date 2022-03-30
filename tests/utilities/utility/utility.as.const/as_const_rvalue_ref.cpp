// EXPECT:NO_COMPILE 1

#include <utility>

#include "testing.h"

struct Struct {};

TEST() {
#if NC_TEST_ID == 0
    std::as_const(Struct{});
#elif NC_TEST_ID == 1
    std::as_const(3);
#endif
}
