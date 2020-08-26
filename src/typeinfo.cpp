#include "typeinfo"

namespace std {

type_info::~type_info() = default;

bool type_info::operator==(const type_info& __rhs) const noexcept {
    return name() == __rhs.name();
}

bool type_info::before(const type_info& __rhs) const noexcept {
    return name() < __rhs.name();
}

size_t type_info::hash_code() const noexcept {
    return reinterpret_cast<size_t>(__name);
}

const char* type_info::name() const noexcept {
    return __name;
}

bad_cast::bad_cast() noexcept = default;

bad_cast::bad_cast(const bad_cast&) noexcept = default;

bad_cast& bad_cast::operator=(const bad_cast&) noexcept = default;

bad_cast::~bad_cast() noexcept = default;

const char* bad_cast::what() const noexcept {
    return "bad_cast";
}

bad_typeid::bad_typeid() noexcept = default;

bad_typeid::bad_typeid(const bad_typeid&) noexcept = default;

bad_typeid& bad_typeid::operator=(const bad_typeid&) noexcept = default;

bad_typeid::~bad_typeid() noexcept = default;

const char* bad_typeid::what() const noexcept {
    return "bad_typeid";
}

}  // namespace std
