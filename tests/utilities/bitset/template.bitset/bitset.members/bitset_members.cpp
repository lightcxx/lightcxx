#include "bitset_testing.h"

#include "testing.h"

template<std::size_t N>
struct bitset_members_tests {
    static void test_xor_eq() {
        auto bit_a = Testing::build_bitset<N>(Testing::random_bits);
        const auto bit_b = Testing::build_bitset<N>(Testing::random_bits_2);
        auto& result = bit_a ^= bit_b;
        expect(&result == &bit_a);
        std::size_t num_set_bits = 0;
        for (std::size_t i = 0; i < N; i++) {
            const auto bit = (Testing::random_bits[i] == '1') != (Testing::random_bits_2[i] == '1');
            expect(result.test(i) == bit);
            expect(result[i] == bit);
            num_set_bits += bit;
        }
        expect(result.count() == num_set_bits);
        expect(result.size() == N);
        expect(result.all() == (num_set_bits == N));
        expect(result.none() == (num_set_bits == 0));
        expect(result.any() == (num_set_bits != 0));
    }

    static void test_and_eq() {
        auto bit_a = Testing::build_bitset<N>(Testing::random_bits);
        const auto bit_b = Testing::build_bitset<N>(Testing::random_bits_2);
        auto& result = bit_a &= bit_b;
        expect(&result == &bit_a);
        std::size_t num_set_bits = 0;
        for (std::size_t i = 0; i < N; i++) {
            const auto bit = (Testing::random_bits[i] == '1') && (Testing::random_bits_2[i] == '1');
            expect(result.test(i) == bit);
            expect(result[i] == bit);
            num_set_bits += bit;
        }
        expect(result.count() == num_set_bits);
        expect(result.size() == N);
        expect(result.all() == (num_set_bits == N));
        expect(result.none() == (num_set_bits == 0));
        expect(result.any() == (num_set_bits != 0));
    }

    static void test_or_eq() {
        auto bit_a = Testing::build_bitset<N>(Testing::random_bits);
        const auto bit_b = Testing::build_bitset<N>(Testing::random_bits_2);
        auto& result = bit_a |= bit_b;
        expect(&result == &bit_a);
        std::size_t num_set_bits = 0;
        for (std::size_t i = 0; i < N; i++) {
            const auto bit = (Testing::random_bits[i] == '1') || (Testing::random_bits_2[i] == '1');
            expect(result.test(i) == bit);
            expect(result[i] == bit);
            num_set_bits += bit;
        }
        expect(result.count() == num_set_bits);
        expect(result.size() == N);
        expect(result.all() == (num_set_bits == N));
        expect(result.none() == (num_set_bits == 0));
        expect(result.any() == (num_set_bits != 0));
    }

    static void expect_shr(const std::bitset<N>& result, std::size_t I) {
        std::size_t num_set_bits = 0;
        for (std::size_t i = 0; i < N; i++) {
            if (i < I) {
                expect(!result.test(i));
                expect(!result[i]);
            } else {
                const auto bit = Testing::random_bits[i - I] == '1';
                num_set_bits += bit;
                expect(result.test(i) == bit);
                expect(result[i] == bit);
            }
        }
        expect(result.count() == num_set_bits);
        expect(result.size() == N);
        expect(result.all() == (num_set_bits == N));
        expect(result.none() == (num_set_bits == 0));
        expect(result.any() == (num_set_bits != 0));
    }

    static void test_shr(std::size_t I) {
        auto bit_a = Testing::build_bitset<N>(Testing::random_bits);
        const auto shr_result = bit_a << I;
        expect_shr(shr_result, I);
    }

    static void test_shr_eq(std::size_t I) {
        auto bit_a = Testing::build_bitset<N>(Testing::random_bits);
        auto& shr_eq_result = bit_a <<= I;
        expect(&shr_eq_result == &bit_a);
        expect_shr(bit_a, I);
    }

    static void expect_shl(const std::bitset<N>& result, std::size_t I) {
        std::size_t num_set_bits = 0;
        for (std::size_t i = 0; i < N; i++) {
            if (I >= N - i) {
                expect(!result.test(i));
                expect(!result[i]);
            } else {
                const auto bit = Testing::random_bits[i + I] == '1';
                num_set_bits += bit;
                expect(result.test(i) == bit);
                expect(result[i] == bit);
            }
        }
        expect(result.count() == num_set_bits);
        expect(result.size() == N);
        expect(result.all() == (num_set_bits == N));
        expect(result.none() == (num_set_bits == 0));
        expect(result.any() == (num_set_bits != 0));
    }

