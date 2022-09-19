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
        __obj = _Light::__any_alloc(__other.__vtable->__alignment, __other.__vtable->__size);
        try {
            __vtable->__copy(__other.__obj, __obj);
        } catch(...) {
            free(__obj);
            throw;
        }
    }
}

_EXPORT any::any(any&& __other) noexcept
        : __vtable(__other.__vtable), __obj(__other.__obj) {
    __other.__vtable = nullptr;
}

_EXPORT any::~any() {
    if (__vtable != nullptr) {
        __vtable->__dtor(__obj);
        free(__obj);
    }
}

_EXPORT any& any::operator=(const any& __rhs) {
    if (this != addressof(__rhs)) {
        if (!__rhs.has_value()) {
            reset();
        } else {
            void* __new_obj = _Light::__any_alloc(__rhs.__vtable->__alignment, __rhs.__vtable->__size);
            try {
                __rhs.__vtable->__copy(__rhs.__obj, __new_obj);
            } catch (...) {
                free(__new_obj);
                throw;
            }
            reset();
            __vtable = __rhs.__vtable;
            __obj = __new_obj;
        }
    }
    return *this;
}

_EXPORT any& any::operator=(any&& __rhs) noexcept {
    if (this != addressof(__rhs)) {
        reset();
        __vtable = __rhs.__vtable;
        __obj = __rhs.__obj;
        __rhs.__vtable = nullptr;
    }
    return *this;
}

_EXPORT void any::reset() noexcept {
    if (__vtable != nullptr) {
        __vtable->__dtor(__obj);
        free(__obj);
        __vtable = nullptr;
    }
}

_EXPORT void any::swap(std::any& __rhs) noexcept {
    std::swap(__vtable, __rhs.__vtable);
    std::swap(__obj, __rhs.__obj);
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
