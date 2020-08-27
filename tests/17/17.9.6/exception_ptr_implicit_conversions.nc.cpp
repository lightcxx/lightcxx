// EXPECT:NO_COMPILE 8

#include <exception>

#include "testing/test.h"

void takes_bool(bool) {}

void takes_int(int) {}

void takes_unsigned_long(unsigned long) {}

void takes_double(double) {}

enum [[maybe_unused]] OldStyleEnum { OSE_a, OSE_b };
void takes_old_style_enum(OldStyleEnum) {}

enum class [[maybe_unused]] ScopedEnum { a, b };
void takes_scoped_enum(ScopedEnum) {}

void takes_int_ptr(int*) {}

void takes_unsigned_char_ptr(unsigned char*) {}

void takes_void_ptr(void*) {}

TEST() {
    std::exception_ptr exc;
#if NC_TEST_ID == 0
    takes_bool(exc);
#elif NC_TEST_ID == 1
    takes_int(exc);
#elif NC_TEST_ID == 2
    takes_unsigned_long(exc);
#elif NC_TEST_ID == 3
    takes_double(exc);
#elif NC_TEST_ID == 4
    takes_old_style_enum(exc);
#elif NC_TEST_ID == 5
    takes_scoped_enum(exc);
#elif NC_TEST_ID == 6
    takes_int_ptr(exc);
#elif NC_TEST_ID == 7
    takes_unsigned_char_ptr(exc);
#elif NC_TEST_ID == 8
    takes_void_ptr(exc);
#endif
}
