#include <cstddef>

#include "testing.h"

template<class T>
void test_byte_ops_with_valid_int_type() {
    expect_ct_and_rt(::std::byte{8} == ::std::byte{4} << static_cast<T>(1));
    expect_ct_and_rt(::std::byte{8} == [] {
        ::std::byte b{4};
        b <<= static_cast<T>(1);
        return b;
    }());
    expect_ct_and_rt(::std::byte{8} == ::std::byte{16} >> static_cast<T>(1));
    expect_ct_and_rt(::std::byte{8} == [] {
        ::std::byte b{16};
        b >>= static_cast<T>(1);
        return b;
    }());
    expect_ct_and_rt(::std::to_integer<T>(::std::byte{8}) == static_cast<T>(8));
}

TEST() {
    test_byte_ops_with_valid_int_type<bool>();
    test_byte_ops_with_valid_int_type<char>();
    test_byte_ops_with_valid_int_type<unsigned char>();
    test_byte_ops_with_valid_int_type<short>();
    test_byte_ops_with_valid_int_type<unsigned short>();
    test_byte_ops_with_valid_int_type<int>();
    test_byte_ops_with_valid_int_type<unsigned int>();
    test_byte_ops_with_valid_int_type<long>();
    test_byte_ops_with_valid_int_type<unsigned long>();
    test_byte_ops_with_valid_int_type<long long>();
    test_byte_ops_with_valid_int_type<unsigned long long>();
    test_byte_ops_with_valid_int_type<char8_t>();
    test_byte_ops_with_valid_int_type<char16_t>();
    test_byte_ops_with_valid_int_type<char32_t>();
    test_byte_ops_with_valid_int_type<wchar_t>();

    for (int i = 0; i <= 255; i++) {
        ::std::byte bi{static_cast<unsigned char>(i)};
        for (int j = 0; j <= 255; j++) {
            ::std::byte bj{static_cast<unsigned char>(j)};
            expect((bi | bj) == ::std::byte{static_cast<unsigned char>(i | j)});
            expect((bi & bj) == ::std::byte{static_cast<unsigned char>(i & j)});
            expect((bi ^ bj) == ::std::byte{static_cast<unsigned char>(i ^ j)});
            ::std::byte aux;
            aux = bi;
            aux |= bj;
            expect(aux == ::std::byte{static_cast<unsigned char>(i | j)});
            aux = bi;
            aux &= bj;
            expect(aux == ::std::byte{static_cast<unsigned char>(i & j)});
            aux = bi;
            aux ^= bj;
            expect(aux == ::std::byte{static_cast<unsigned char>(i ^ j)});
        }
        expect(~bi == ::std::byte{static_cast<unsigned char>(~i)});
    }
}
