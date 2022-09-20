#include "cstring"

#include "export.h"

#include <string.h>

namespace std {

_EXPORT char* strcpy(char* __dst, const char* __src) {
    return ::strcpy(__dst, __src);
}

_EXPORT char* strncpy(char* __dst, const char* __src, size_t __n) {
    return ::strncpy(__dst, __src, __n);
}

_EXPORT char* strcat(char* __dst, const char* __src) {
    return ::strcat(__dst, __src);
}

_EXPORT char* strncat(char* __dst, const char* __src, size_t __n) {
    return ::strncat(__dst, __src, __n);
}

_EXPORT size_t strxfrm(char* __dst, const char* __src, size_t __n) {
    return ::strxfrm(__dst, __src, __n);
}

_EXPORT size_t strlen(const char* __str) {
    return ::strlen(__str);
}

_EXPORT int strcmp(const char* __lhs, const char* __rhs) {
    return ::strcmp(__lhs, __rhs);
}

_EXPORT int strncmp(const char* __lhs, const char* __rhs, size_t __n) {
    return ::strncmp(__lhs, __rhs, __n);
}

_EXPORT int strcoll(const char* __lhs, const char* __rhs) {
    return ::strcoll(__lhs, __rhs);
}

_EXPORT const char* strchr(const char* __str, int __ch) {
    return ::strchr(__str, __ch);
}

_EXPORT char* strchr(char* __str, int __ch) {
    return ::strchr(__str, __ch);
}

_EXPORT const char* strrchr(const char* __str, int __ch) {
    return ::strrchr(__str, __ch);
}

_EXPORT char* strrchr(char* __str, int __ch) {
    return ::strrchr(__str, __ch);
}

_EXPORT size_t strspn(const char* __dst, const char* __src) {
    return ::strspn(__dst, __src);
}

_EXPORT size_t strcspn(const char* __dst, const char* __src) {
    return ::strcspn(__dst, __src);
}

_EXPORT const char* strpbrk(const char* __dst, const char* __breakset) {
    return ::strpbrk(__dst, __breakset);
}

_EXPORT char* strpbrk(char* __dst, const char* __breakset) {
    return ::strpbrk(__dst, __breakset);
}

_EXPORT const char* strstr(const char* __haystack, const char* __needle) {
    return ::strstr(__haystack, __needle);
}

_EXPORT char* strstr(char* __haystack, const char* __needle) {
    return ::strstr(__haystack, __needle);
}

_EXPORT char* strtok(char* __str, const char* __delim) {
    return ::strtok(__str, __delim);
}

_EXPORT char* strerror(int __errnum) {
    return ::strerror(__errnum);
}

_EXPORT const void* memchr(const void* __ptr, int __ch, size_t __n) {
    return ::memchr(__ptr, __ch, __n);
}

_EXPORT void* memchr(void* __ptr, int __ch, size_t __n) {
    return ::memchr(__ptr, __ch, __n);
}

_EXPORT int memcmp(const void* __lhs, const void* __rhs, size_t __n) {
    return ::memcmp(__lhs, __rhs, __n);
}

_EXPORT void* memset(void* __dst, int __ch, size_t __n) {
    return ::memset(__dst, __ch, __n);
}

_EXPORT void* memcpy(void* __dst, const void* __src, size_t __n) {
    return ::memcpy(__dst, __src, __n);
}

_EXPORT void* memmove(void* __dst, const void* __src, size_t __n) {
    return ::memmove(__dst, __src, __n);
}

}  // namespace std
