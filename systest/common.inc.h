#include "common.h"

#define TEST_CASE_START                                         \
    extern "C" const char* FUNC_NAME(int test_index) noexcept { \
        static char buf[1024];                                  \
        switch (test_index) {
#define TEST_CASE_END        \
    default: return nullptr; \
        }                    \
        }

#define TEST_TYPE_ALIAS(T) \
    case __COUNTER__:      \
        return describe_type_alias<T>(buf, #T);

#define TEST_CONSTANT(C) \
    case __COUNTER__:    \
        return describe_constant(buf, #C, C);
