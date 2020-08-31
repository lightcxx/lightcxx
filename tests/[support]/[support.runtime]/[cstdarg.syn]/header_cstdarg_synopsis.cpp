#include <cstdarg>

#include "testing.h"

static void sum_and_product(long long* sum, long long* product, const char* format, ...) {
    std::va_list va_s;
    va_start(va_s, format);
    std::va_list va_p;
    va_copy(va_p, va_s);
    *sum = 0;
    *product = 1;
    for (const char* p = format; *p != '\0'; p++) {
        switch (*p) {
            case 'd': {
                *sum += va_arg(va_s, int);
                *product *= va_arg(va_p, int);
                break;
            }
            case 'l': {
                *sum += va_arg(va_s, long);
                *product *= va_arg(va_p, long);
                break;
            }
            case 'L': {
                *sum += va_arg(va_s, long long);
                *product *= va_arg(va_p, long long);
                break;
            }
            case 'u': {
                *sum += va_arg(va_s, unsigned);
                *product *= va_arg(va_p, unsigned);
                break;
            }
            case 'U': {
                *sum += va_arg(va_s, unsigned long);
                *product *= va_arg(va_p, unsigned long);
                break;
            }
            default: {
                Testing::fail();
            }
        }
    }
    va_end(va_s);
    va_end(va_p);
}

TEST() {
    long long s, p;
    sum_and_product(&s, &p, "Lld", 1LL, 2l, 3);
    expect(s == 6 && p == 6);
    sum_and_product(&s, &p, "uLLd", 2u, 2LL, 2LL, 2);
    expect(s == 8 && p == 16);
    sum_and_product(&s, &p, "dddd", 2, 2, 2, 2);
    expect(s == 8 && p == 16);
}
