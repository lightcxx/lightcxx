#ifndef _LIGHTCXX_GUARD_TESTING_META_H
#define _LIGHTCXX_GUARD_TESTING_META_H

namespace Testing {

template<class T, class U>
struct IsSameType {
    static constexpr bool value = false;
};
template<class T>
struct IsSameType<T, T> {
    static constexpr bool value = true;
};

template<class T, class... Args>
constexpr bool IsOneOf = (IsSameType<T, Args>::value || ...);

template<class T>
constexpr bool IsSignedIntegerType = IsOneOf<T, signed char, short, int, long, long long>;

template<class T>
constexpr bool IsUnsignedIntegerType
  = IsOneOf<T, unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long>;

}

#endif
