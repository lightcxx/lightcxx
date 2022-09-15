#ifndef _LIGHTCXX_GUARD_BIT_H
#define _LIGHTCXX_GUARD_BIT_H

namespace std {

using size_t = decltype(sizeof(nullptr));

namespace _Light {

inline constexpr size_t __char_bit = __CHAR_BIT__;

template<class _T>
constexpr size_t __n_bits() {
    return __char_bit * sizeof(_T);
}

}  // namespace _Light

}  // namespace std

#endif
