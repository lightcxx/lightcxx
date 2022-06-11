#include <csetjmp>

#include "testing.h"

#ifndef setjmp
#error "setjmp not defined"
#endif

TEST() {
    std::jmp_buf jb;
    auto&& ret = setjmp(jb);
    expect_type_and_value(ret, int&, 0);
    expect_type(void, std::longjmp(jb, 0));
}

bool jumped = false;

void func(std::jmp_buf& jb, int ret) {
    if (jumped) {
        expect(ret == 1);
        return;
    }
    expect(ret == 0);
    jumped = true;
    std::longjmp(jb, 1);
}

TEST(using_longjmp) {
    std::jmp_buf jb;
    auto&& ret = setjmp(jb);
    func(jb, ret);
}
