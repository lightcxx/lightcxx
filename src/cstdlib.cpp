#include "cstdlib"

#include "exception"
#include "handler.h"

// Un-define this so we can get it from the LibC implementation.
#undef MB_CUR_MAX

#include <math.h>
// TODO: Remove dependency on C's <stdatomic.h> once <atomic> is implemented.
#include <stdatomic.h>
#include <stdlib.h>

namespace std {

namespace _Light {

namespace {

atomic_size_t num_quick_exit_handlers = 0;
Handler<_AtExitHandler*> quick_exit_handlers[32]{};

}  // namespace

int _MBCurMax() {
    return MB_CUR_MAX;
}

}  // namespace _Light

[[noreturn]] void abort() noexcept {
    ::abort();
}

int atexit(_Light::_AtExitHandler* func) noexcept {
    return ::atexit(func);
}

int at_quick_exit(_Light::_AtExitHandler* func) noexcept {
    const auto index = atomic_fetch_add(&_Light::num_quick_exit_handlers, 1);
    if (index >= 32) {
        return 1;
    }
    _Light::quick_exit_handlers[index].set(func);
    return 0;
}

[[noreturn]] void exit(int status) {
    try {
        ::exit(status);
    } catch (...) {
        std::terminate();
    }
}

[[noreturn]] void _Exit(int status) noexcept {
    ::_Exit(status);
}

[[noreturn]] void quick_exit(int status) noexcept {
    auto index = atomic_load_explicit(&_Light::num_quick_exit_handlers, memory_order_acquire);
    if (index > 32)
        index = 32;
    for (; index > 0; --index) {
        try {
            _Light::quick_exit_handlers[index - 1].get()();
        } catch (...) {
            std::terminate();
        }
    }
    std::_Exit(status);
}

char* getenv(const char* name) {
    return ::getenv(name);
}

int system(const char* string) {
    return ::system(string);
}

void* aligned_alloc(std::size_t alignment, std::size_t size) {
    return ::aligned_alloc(alignment, size);
}

void* calloc(std::size_t n, std::size_t size) {
    return ::calloc(n, size);
}

void free(void* ptr) {
    ::free(ptr);
}

void* malloc(std::size_t size) {
    return ::malloc(size);
}

void* realloc(void* ptr, std::size_t size) {
    return ::realloc(ptr, size);
}

double atof(const char* str) {
    return ::atof(str);
}

int atoi(const char* str) {
    return ::atoi(str);
}

long atol(const char* str) {
    return ::atol(str);
}

long long atoll(const char* str) {
    return ::atoll(str);
}

double strtod(const char* str, char** end) {
    return ::strtod(str, end);
}

float strtof(const char* str, char** end) {
    return ::strtof(str, end);
}

long double strtold(const char* str, char** end) {
    return ::strtold(str, end);
}

long strtol(const char* str, char** end, int base) {
    return ::strtol(str, end, base);
}

long long strtoll(const char* str, char** end, int base) {
    return ::strtoll(str, end, base);
}

unsigned long strtoul(const char* str, char** end, int base) {
    return ::strtoul(str, end, base);
}

unsigned long long strtoull(const char* str, char** end, int base) {
    return ::strtoull(str, end, base);
}

int mblen(const char* s, size_t n) {
    return ::mblen(s, n);
}

int mbtowc(wchar_t* pwc, const char* s, size_t n) {
    return ::mbtowc(pwc, s, n);
}

int wctomb(char* s, wchar_t wchar) {
    return ::wctomb(s, wchar);
}

size_t mbstowcs(wchar_t* pwcs, const char* s, size_t n) {
    return ::mbstowcs(pwcs, s, n);
}

size_t wcstombs(char* s, const wchar_t* pwcs, size_t n) {
    return ::wcstombs(s, pwcs, n);
}

void* bsearch(const void* key, const void* base, size_t n, size_t size, _Light::_ComparePred* cmp) {
    return ::bsearch(key, base, n, size, cmp);
}

void qsort(void* base, size_t n, size_t size, _Light::_ComparePred* cmp) {
    return ::qsort(base, n, size, cmp);
}

int rand() {
    return ::rand();
}

void srand(unsigned int seed) {
    ::srand(seed);
}

int abs(int j) {
    return ::abs(j);
}

long abs(long j) {
    return ::labs(j);
}

long long abs(long long j) {
    return ::llabs(j);
}

float abs(float j) {
    return ::fabsf(j);
}

double abs(double j) {
    return ::fabs(j);
}

long double abs(long double j) {
    return ::fabsl(j);
}

long labs(long j) {
    return ::labs(j);
}

long long llabs(long long j) {
    return ::llabs(j);
}

div_t div(int num, int den) {
    const auto result = ::div(num, den);
    return {
      .quot = result.quot,
      .rem = result.rem,
    };
}

ldiv_t div(long num, long den) {
    const auto result = ::ldiv(num, den);
    return {
      .quot = result.quot,
      .rem = result.rem,
    };
}

lldiv_t div(long long num, long long den) {
    const auto result = ::lldiv(num, den);
    return {
      .quot = result.quot,
      .rem = result.rem,
    };
}

ldiv_t ldiv(long num, long den) {
    const auto result = ::ldiv(num, den);
    return {
      .quot = result.quot,
      .rem = result.rem,
    };
}

lldiv_t lldiv(long long num, long long den) {
    const auto result = ::lldiv(num, den);
    return {
      .quot = result.quot,
      .rem = result.rem,
    };
}

}  // namespace std
