#include "any"

#include "export.h"

namespace std {

namespace _Light {

_EXPORT void* __any_alloc(size_t __align, size_t __size) {
    if (__align <= alignof(max_align_t)) {
        return malloc(__size);
    }
    void* __mem = aligned_alloc(__align, __size);
    if (__mem == nullptr) {
        throw bad_alloc{};
    }
    return __mem;
}

}  // namespace _Light

_EXPORT bad_any_cast::~bad_any_cast() {}

_EXPORT const char* bad_any_cast::what() const noexcept {
    return "bad_any_cast";
}

_EXPORT any::any(const any& __other)
        : __vtable(__other.__vtable) {
    if (__vtable != nullptr) {
        __vtable->__copy(__other.__obj, __obj);
    }
}

_EXPORT any::any(any&& __other) noexcept
        : __vtable(__other.__vtable) {
    if (__vtable != nullptr) {
        __vtable->__move(__other.__obj, __obj);
    }
    __other.__vtable = nullptr;
}

_EXPORT any::~any() {
    if (__vtable != nullptr) {
        __vtable->__dtor(__obj);
        if (!__vtable->__is_local) {
            free(__obj.__remote);
        }
    }
}

_EXPORT any& any::operator=(const any& __rhs) {
    if (this != addressof(__rhs)) {
        if (!__rhs.has_value()) {
            reset();
        } else {
            _Light::_AnyStorage __new_obj;
            __rhs.__vtable->__copy(__rhs.__obj, __new_obj);
            reset();
            __vtable = __rhs.__vtable;
            __vtable->__move(__new_obj, __obj);
        }
    }
    return *this;
}

_EXPORT any& any::operator=(any&& __rhs) noexcept {
    if (this != addressof(__rhs)) {
        reset();
        __vtable = __rhs.__vtable;
        if (__vtable != nullptr) {
            __vtable->__move(__rhs.__obj, __obj);
        }
        __rhs.__vtable = nullptr;
    }
    return *this;
}

_EXPORT void any::reset() noexcept {
    if (__vtable != nullptr) {
        __vtable->__dtor(__obj);
        if (!__vtable->__is_local) {
            free(__obj.__remote);
        }
        __vtable = nullptr;
    }
}

_EXPORT void any::swap(any& __rhs) noexcept {
    if (__vtable == nullptr && __rhs.__vtable == nullptr) {
    } else if (__vtable == nullptr) {
        __rhs.__vtable->__move(__rhs.__obj, __obj);
        std::swap(__vtable, __rhs.__vtable);
    } else if (__rhs.__vtable == nullptr) {
        __vtable->__move(__obj, __rhs.__obj);
        std::swap(__vtable, __rhs.__vtable);
    } else {
        if (__vtable->__is_local && __rhs.__vtable->__is_local) {
            _Light::_AnyStorage __tmp;
            __vtable->__move(__obj, __tmp);
            __rhs.__vtable->__move(__rhs.__obj, __obj);
            __vtable->__move(__tmp, __rhs.__obj);
        } else if (__vtable->__is_local) {
            void* __tmp = __rhs.__obj.__remote;
            __vtable->__move(__obj, __rhs.__obj);
            __obj.__remote = __tmp;
        } else if (__rhs.__vtable->__is_local) {
            void* __tmp = __obj.__remote;
            __rhs.__vtable->__move(__rhs.__obj, __obj);
            __rhs.__obj.__remote = __tmp;
        } else {
            std::swap(__obj.__remote, __rhs.__obj.__remote);
        }
        std::swap(__vtable, __rhs.__vtable);
    }
}

_EXPORT bool any::has_value() const noexcept {
    return __vtable != nullptr;
}

_EXPORT const type_info& any::type() const noexcept {
    return __vtable != nullptr ? __vtable->__type : typeid(void);
}

_EXPORT void swap(any& __x, any& __y) noexcept {
    __x.swap(__y);
}

}  // namespace std
