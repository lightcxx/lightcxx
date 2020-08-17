#include <typeinfo>

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

const char* bad_cast::what() const noexcept {
    return "bad_cast";
}

const char* bad_typeid::what() const noexcept {
    return "bad_typeid";
}

}  // namespace std

// Add these so compilers using the Itanium ABI will throw lightcxx's implementations of
// bad_cast and bad_typeid
namespace __cxxabiv1 {

[[noreturn]] [[maybe_unused]] extern "C" void __cxa_bad_cast() {
    throw std::bad_cast();
}

[[noreturn]] [[maybe_unused]] extern "C" void __cxa_bad_typeid() {
    throw std::bad_typeid();
}

}  // namespace __cxxabiv1
