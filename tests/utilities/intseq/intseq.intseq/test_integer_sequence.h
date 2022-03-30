#ifndef LIGHTCXX_TEST_INTEGER_SEQUENCE
#define LIGHTCXX_TEST_INTEGER_SEQUENCE

#include <type_traits>
#include <utility>

#include "testing.h"

template<class ISeq, std::size_t size, class ValueT>
constexpr void test_integer_sequence() {
    static_assert(std::is_same_v<typename ISeq::value_type, ValueT>);
    static_assert(std::is_same_v<decltype(ISeq::size()), std::size_t>);
    static_assert(ISeq::size() == size);
    static_assert(noexcept(ISeq::size()));
}

#endif