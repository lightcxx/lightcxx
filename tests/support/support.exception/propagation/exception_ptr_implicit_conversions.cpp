// EXPECT:NO_COMPILE 9

#include <exception>

#include "testing.h"

void takes_bool(bool) {}

void takes_int(int) {}

void takes_unsigned_long(unsigned long) {}

void takes_double(double) {}

enum OldStyleEnum {
    OSE_a,
    OSE_b,
};
void takes_old_style_enum(OldStyleEnum) {}

enum class ScopedEnum {
    a,
    b,
};
void takes_scoped_enum(ScopedEnum) {}

void takes_int_ptr(int*) {}

void takes_unsigned_char_ptr(unsigned char*) {}

void takes_void_ptr(void*) {}

TEST() {
    std::exception_ptr exc;
#if NEGATIVE_COMPILE_ITERATION == 0
    takes_bool(exc);
#elif NEGATIVE_COMPILE_ITERATION == 1
    takes_int(exc);
#elif NEGATIVE_COMPILE_ITERATION == 2
    takes_unsigned_long(exc);
#elif NEGATIVE_COMPILE_ITERATION == 3
    takes_double(exc);
#elif NEGATIVE_COMPILE_ITERATION == 4
    takes_old_style_enum(exc);
#elif NEGATIVE_COMPILE_ITERATION == 5
    takes_scoped_enum(exc);
#elif NEGATIVE_COMPILE_ITERATION == 6
    takes_int_ptr(exc);
#elif NEGATIVE_COMPILE_ITERATION == 7
    takes_unsigned_char_ptr(exc);
#elif NEGATIVE_COMPILE_ITERATION == 8
    takes_void_ptr(exc);
#endif
}
