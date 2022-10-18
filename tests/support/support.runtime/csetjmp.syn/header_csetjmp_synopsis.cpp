#include <csetjmp>

#include "testing.h"

#ifndef setjmp
#error "setjmp not defined"
#endif

TEST() {
    std::jmp_buf jb;
    auto&& ret = setjmp(jb);
    ASSERT_TYPE_AND_VALUE(ret, int&, 0);
    ASSERT_TYPE(void, std::longjmp(jb, 0));
}

bool jumped = false;

void func(std::jmp_buf& jb, int ret) {
    if (jumped) {
        ASSERT(ret == 1);
        return;
    }
    ASSERT(ret == 0);
    jumped = true;
    std::longjmp(jb, 1);
}

TEST(using_longjmp) {
    std::jmp_buf jb;
    auto&& ret = setjmp(jb);
    func(jb, ret);
}
