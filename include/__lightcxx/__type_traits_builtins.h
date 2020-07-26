#ifndef __LIGHTCXX_GUARD_LIGHTCXX_TYPE_TRAITS_BUILTINS_H
#define __LIGHTCXX_GUARD_LIGHTCXX_TYPE_TRAITS_BUILTINS_H

#ifdef __clang__

#define _Light_IS_INTEGRAL(_T) __is_integral(_T)

#else

#error "Compiler not supported by the lightcxx implementation of the standard library."

#endif

#endif
