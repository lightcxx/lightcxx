#ifndef __LIGHTCXX_GUARD_LIGHTCXX_TYPE_TRAITS_BUILTINS_H
#define __LIGHTCXX_GUARD_LIGHTCXX_TYPE_TRAITS_BUILTINS_H

namespace _Light {

template<class _T>
constexpr bool _IsIntegral = __is_integral(_T);

}

#endif
