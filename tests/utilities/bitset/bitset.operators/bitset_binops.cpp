#include "../template.bitset/bitset.members/bitset_testing.h"

#include "testing.h"

template<std::size_t N>
struct bitset_binary_ops_tests {
    static void test() {
        const auto bit_a = Testing::build_bitset<N>(Testing::random_bits);
        const auto bit_b = Testing::build_bitset<N>(Testing::random_bits_2);

        {
            const auto result = bit_a ^ bit_b;
            std::size_t num_bits = 0;
            for (std::size_t i = 0; i < N; i++) {
                const auto bit = (Testing::random_bits[i] == '1') != (Testing::random_bits_2[i] == '1');
                ASSERT(result[i] == bit);
                ASSERT(result.test(i) == bit);
                num_bits += bit;
            }
            ASSERT(result.count() == num_bits);
            ASSERT(result.size() == N);
            ASSERT(result.all() == (num_bits == N));
            ASSERT(result.none() == (num_bits == 0));
            ASSERT(result.any() == (num_bits != 0));
        }
        {
            const auto result = bit_a | bit_b;
            std::size_t num_bits = 0;
            for (std::size_t i = 0; i < N; i++) {
                const auto bit = (Testing::random_bits[i] == '1') || (Testing::random_bits_2[i] == '1');
                ASSERT(result[i] == bit);
                ASSERT(result.test(i) == bit);
                num_bits += bit;
            }
            ASSERT(result.count() == num_bits);
            ASSERT(result.size() == N);
            ASSERT(result.all() == (num_bits == N));
            ASSERT(result.none() == (num_bits == 0));
            ASSERT(result.any() == (num_bits != 0));
        }
        {
            const auto result = bit_a & bit_b;
            std::size_t num_bits = 0;
            for (std::size_t i = 0; i < N; i++) {
                const auto bit = (Testing::random_bits[i] == '1') && (Testing::random_bits_2[i] == '1');
                ASSERT(result[i] == bit);
                ASSERT(result.test(i) == bit);
                num_bits += bit;
            }
            ASSERT(result.count() == num_bits);
            ASSERT(result.size() == N);
            ASSERT(result.all() == (num_bits == N));
            ASSERT(result.none() == (num_bits == 0));
            ASSERT(result.any() == (num_bits != 0));
        }
    }
};

TEST() {
    apply_bitset_tests_all_sizes<bitset_binary_ops_tests>();
}
