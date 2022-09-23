#ifndef LIGHTCXX_TESTS_BITSET_TESTING_H
#define LIGHTCXX_TESTS_BITSET_TESTING_H

#include <bitset>

namespace Testing {

constexpr const char* random_bits = "0101010111010101110101010101110111101101010110101010100101101010111111100000101111101010000111001101010101010100101010110101000101000101001000101001000010111110001101110011110010101001010101001010101001010101011111111000000100111010111010111000111101110111";
constexpr const char* random_bits_2 = "1000111011101010100101001001011111010101111010010100101000011110100101001010010100100100000011110101010111101010101010101010101111010101010101000001111010101011110101000011101010101010001010101100001000011011111000101101010101010101111100101010101110101010";

template<std::size_t N>
std::bitset<N> build_bitset(const char* s) {
    std::bitset<N> a;
    for (std::size_t i = 0; i < N; i++) {
        a.set(i, s[i] == '1');
    }
    return a;
}

template<template<std::size_t> class op>
void apply_bitset_tests_all_sizes() {
    op<1>::test();
    op<2>::test();
    op<7>::test();
    op<8>::test();
    op<9>::test();
    op<15>::test();
    op<16>::test();
    op<17>::test();
    op<31>::test();
    op<32>::test();
    op<33>::test();
    op<63>::test();
    op<64>::test();
    op<65>::test();
    op<127>::test();
    op<128>::test();
    op<129>::test();
    op<191>::test();
    op<192>::test();
    op<193>::test();
    op<255>::test();
    op<256>::test();
}

}  // namespace Testing

#endif
