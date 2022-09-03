#include "cstdlib"

#include "exception"
#include "handler.h"

// Un-define this so we can get it from the LibC implementation.
#undef MB_CUR_MAX

#include "export.h"
#include <math.h>
#include <stdlib.h>

namespace {

constinit std::_Light::handler_array<std::_Light::_AtExitHandler*, 32> quick_exit_handlers{};

}

namespace std {

namespace _Light {

_EXPORT int _MBCurMax() {
#ifdef __clang__
    return static_cast<int>(MB_CUR_MAX);
#else
    return MB_CUR_MAX;
#endif
}

}  // namespace _Light

[[noreturn]] _EXPORT void abort() noexcept {
    ::abort();
}

_EXPORT int atexit(_Light::_AtExitHandler* func) noexcept {
    return ::atexit(func);
}

_EXPORT int at_quick_exit(_Light::_AtExitHandler* func) noexcept {
    return quick_exit_handlers.add(func);
}

[[noreturn]] _EXPORT void exit(int status) {
    try {
        ::exit(status);
    } catch (...) {
        std::terminate();
    }
}

[[noreturn]] _EXPORT void _Exit(int status) noexcept {
    ::_Exit(status);
}

[[noreturn]] _EXPORT void quick_exit(int status) noexcept {
    quick_exit_handlers.run();
    std::_Exit(status);
}

_EXPORT char* getenv(const char* name) {
    return ::getenv(name);
}

_EXPORT int system(const char* string) {
    return ::system(string);
}

_EXPORT void* aligned_alloc(std::size_t alignment, std::size_t size) {
    return ::aligned_alloc(alignment, size);
}

_EXPORT void* calloc(std::size_t n, std::size_t size) {
    return ::calloc(n, size);
}

_EXPORT void free(void* ptr) {
    ::free(ptr);
}

_EXPORT void* malloc(std::size_t size) {
    return ::malloc(size);
}

_EXPORT void* realloc(void* ptr, std::size_t size) {
    return ::realloc(ptr, size);
}

_EXPORT double atof(const char* str) {
    return ::atof(str);
}

_EXPORT int atoi(const char* str) {
    return ::atoi(str);
}

_EXPORT long atol(const char* str) {
    return ::atol(str);
}

_EXPORT long long atoll(const char* str) {
    return ::atoll(str);
}

_EXPORT double strtod(const char* str, char** end) {
    return ::strtod(str, end);
}

_EXPORT float strtof(const char* str, char** end) {
    return ::strtof(str, end);
}

_EXPORT long double strtold(const char* str, char** end) {
    return ::strtold(str, end);
}

_EXPORT long strtol(const char* str, char** end, int base) {
    return ::strtol(str, end, base);
}

_EXPORT long long strtoll(const char* str, char** end, int base) {
    return ::strtoll(str, end, base);
}

_EXPORT unsigned long strtoul(const char* str, char** end, int base) {
    return ::strtoul(str, end, base);
}

_EXPORT unsigned long long strtoull(const char* str, char** end, int base) {
    return ::strtoull(str, end, base);
}

_EXPORT int mblen(const char* s, size_t n) {
    return ::mblen(s, n);
}

_EXPORT int mbtowc(wchar_t* pwc, const char* s, size_t n) {
    return ::mbtowc(pwc, s, n);
}

_EXPORT int wctomb(char* s, wchar_t wchar) {
    return ::wctomb(s, wchar);
}

_EXPORT size_t mbstowcs(wchar_t* pwcs, const char* s, size_t n) {
    return ::mbstowcs(pwcs, s, n);
}

_EXPORT size_t wcstombs(char* s, const wchar_t* pwcs, size_t n) {
    return ::wcstombs(s, pwcs, n);
}

_EXPORT void* bsearch(const void* key, const void* base, size_t n, size_t size, _Light::_ComparePred* cmp) {
    return ::bsearch(key, base, n, size, cmp);
}

_EXPORT void qsort(void* base, size_t n, size_t size, _Light::_ComparePred* cmp) {
    return ::qsort(base, n, size, cmp);
}

_EXPORT int rand() {
    return ::rand();
}

_EXPORT void srand(unsigned int seed) {
    ::srand(seed);
}

_EXPORT int abs(int j) {
    return ::abs(j);
}

_EXPORT long abs(long j) {
    return ::labs(j);
}

_EXPORT long long abs(long long j) {
    return ::llabs(j);
}

_EXPORT float abs(float j) {
    return ::fabsf(j);
}

_EXPORT double abs(double j) {
    return ::fabs(j);
}

_EXPORT long double abs(long double j) {
    return ::fabsl(j);
}

_EXPORT long labs(long j) {
    return ::labs(j);
}

_EXPORT long long llabs(long long j) {
    return ::llabs(j);
}

_EXPORT div_t div(int num, int den) {
    const auto result = ::div(num, den);
    return {
      .quot = result.quot,
      .rem = result.rem,
    };
}

_EXPORT ldiv_t div(long num, long den) {
    const auto result = ::ldiv(num, den);
    return {
      .quot = result.quot,
      .rem = result.rem,
    };
}

_EXPORT lldiv_t div(long long num, long long den) {
    const auto result = ::lldiv(num, den);
    return {
      .quot = result.quot,
      .rem = result.rem,
    };
}

_EXPORT ldiv_t ldiv(long num, long den) {
    const auto result = ::ldiv(num, den);
    return {
      .quot = result.quot,
      .rem = result.rem,
    };
}

_EXPORT lldiv_t lldiv(long long num, long long den) {
    const auto result = ::lldiv(num, den);
    return {
      .quot = result.quot,
      .rem = result.rem,
    };
}

}  // namespace std
