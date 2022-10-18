#include <bitset>

#include "testing.h"

template<std::size_t N>
static void test_bitset_default_ctor() {
    std::bitset<N> b;
    ASSERT(b.to_ulong() == 0);
    ASSERT(b.to_ullong() == 0);
    ASSERT(b.count() == 0);
    ASSERT(b.none());
    ASSERT(!b.any());
    ASSERT(!b.all());
    for (std::size_t i = 0; i < N; i++) {
        ASSERT(!b.test(i));
    }
}

TEST(default_ctor) {
    test_bitset_default_ctor<1>();
    test_bitset_default_ctor<2>();
    test_bitset_default_ctor<7>();
    test_bitset_default_ctor<8>();
    test_bitset_default_ctor<9>();
    test_bitset_default_ctor<15>();
    test_bitset_default_ctor<16>();
    test_bitset_default_ctor<17>();
    test_bitset_default_ctor<31>();
    test_bitset_default_ctor<32>();
    test_bitset_default_ctor<33>();
    test_bitset_default_ctor<63>();
    test_bitset_default_ctor<64>();
    test_bitset_default_ctor<65>();
    test_bitset_default_ctor<127>();
    test_bitset_default_ctor<128>();
    test_bitset_default_ctor<129>();
    test_bitset_default_ctor<1023>();
    test_bitset_default_ctor<1024>();
    test_bitset_default_ctor<1025>();
}

template<std::size_t N>
static void test_bitset_ullong_ctor(unsigned long long value) {
    unsigned long long expected = value;
    if constexpr (N < std::_Light::__n_bits<unsigned long long>()) {
        expected &= ((1ull << N) - 1);
    }

    std::bitset<N> b(value);
    ASSERT(b.to_ulong() == expected);
    ASSERT(b.to_ullong() == expected);
    ASSERT(b.count() == static_cast<std::size_t>(std::popcount(expected)));
    ASSERT(b.none() == (expected == 0));
    ASSERT(b.any() == !(expected == 0));
    ASSERT(b.all() == (std::popcount(expected) == N));
    for (std::size_t i = 0; i < N; i++) {
        if (i < std::_Light::__n_bits<unsigned long long>()) {
            ASSERT(b.test(i) == ((expected & (1ull << i)) != 0));
        } else {
            ASSERT(!b.test(i));
        }
    }
}

template<std::size_t N>
void test_all_bitset_ullong_ctors() {
  test_bitset_ullong_ctor<N>(0);
  test_bitset_ullong_ctor<N>(1);
  test_bitset_ullong_ctor<N>(255);
  test_bitset_ullong_ctor<N>(256);
  test_bitset_ullong_ctor<N>(1ull << 20);
  test_bitset_ullong_ctor<N>((1ull << 20) - 1);
  test_bitset_ullong_ctor<N>(0xDEADBEEFull);
}

TEST(ullong_ctor) {
    test_all_bitset_ullong_ctors<1>();
    test_all_bitset_ullong_ctors<2>();
    test_all_bitset_ullong_ctors<7>();
    test_all_bitset_ullong_ctors<8>();
    test_all_bitset_ullong_ctors<9>();
    test_all_bitset_ullong_ctors<15>();
    test_all_bitset_ullong_ctors<16>();
    test_all_bitset_ullong_ctors<17>();
    test_all_bitset_ullong_ctors<31>();
    test_all_bitset_ullong_ctors<32>();
    test_all_bitset_ullong_ctors<33>();
    test_all_bitset_ullong_ctors<63>();
    test_all_bitset_ullong_ctors<64>();
    test_all_bitset_ullong_ctors<65>();
    test_all_bitset_ullong_ctors<127>();
    test_all_bitset_ullong_ctors<128>();
    test_all_bitset_ullong_ctors<129>();
    test_all_bitset_ullong_ctors<1023>();
    test_all_bitset_ullong_ctors<1024>();
    test_all_bitset_ullong_ctors<1025>();
}