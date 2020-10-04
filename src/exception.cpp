#include "exception"

#include "cstdlib"
#include "handler.h"

#include "cxxabi.h"

namespace std {

exception::exception() noexcept = default;

exception::exception(const exception&) noexcept = default;

exception& exception::operator=(const exception&) noexcept = default;

exception::~exception() noexcept = default;

const char* exception::what() const noexcept {
    return "exception";
}

bad_exception::bad_exception() noexcept = default;

bad_exception::bad_exception(const bad_exception&) noexcept = default;

bad_exception& bad_exception::operator=(const bad_exception&) noexcept = default;

bad_exception::~bad_exception() noexcept = default;

const char* bad_exception::what() const noexcept {
    return "bad_exception";
}

namespace {
_Light::Handler<terminate_handler> global_terminate_handler;
}  // namespace

terminate_handler set_terminate(terminate_handler f) noexcept {
    return global_terminate_handler.set(f);
}

terminate_handler get_terminate() noexcept {
    return global_terminate_handler.get();
}

[[noreturn]] void terminate() noexcept {
    const auto handler = get_terminate();
    if (handler) {
        try {
            handler();
        } catch (...) {}
    }
    abort();
}

int uncaught_exceptions() noexcept {
    return __cxxabiv1::__cxa_uncaught_exceptions();
}

exception_ptr current_exception() noexcept {
    return exception_ptr(__cxxabiv1::__cxa_current_primary_exception());
}

[[noreturn]] void rethrow_exception(exception_ptr p) {
    if (p == nullptr) {
        terminate();
    }
    __cxxabiv1::__cxa_rethrow_primary_exception(p.__ptr);
    terminate();
}

exception_ptr::exception_ptr() noexcept = default;

exception_ptr::exception_ptr(nullptr_t) noexcept: exception_ptr() {}

exception_ptr::exception_ptr(const exception_ptr& __other) noexcept: __ptr(__other.__ptr) {
    __cxxabiv1::__cxa_increment_exception_refcount(__ptr);
}

exception_ptr& exception_ptr::operator=(const exception_ptr& __other) noexcept {
    if (__ptr != __other.__ptr) {
        __cxxabiv1::__cxa_increment_exception_refcount(__other.__ptr);
        __cxxabiv1::__cxa_decrement_exception_refcount(__ptr);
        __ptr = __other.__ptr;
    }
    return *this;
}

exception_ptr::~exception_ptr() noexcept {
    __cxxabiv1::__cxa_decrement_exception_refcount(__ptr);
}

exception_ptr::exception_ptr(void* __ptr): __ptr(__ptr) {}

nested_exception::nested_exception() noexcept: __nested_ptr(current_exception()) {}

nested_exception::nested_exception(const nested_exception&) noexcept = default;

nested_exception& nested_exception::operator=(const nested_exception&) noexcept = default;

nested_exception::~nested_exception() = default;

void nested_exception::rethrow_nested() const {
    if (__nested_ptr == nullptr) {
        terminate();
    }
    rethrow_exception(__nested_ptr);
}

exception_ptr nested_exception::nested_ptr() const noexcept {
    return __nested_ptr;
}

}  // namespace std

// Stubs for libc++abi
namespace std {

[[noreturn, maybe_unused]] void __terminate(terminate_handler handler) noexcept {
    if (handler) {
        try {
            handler();
        } catch (...) {}
    }
    abort();
}

[[noreturn, maybe_unused]] void __unexpected(terminate_handler handler) noexcept {
    if (handler) {
        try {
            handler();
        } catch (...) {}
    }
    abort();
}

[[maybe_unused]] terminate_handler get_unexpected() noexcept {
    return abort;
}

}  // namespace std
