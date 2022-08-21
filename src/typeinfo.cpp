#include "typeinfo"

#include "export.h"

namespace std {

_EXPORT type_info::~type_info() = default;

_EXPORT bool type_info::operator==(const type_info& __rhs) const noexcept {
    return name() == __rhs.name();
}

_EXPORT bool type_info::before(const type_info& __rhs) const noexcept {
    return name() < __rhs.name();
}

_EXPORT size_t type_info::hash_code() const noexcept {
    return reinterpret_cast<size_t>(__name);
}

_EXPORT const char* type_info::name() const noexcept {
    return __name;
}

_EXPORT bad_cast::bad_cast() noexcept = default;

_EXPORT bad_cast::bad_cast(const bad_cast&) noexcept = default;

_EXPORT bad_cast& bad_cast::operator=(const bad_cast&) noexcept = default;

_EXPORT bad_cast::~bad_cast() noexcept = default;

_EXPORT const char* bad_cast::what() const noexcept {
    return "bad_cast";
}

_EXPORT bad_typeid::bad_typeid() noexcept = default;

_EXPORT bad_typeid::bad_typeid(const bad_typeid&) noexcept = default;

_EXPORT bad_typeid& bad_typeid::operator=(const bad_typeid&) noexcept = default;

_EXPORT bad_typeid::~bad_typeid() noexcept = default;

_EXPORT const char* bad_typeid::what() const noexcept {
    return "bad_typeid";
}

}  // namespace std
