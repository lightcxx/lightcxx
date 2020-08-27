#include <cstddef>

#include "testing/test.h"

TEST() {
#define TEST_BYTE_OPS_WITH_VALID_INT_TYPE(T)                                                       \
    STATIC_EXPECT(::std::byte{8} == ::std::byte{4} << (T)1, "<< (" #T ")");                        \
    STATIC_EXPECT(                                                                                 \
      ::std::byte{8} ==                                                                            \
        [] {                                                                                       \
            ::std::byte b{4};                                                                      \
            b <<= (T)1;                                                                            \
            return b;                                                                              \
        }(),                                                                                       \
      "<<= (" #T ")");                                                                             \
    STATIC_EXPECT(::std::byte{8} == ::std::byte{16} >> (T)1, ">> (" #T ")");                       \
    STATIC_EXPECT(                                                                                 \
      ::std::byte{8} ==                                                                            \
        [] {                                                                                       \
            ::std::byte b{16};                                                                     \
            b >>= (T)1;                                                                            \
            return b;                                                                              \
        }(),                                                                                       \
      ">>= (" #T ")");

#define TEST_BYTE_OPS_AND_TO_INTEGER_WITH_VALID_INT_TYPE_ALL_CV_VARIANTS(T)                        \
    TEST_BYTE_OPS_WITH_VALID_INT_TYPE(T);                                                          \
    TEST_BYTE_OPS_WITH_VALID_INT_TYPE(T const);                                                    \
    TEST_BYTE_OPS_WITH_VALID_INT_TYPE(T volatile);                                                 \
    TEST_BYTE_OPS_WITH_VALID_INT_TYPE(T const volatile);                                           \
    STATIC_EXPECT(::std::to_integer<T>(::std::byte{8}) == (T)8, "to_integer<" #T ">")

    TEST_BYTE_OPS_AND_TO_INTEGER_WITH_VALID_INT_TYPE_ALL_CV_VARIANTS(bool);
    TEST_BYTE_OPS_AND_TO_INTEGER_WITH_VALID_INT_TYPE_ALL_CV_VARIANTS(char);
    TEST_BYTE_OPS_AND_TO_INTEGER_WITH_VALID_INT_TYPE_ALL_CV_VARIANTS(unsigned char);
    TEST_BYTE_OPS_AND_TO_INTEGER_WITH_VALID_INT_TYPE_ALL_CV_VARIANTS(short);
    TEST_BYTE_OPS_AND_TO_INTEGER_WITH_VALID_INT_TYPE_ALL_CV_VARIANTS(unsigned short);
    TEST_BYTE_OPS_AND_TO_INTEGER_WITH_VALID_INT_TYPE_ALL_CV_VARIANTS(int);
    TEST_BYTE_OPS_AND_TO_INTEGER_WITH_VALID_INT_TYPE_ALL_CV_VARIANTS(unsigned int);
    TEST_BYTE_OPS_AND_TO_INTEGER_WITH_VALID_INT_TYPE_ALL_CV_VARIANTS(long);
    TEST_BYTE_OPS_AND_TO_INTEGER_WITH_VALID_INT_TYPE_ALL_CV_VARIANTS(unsigned long);
    TEST_BYTE_OPS_AND_TO_INTEGER_WITH_VALID_INT_TYPE_ALL_CV_VARIANTS(long long);
    TEST_BYTE_OPS_AND_TO_INTEGER_WITH_VALID_INT_TYPE_ALL_CV_VARIANTS(unsigned long long);
    TEST_BYTE_OPS_AND_TO_INTEGER_WITH_VALID_INT_TYPE_ALL_CV_VARIANTS(char8_t);
    TEST_BYTE_OPS_AND_TO_INTEGER_WITH_VALID_INT_TYPE_ALL_CV_VARIANTS(char16_t);
    TEST_BYTE_OPS_AND_TO_INTEGER_WITH_VALID_INT_TYPE_ALL_CV_VARIANTS(char32_t);
    TEST_BYTE_OPS_AND_TO_INTEGER_WITH_VALID_INT_TYPE_ALL_CV_VARIANTS(wchar_t);

    for (int i = 0; i <= 255; i++) {
        ::std::byte bi{(unsigned char)i};
        for (int j = 0; j <= 255; j++) {
            ::std::byte bj{(unsigned char)j};
            expect((bi | bj) == ::std::byte{(unsigned char)(i | j)}, "|");
            expect((bi & bj) == ::std::byte{(unsigned char)(i & j)}, "&");
            expect((bi ^ bj) == ::std::byte{(unsigned char)(i ^ j)}, "^");
            ::std::byte aux;
            aux = bi;
            aux |= bj;
            expect(aux == ::std::byte{(unsigned char)(i | j)}, "|=");
            aux = bi;
            aux &= bj;
            expect(aux == ::std::byte{(unsigned char)(i & j)}, "&=");
            aux = bi;
            aux ^= bj;
            expect(aux == ::std::byte{(unsigned char)(i ^ j)}, "^=");
        }
        expect(~bi == ::std::byte{(unsigned char)(~i)}, "~");
    }
}
