#ifndef TESTING_WARNINGS_H
#define TESTING_WARNINGS_H

#ifdef __clang__
#    define CLANG_DIAGNOSTIC_PUSH(W) _Pragma("clang diagnostic push") _Pragma(W)
#    define CLANG_DIAGNOSTIC_POP() _Pragma("clang diagnostic pop")
#    define GCC_DIAGNOSTIC_PUSH(W)
#    define GCC_DIAGNOSTIC_POP()
#else
#    define CLANG_DIAGNOSTIC_PUSH(W)
#    define CLANG_DIAGNOSTIC_POP()
#    define GCC_DIAGNOSTIC_PUSH(W) _Pragma("GCC diagnostic push") _Pragma(W)
#    define GCC_DIAGNOSTIC_POP() _Pragma("GCC diagnostic pop")
#endif

#define WARNINGS_IGNORE_NON_VIRTUAL_DTOR()                               \
    GCC_DIAGNOSTIC_PUSH("GCC diagnostic ignored \"-Wnon-virtual-dtor\"") \
    CLANG_DIAGNOSTIC_PUSH("clang diagnostic ignored \"-Wnon-virtual-dtor\"")
#define WARNINGS_POP()     \
    CLANG_DIAGNOSTIC_POP() \
    GCC_DIAGNOSTIC_POP()

#endif
