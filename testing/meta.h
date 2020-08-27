#ifndef TESTING_META_H
#define TESTING_META_H

#include <type_traits>

namespace Testing {

template<class T, class... Args>
constexpr bool IsOneOf = (std::is_same_v<T, Args> || ...);

template<class T>
constexpr bool IsSignedIntegerType = IsOneOf<T, signed char, short, int, long, long long>;

template<class T>
constexpr bool IsUnsignedIntegerType
  = IsOneOf<T, unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long>;

}  // namespace Testing

#endif
