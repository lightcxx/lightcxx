#ifndef __LIGHTCXX_GUARD_DECLVAL_H
#define __LIGHTCXX_GUARD_DECLVAL_H

namespace std {

namespace _Light {

template<class _T>
_T&& __declval_impl(int);

template<class _T>
[[maybe_unused]] _T __declval_impl(long);

}  // namespace _Light

template<class _T>
decltype(_Light::__declval_impl<_T>(0)) declval() noexcept;

}  // namespace std

#endif
