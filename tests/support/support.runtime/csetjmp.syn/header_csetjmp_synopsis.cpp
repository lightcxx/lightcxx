#include <csetjmp>

#include "testing.h"

#ifndef setjmp
#error "setjmp not defined"
#endif

TEST() {
    std::jmp_buf jb;
    auto&& ret = setjmp(jb);
    expect_type_and_value<int&>(ret, 0);
    expect_type(void, std::longjmp(jb, 0));
}

TEST(using_longjmp) {
    bool jumped = false;
    std::jmp_buf jb;
    auto&& ret = setjmp(jb);
    if (jumped) {
        expect(ret == 1);
        return;
    }
    expect(ret == 0);
    jumped = true;
    std::longjmp(jb, 1);
}
