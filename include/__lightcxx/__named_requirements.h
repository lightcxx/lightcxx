#ifndef __LIGHTCXX_GUARD_LIGHTCXX_NAMED_REQUIREMENTS_H
#define __LIGHTCXX_GUARD_LIGHTCXX_NAMED_REQUIREMENTS_H

#include <type_traits>

namespace std::_Light {

struct _Cpp17CopyConstructible {
    template<class _T>
    static constexpr bool __check() noexcept {
        return is_copy_constructible_v<_T>;
    }

    template<class _T>
    static constexpr void __assert() noexcept {
        static_assert(__check<_T>(), "Type does not satisfy requirement Cpp17CopyConstructible");
    }
};

}

#endif