    static void test_shl(std::size_t I) {
        auto bit_a = Testing::build_bitset<N>(Testing::random_bits);
        const auto shr_result = bit_a >> I;
        expect_shl(shr_result, I);
    }

    static void test_shl_eq(std::size_t I) {
        auto bit_a = Testing::build_bitset<N>(Testing::random_bits);
        auto& shr_eq_result = bit_a >>= I;
        expect(&shr_eq_result == &bit_a);
        expect_shl(bit_a, I);
    }

    static inline constexpr std::size_t offsets[] = {0, 1, 5, 7, 8, 9, 15, 16, 17, 31, 32, 33, 63, 64, 65, 127, 128, 129, 255, 256, 257, std::size_t(-1)};

    static void test_shift_left() {
        for (int i = 0; offsets[i] <= N; i++) {
            test_shl(offsets[i]);
            test_shl_eq(offsets[i]);
        }
        test_shl(N + 1);
        test_shl_eq(N + 1);
    }

    static void test_shift_right() {
        for (int i = 0; offsets[i] <= N; i++) {
            test_shr(offsets[i]);
            test_shr_eq(offsets[i]);
        }
        test_shr(N + 1);
        test_shr_eq(N + 1);
    }

    static void test_set_no_args() {
        auto bit_a = Testing::build_bitset<N>(Testing::random_bits);
        auto& result = bit_a.set();
        expect(&result == &bit_a);
        for (std::size_t i = 0; i < N; i++) {
            expect(bit_a.test(i));
            expect(bool(bit_a[i]));
        }
        expect(bit_a.size() == N);
        expect(bit_a.count() == N);
        expect(bit_a.any());
        expect(bit_a.all());
        expect(!bit_a.none());
    }

    static void test_set() {
        auto bit_a = Testing::build_bitset<N>(Testing::random_bits);
        for (std::size_t i = 0; i < N; i++) {
            bool bit = (Testing::random_bits_2[i] == '1');
            auto& result = bit_a.set(i, bit);
            expect(&result == &bit_a);
            for (std::size_t j = 0; j < N; j++) {
                if (j <= i) {
                    expect(bit_a.test(j) == (Testing::random_bits_2[j] == '1'));
                } else {
                    expect(bit_a.test(j) == (Testing::random_bits[j] == '1'));
                }
            }
        }

        for (std::size_t i = 0; i < N; i++) {
            auto& result = bit_a.set(i);
            expect(&result == &bit_a);
            for (std::size_t j = 0; j < N; j++) {
                if (j <= i) {
                    expect(bit_a.test(j));
                } else {
                    expect(bit_a.test(j) == (Testing::random_bits_2[j] == '1'));
                }
            }
        }

        try {
            bit_a.set(N + 1, false);
            fail();
        } catch (std::out_of_range&) {
        }

        try {
            bit_a.set(N + 1);
            fail();
        } catch (std::out_of_range&) {
        }
    }

    static void test_reset_no_args() {
        auto bit_a = Testing::build_bitset<N>(Testing::random_bits);
        auto& result = bit_a.reset();
        expect(&result == &bit_a);
        for (std::size_t i = 0; i < N; i++) {
            expect(!bit_a.test(i));
            expect(!bool(bit_a[i]));
        }
        expect(bit_a.size() == N);
        expect(bit_a.count() == 0);
        expect(!bit_a.any());
        expect(!bit_a.all());
        expect(bit_a.none());
    }

    static void test_reset() {
        auto bit_a = Testing::build_bitset<N>(Testing::random_bits);
        for (std::size_t i = 0; i < N; i++) {
            auto& result = bit_a.reset(i);
            expect(&result == &bit_a);
            for (std::size_t j = 0; j < N; j++) {
                if (j <= i) {
                    expect(!bit_a.test(j));
                } else {
                    expect(bit_a.test(j) == (Testing::random_bits[j] == '1'));
                }
            }
        }

        try {
            bit_a.reset(N + 1);
            fail();
        } catch (std::out_of_range&) {
        }
    }

    static void test_tilde() {
        const auto bit_a = Testing::build_bitset<N>(Testing::random_bits);
        auto result = ~bit_a;
        std::size_t num_set_bits = 0;
        for (std::size_t i = 0; i < N; i++) {
            const auto bit = Testing::random_bits[i] == '0';
            num_set_bits += bit;
            expect(result.test(i) == bit);
            expect(result[i] == bit);
        }
        expect(result.count() == num_set_bits);
        expect(result.size() == N);
        expect(result.all() == (num_set_bits == N));
        expect(result.none() == (num_set_bits == 0));
        expect(result.any() == (num_set_bits != 0));
    }

