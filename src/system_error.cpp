#include <system_error>

#include "export.h"

namespace std {

_EXPORT error_category::~error_category() = default;

_EXPORT error_condition error_category::default_error_condition(int __ev) const noexcept {
    return error_condition(__ev, *this);
}

_EXPORT bool error_category::equivalent(int __code, const error_condition& __condition) const noexcept {
    return default_error_condition(__code) == __condition;
}

_EXPORT bool error_category::equivalent(const error_code& __code, int __condition) const noexcept {
    return *this == __code.category() && __code.value() == __condition;
}

_EXPORT bool error_category::operator==(const error_category& __rhs) const noexcept {
    return this == addressof(__rhs);
}

// TODO: After implementing compare_three_way().
//_EXPORT strong_ordering error_category::operator<=>(const error_category& __rhs) const noexcept {
//    return compare_three_way()(this, addressof(__rhs));
//}

namespace _Light {

class _Generic_error_category final : public error_category {
  public:
    using error_category::error_category;
    const char* name() const noexcept final;
};

_EXPORT const char* _Generic_error_category::name() const noexcept {
    return "generic";
}

class _System_error_category final : public error_category {
  public:
    using error_category::error_category;
    const char* name() const noexcept final;
    error_condition default_error_condition(int __ev) const noexcept final;
};

_EXPORT const char* _System_error_category::name() const noexcept {
    return "system";
}

_EXPORT error_condition _System_error_category::default_error_condition(int __ev) const noexcept {
    // TODO: Implement properly!
    return error_condition(__ev, *this);
}

static constinit _Generic_error_category __generic_category{};
static constinit _System_error_category __system_category{};

}  // namespace _Light

_EXPORT const error_category& generic_category() noexcept {
    return _Light::__generic_category;
}

_EXPORT const error_category& system_category() noexcept {
    return _Light::__system_category;
}

_EXPORT error_code::error_code() noexcept
        : error_code(0, system_category()) {}

_EXPORT error_code::error_code(int __v, const error_category& __c) noexcept
        : __val(__v), __cat(addressof(__c)) {
}

_EXPORT void error_code::assign(int __v, const error_category& __c) noexcept {
    __val = __v;
    __cat = addressof(__c);
}

_EXPORT void error_code::clear() noexcept {
    __val = 0;
    __cat = addressof(system_category());
}

_EXPORT int error_code::value() const noexcept {
    return __val;
}

_EXPORT const error_category& error_code::category() const noexcept {
    return *__cat;
}

_EXPORT error_condition error_code::default_error_condition() const noexcept {
    return category().default_error_condition(__val);
}

// TODO: After implementing string.
//_EXPORT string error_code::message() const {
//    return category().message(__val);
//}

_EXPORT error_code::operator bool() const noexcept {
    return __val != 0;
}

_EXPORT error_code make_error_code(errc __e) noexcept {
    return error_code(static_cast<int>(__e), generic_category());
}

_EXPORT error_condition::error_condition() noexcept
        : error_condition(0, generic_category()) {}

_EXPORT error_condition::error_condition(int __v, const error_category& __c) noexcept
        : __val(__v), __cat(addressof(__c)) {}

_EXPORT void error_condition::assign(int __v, const error_category& __c) noexcept {
    __val = __v;
    __cat = addressof(__c);
}

_EXPORT void error_condition::clear() noexcept {
    __val = 0;
    __cat = addressof(generic_category());
}

_EXPORT int error_condition::value() const noexcept {
    return __val;
}

_EXPORT const error_category& error_condition::category() const noexcept {
    return *__cat;
}

// TODO: After implementing string.
//_EXPORT string error_condition::message() const {
//    return category().message(__val);
//}

_EXPORT error_condition::operator bool() const noexcept {
    return __val != 0;
}

_EXPORT error_condition make_error_condition(errc __e) noexcept {
    return error_condition(static_cast<int>(__e), generic_category());
}

_EXPORT bool operator==(const error_code& __lhs, const error_code& __rhs) noexcept {
    return __lhs.category() == __rhs.category() && __lhs.value() == __rhs.value();
}

_EXPORT bool operator==(const error_code& __lhs, const error_condition& __rhs) noexcept {
    return __lhs.category().equivalent(__lhs.value(), __rhs)
           || __rhs.category().equivalent(__lhs, __rhs.value());
}

_EXPORT bool operator==(const error_condition& __lhs, const error_condition& __rhs) noexcept {
    return __lhs.category() == __rhs.category() && __lhs.value() == __rhs.value();
}

_EXPORT strong_ordering operator<=>(const error_code& __lhs, const error_code& __rhs) noexcept {
    if (auto c = __lhs.category() <=> __rhs.category(); c != 0) {
        return c;
    }
    return __lhs.value() <=> __rhs.value();
}

_EXPORT strong_ordering operator<=>(const error_condition& __lhs, const error_condition& __rhs) noexcept {
    if (auto c = __lhs.category() <=> __rhs.category(); c != 0) {
        return c;
    }
    return __lhs.value() <=> __rhs.value();
}

}  // namespace std
