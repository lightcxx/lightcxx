#include "exception"

#include "cstdlib"
#include "export.h"
#include "handler.h"

extern "C" {
unsigned int __cxa_uncaught_exceptions() throw();
void* __cxa_current_primary_exception() throw();
void __cxa_rethrow_primary_exception(void*);
void __cxa_increment_exception_refcount(void*) throw();
void __cxa_decrement_exception_refcount(void*) throw();
}

namespace std {

_EXPORT exception::exception() noexcept = default;

_EXPORT exception::exception(const exception&) noexcept = default;

_EXPORT exception& exception::operator=(const exception&) noexcept = default;

_EXPORT exception::~exception() noexcept = default;

_EXPORT const char* exception::what() const noexcept {
    return "exception";
}

_EXPORT bad_exception::bad_exception() noexcept = default;

_EXPORT bad_exception::bad_exception(const bad_exception&) noexcept = default;

_EXPORT bad_exception& bad_exception::operator=(const bad_exception&) noexcept = default;

_EXPORT bad_exception::~bad_exception() noexcept = default;

_EXPORT const char* bad_exception::what() const noexcept {
    return "bad_exception";
}

static constinit _Light::handler<terminate_handler> global_terminate_handler;

_EXPORT terminate_handler set_terminate(terminate_handler f) noexcept {
    return global_terminate_handler.set(f);
}

_EXPORT terminate_handler get_terminate() noexcept {
    return global_terminate_handler.get();
}

[[noreturn]] _EXPORT void terminate() noexcept {
    const auto handler = get_terminate();
    if (handler != nullptr) {
        try {
            handler();
        } catch (...) {}
    }
    abort();
}

_EXPORT int uncaught_exceptions() noexcept {
    return int(__cxa_uncaught_exceptions());
}

_EXPORT exception_ptr current_exception() noexcept {
    return exception_ptr(__cxa_current_primary_exception());
}

[[noreturn]] _EXPORT void rethrow_exception(exception_ptr p) {
    if (p == nullptr) {
        terminate();
    }
    __cxa_rethrow_primary_exception(p.__ptr);
    terminate();
}

_EXPORT exception_ptr::exception_ptr() noexcept = default;

_EXPORT exception_ptr::exception_ptr(nullptr_t) noexcept
        : exception_ptr() {}

_EXPORT exception_ptr::exception_ptr(const exception_ptr& __other) noexcept
        : __ptr(__other.__ptr) {
    __cxa_increment_exception_refcount(__ptr);
}

_EXPORT exception_ptr& exception_ptr::operator=(const exception_ptr& __other) noexcept {
    if (__ptr != __other.__ptr) {
        __cxa_increment_exception_refcount(__other.__ptr);
        __cxa_decrement_exception_refcount(__ptr);
        __ptr = __other.__ptr;
    }
    return *this;
}

_EXPORT exception_ptr::~exception_ptr() noexcept {
    __cxa_decrement_exception_refcount(__ptr);
}

_EXPORT exception_ptr::exception_ptr(void* __ptr)
        : __ptr(__ptr) {}

_EXPORT nested_exception::nested_exception() noexcept
        : __nested_ptr(current_exception()) {}

_EXPORT nested_exception::nested_exception(const nested_exception&) noexcept = default;

_EXPORT nested_exception& nested_exception::operator=(const nested_exception&) noexcept = default;

_EXPORT nested_exception::~nested_exception() = default;

_EXPORT void nested_exception::rethrow_nested() const {
    if (__nested_ptr == nullptr) {
        terminate();
    }
    rethrow_exception(__nested_ptr);
}

_EXPORT exception_ptr nested_exception::nested_ptr() const noexcept {
    return __nested_ptr;
}

}  // namespace std

// Stubs for libc++abi
namespace std {

[[noreturn, maybe_unused]] _EXPORT void __terminate(terminate_handler handler) noexcept {
    if (handler) {
        try {
            handler();
        } catch (...) {}
    }
    abort();
}

[[noreturn, maybe_unused]] _EXPORT void __unexpected(terminate_handler handler) noexcept {
    if (handler) {
        try {
            handler();
        } catch (...) {}
    }
    abort();
}

_EXPORT terminate_handler get_unexpected() noexcept {
    return abort;
}

}  // namespace std