    static void test_flip_no_args() {
        auto bit_a = Testing::build_bitset<N>(Testing::random_bits);
        auto& result = bit_a.flip();
        expect(&result == &bit_a);
        std::size_t num_set_bits = 0;
        for (std::size_t i = 0; i < N; i++) {
            const auto bit = Testing::random_bits[i] == '0';
            num_set_bits += bit;
            expect(bit_a.test(i) == bit);
            expect(bit_a[i] == bit);
        }
        expect(bit_a.count() == num_set_bits);
        expect(bit_a.size() == N);
        expect(bit_a.all() == (num_set_bits == N));
        expect(bit_a.none() == (num_set_bits == 0));
        expect(bit_a.any() == (num_set_bits != 0));
    }

    static void test_flip() {
        auto bit_a = Testing::build_bitset<N>(Testing::random_bits);
        for (std::size_t i = 0; i < N; i++) {
            auto& result = bit_a.flip(i);
            expect(&result == &bit_a);
            for (std::size_t j = 0; j < N; j++) {
                if (j <= i) {
                    expect(bit_a.test(j) == (Testing::random_bits[j] == '0'));
                } else {
                    expect(bit_a.test(j) == (Testing::random_bits[j] == '1'));
                }
            }
        }

        try {
            bit_a.flip(N + 1);
            fail();
        } catch (std::out_of_range&) {
        }
    }

    static void test_to_integer(auto to_integer) {
        using Int = decltype(to_integer(std::bitset<N>(0ull)));

        Int mx = static_cast<Int>(-1);
        if constexpr (N < std::_Light::__char_bit * sizeof(Int)) {
            mx &= (static_cast<Int>(1) << N) - 1;
        }
        for (std::size_t i = 0; i < 50; i++) {
            if (i < mx) {
                expect(i == to_integer(std::bitset<N>(i)));
                expect(mx - i == to_integer(std::bitset<N>(mx - i)));
            }
        }
    }

    static void test_equals() {
        const auto a = Testing::build_bitset<N>(Testing::random_bits);
        const auto a_2 = Testing::build_bitset<N>(Testing::random_bits);
        const auto b = Testing::build_bitset<N>(Testing::random_bits_2);
        expect(a == a);
        expect(a == a_2);
        expect(!(a == b));

        if (N > 160) {
            const auto d1 = Testing::build_bitset<N>("0101110101101110111010100000111101010111111111100100000110110101011011010101001010001000111110100000011111000011100101101000111010101011010111111100000001111011110100000011");
            const auto d2 = Testing::build_bitset<N>("0101110101101110111010100000111101010111111111100100000110110101011011010101001010001000111110100000011111000011100101101000111010101011010111111100000001111011010100000011");
            expect(!(d1 == d2));
        }
    }

    static void test_reference() {
        auto bit_a = Testing::build_bitset<N>(Testing::random_bits);
        auto bit_b = Testing::build_bitset<N>(Testing::random_bits_2);
        for (std::size_t i = 0; i < N; i++) {
            bool bit = bit_b[i];
            auto ref = bit_a[i];
            auto& result1 = (ref = bit);
            auto& result2 = (ref = bit_b[i]);
            expect(&result1 == &ref);
            expect(&result2 == &ref);
            for (std::size_t j = 0; j < N; j++) {
                if (j <= i) {
                    expect(bool(bit_a[j]) == (Testing::random_bits_2[j] == '1'));
                    expect((~bit_a[j]) == (Testing::random_bits_2[j] == '0'));
                } else {
                    expect(bool(bit_a[j]) == (Testing::random_bits[j] == '1'));
                    expect((~bit_a[j]) == (Testing::random_bits[j] == '0'));
                }
            }
            bit_a[i].flip();
            expect(bit_a.test(i) != bit);
            bit_a[i].flip();
            expect(bit_a.test(i) == bit);
        }
    }

    static void test() {
        test_xor_eq();
        test_and_eq();
        test_or_eq();
        test_shift_left();
        test_shift_right();
        test_set_no_args();
        test_set();
        test_reset_no_args();
        test_reset();
        test_tilde();
        test_flip_no_args();
        test_flip();
        test_to_integer([](const auto& bits) -> unsigned long { return bits.to_ulong(); });
        test_to_integer([](const auto& bits) -> unsigned long long { return bits.to_ullong(); });
        //        test_to_string();  // TODO: to_string() not implemented!
        test_equals();
        test_reference();
    }
};

TEST() {
    apply_bitset_tests_all_sizes<bitset_members_tests>();
}
