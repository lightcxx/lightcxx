#ifndef __LIGHTCXX_GUARD_UTILITY_CORE_H
#define __LIGHTCXX_GUARD_UTILITY_CORE_H

#include <type_traits>

namespace std {

template<class _T>
constexpr _T&& forward(remove_reference_t<_T>& __t) noexcept {
    return static_cast<_T&&>(__t);
}

template<class _T>
constexpr _T&& forward(remove_reference_t<_T>&& __t) noexcept {
    static_assert(!is_lvalue_reference_v<_T>, "can not forward an rvalue as an lvalue");
    return static_cast<_T&&>(__t);
}

template<class _T>
constexpr remove_reference_t<_T>&& move(_T&& __t) noexcept {
    return static_cast<remove_reference_t<_T>&&>(__t);
}

}  // namespace std

#endif
