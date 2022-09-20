#include "cstring"

#include "export.h"

#include <string.h>

namespace std {

_EXPORT void* memchr(const void* __s, int __c, size_t __n) {
    return ::memchr(__s, __c, __n);
}

_EXPORT int memcmp(const void* __s1, const void* __s2, size_t __n) {
    return ::memcmp(__s1, __s2, __n);
}

_EXPORT void* memcpy(void* __dst, const void* __src, size_t __n) {
    return ::memcpy(__dst, __src, __n);
}

_EXPORT void* memmove(void* __dst, const void* __src, size_t __len) {
    return ::memmove(__dst, __src, __len);
}

_EXPORT void* memset(void* __b, int __c, size_t __len) {
    return ::memset(__b, __c, __len);
}

_EXPORT char* strcat(char* __s1, const char* __s2) {
    return ::strcat(__s1, __s2);
}

_EXPORT char* strchr(const char* __s, int __c) {
    return ::strchr(__s, __c);
}

_EXPORT int strcmp(const char* __s1, const char* __s2) {
    return ::strcmp(__s1, __s2);
}

_EXPORT int strcoll(const char* __s1, const char* __s2) {
    return ::strcoll(__s1, __s2);
}

_EXPORT char* strcpy(char* __dst, const char* __src) {
    return ::strcpy(__dst, __src);
}

_EXPORT size_t strcspn(const char* __s, const char* __charset) {
    return ::strcspn(__s, __charset);
}

_EXPORT char* strerror(int __errnum) {
    return ::strerror(__errnum);
}

_EXPORT size_t strlen(const char* __s) {
    return ::strlen(__s);
}

_EXPORT char* strncat(char* __s1, const char* __s2, size_t __n) {
    return ::strncat(__s1, __s2, __n);
}

_EXPORT int strncmp(const char* __s1, const char* __s2, size_t __n) {
    return ::strncmp(__s1, __s2, __n);
}

_EXPORT char* strncpy(char* __dst, const char* __src, size_t __n) {
    return ::strncpy(__dst, __src, __n);
}

_EXPORT char* strpbrk(const char* __s, const char* __charset) {
    return ::strpbrk(__s, __charset);
}

_EXPORT char* strrchr(const char* __s, int __c) {
    return ::strrchr(__s, __c);
}

_EXPORT size_t strspn(const char* __s, const char* __charset) {
    return ::strspn(__s, __charset);
}

_EXPORT char* strstr(const char* __big, const char* __little) {
    return ::strstr(__big, __little);
}

_EXPORT char* strtok(char* __str, const char* __sep) {
    return ::strtok(__str, __sep);
}

_EXPORT size_t strxfrm(char* __s1, const char* __s2, size_t __n) {
    return ::strxfrm(__s1, __s2, __n);
}

_EXPORT char* strtok_r(char* __str, const char* __sep, char** __lasts) {
    return ::strtok_r(__str, __sep, __lasts);
}

_EXPORT int strerror_r(int __errnum, char* __strerrbuf, size_t __buflen) {
    return ::strerror_r(__errnum, __strerrbuf, __buflen);
}

_EXPORT char* strdup(const char* __s1) {
    return ::strdup(__s1);
}

_EXPORT void* memccpy(void* __dst, const void* __src, int __c, size_t __n) {
    return ::memccpy(__dst, __src, __c, __n);
}

_EXPORT char* stpcpy(char* __dst, const char* __src) {
    return ::stpcpy(__dst, __src);
}

_EXPORT char* stpncpy(char* __dst, const char* __src, size_t __n) {
    return ::stpncpy(__dst, __src, __n);
}

_EXPORT char* strndup(const char* __s1, size_t __n) {
    return ::strndup(__s1, __n);
}

_EXPORT size_t strnlen(const char* __s1, size_t __n) {
    return ::strnlen(__s1, __n);
}

_EXPORT char* strsignal(int __sig) {
    return ::strsignal(__sig);
}

}  // namespace std
