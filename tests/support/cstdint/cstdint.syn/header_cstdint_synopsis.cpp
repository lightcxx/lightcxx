#include <cstdint>

#include "testing.h"
#include <type_traits>

TEST() {
    constexpr ::std::int8_t i8{};
    static_assert(sizeof(i8) == 1);
    static_assert(std::is_signed_v<::std::int8_t>);

    constexpr ::std::int16_t i16{};
    static_assert(sizeof(i16) == 2);
    static_assert(std::is_signed_v<::std::int16_t>);

    constexpr ::std::int32_t i32{};
    static_assert(sizeof(i32) == 4);
    static_assert(std::is_signed_v<::std::int32_t>);

    constexpr ::std::int64_t i64{};
    static_assert(sizeof(i64) == 8);
    static_assert(std::is_signed_v<::std::int64_t>);

    constexpr ::std::int_fast8_t if8{};
    static_assert(sizeof(if8) >= 1);
    static_assert(std::is_signed_v<::std::int_fast8_t>);

    constexpr ::std::int_fast16_t if16{};
    static_assert(sizeof(if16) >= 2);
    static_assert(std::is_signed_v<::std::int_fast16_t>);

    constexpr ::std::int_fast32_t if32{};
    static_assert(sizeof(if32) >= 4);
    static_assert(std::is_signed_v<::std::int_fast32_t>);

    constexpr ::std::int_fast64_t if64{};
    static_assert(sizeof(if64) >= 8);
    static_assert(std::is_signed_v<::std::int_fast64_t>);

    constexpr ::std::int_least8_t il8{};
    static_assert(sizeof(il8) >= 1);
    static_assert(std::is_signed_v<::std::int_least8_t>);

    constexpr ::std::int_least16_t il16{};
    static_assert(sizeof(il16) >= 2);
    static_assert(std::is_signed_v<::std::int_least16_t>);

    constexpr ::std::int_least32_t il32{};
    static_assert(sizeof(il32) >= 4);
    static_assert(std::is_signed_v<::std::int_least32_t>);

    constexpr ::std::int_least64_t il64{};
    static_assert(sizeof(il64) >= 8);
    static_assert(std::is_signed_v<::std::int_least64_t>);

    constexpr ::std::intptr_t ip{};
    static_assert(sizeof(ip) >= 8);
    static_assert(std::is_signed_v<::std::intptr_t>);

    constexpr ::std::intmax_t im{};
    static_assert(sizeof(im) >= 8);
    static_assert(std::is_signed_v<::std::intmax_t>);

    constexpr ::std::uint8_t ui8{};
    static_assert(sizeof(ui8) == 1);
    static_assert(std::is_unsigned_v<::std::uint8_t>);

    constexpr ::std::uint16_t ui16{};
    static_assert(sizeof(ui16) == 2);
    static_assert(std::is_unsigned_v<::std::uint16_t>);

    constexpr ::std::uint32_t ui32{};
    static_assert(sizeof(ui32) == 4);
    static_assert(std::is_unsigned_v<::std::uint32_t>);

    constexpr ::std::uint64_t ui64{};
    static_assert(sizeof(ui64) == 8);
    static_assert(std::is_unsigned_v<::std::uint64_t>);

    constexpr ::std::uint_fast8_t uif8{};
    static_assert(sizeof(uif8) >= 1);
    static_assert(std::is_unsigned_v<::std::uint_fast8_t>);

    constexpr ::std::uint_fast16_t uif16{};
    static_assert(sizeof(uif16) >= 2);
    static_assert(std::is_unsigned_v<::std::uint_fast16_t>);

    constexpr ::std::uint_fast32_t uif32{};
    static_assert(sizeof(uif32) >= 4);
    static_assert(std::is_unsigned_v<::std::uint_fast32_t>);

    constexpr ::std::uint_fast64_t uif64{};
    static_assert(sizeof(uif64) >= 8);
    static_assert(std::is_unsigned_v<::std::uint_fast64_t>);

    constexpr ::std::uint_least8_t uil8{};
    static_assert(sizeof(uil8) >= 1);
    static_assert(std::is_unsigned_v<::std::uint_least8_t>);

    constexpr ::std::uint_least16_t uil16{};
    static_assert(sizeof(uil16) >= 2);
    static_assert(std::is_unsigned_v<::std::uint_least16_t>);

    constexpr ::std::uint_least32_t uil32{};
    static_assert(sizeof(uil32) >= 4);
    static_assert(std::is_unsigned_v<::std::uint_least32_t>);

    constexpr ::std::uint_least64_t uil64{};
    static_assert(sizeof(uil64) >= 8);
    static_assert(std::is_unsigned_v<::std::uint_least64_t>);

    constexpr ::std::uintptr_t uip{};
    static_assert(sizeof(uip) >= 8);
    static_assert(std::is_unsigned_v<::std::uintptr_t>);

    constexpr ::std::uintmax_t uim{};
    static_assert(sizeof(uim) >= 8);
    static_assert(std::is_unsigned_v<::std::uintmax_t>);

    static_assert(INTMAX_MIN <= 0);
    static_assert(std::is_integral_v<decltype(INTMAX_MIN)>);
    static_assert(INTMAX_MAX > 0);
    static_assert(std::is_integral_v<decltype(INTMAX_MAX)>);
    static_assert(UINTMAX_MAX > 0);
    static_assert(std::is_integral_v<decltype(UINTMAX_MAX)>);

    static_assert(INTPTR_MIN <= 0);
    static_assert(std::is_integral_v<decltype(INTPTR_MIN)>);
    static_assert(INTPTR_MAX > 0);
    static_assert(std::is_integral_v<decltype(INTPTR_MAX)>);
    static_assert(UINTPTR_MAX > 0);
    static_assert(std::is_integral_v<decltype(UINTPTR_MAX)>);

    static_assert(PTRDIFF_MIN <= 0);
    static_assert(std::is_integral_v<decltype(PTRDIFF_MIN)>);
    static_assert(PTRDIFF_MAX > 0);
    static_assert(std::is_integral_v<decltype(PTRDIFF_MAX)>);

    static_assert(SIZE_MAX > 0);
    static_assert(std::is_integral_v<decltype(SIZE_MAX)>);

    static_assert(SIG_ATOMIC_MIN <= 0);
    static_assert(std::is_integral_v<decltype(SIG_ATOMIC_MIN)>);
    static_assert(SIG_ATOMIC_MAX > 0);
    static_assert(std::is_integral_v<decltype(SIG_ATOMIC_MAX)>);

    static_assert(WCHAR_MIN <= 0);
    static_assert(std::is_integral_v<decltype(WCHAR_MIN)>);
    static_assert(WCHAR_MAX > 0);
    static_assert(std::is_integral_v<decltype(WCHAR_MAX)>);

    static_assert(WINT_MIN <= 0);
    static_assert(std::is_integral_v<decltype(WINT_MIN)>);
    static_assert(WINT_MAX > 0);
    static_assert(std::is_integral_v<decltype(WINT_MAX)>);

    static_assert(INT8_MIN <= 0);
    static_assert(std::is_integral_v<decltype(INT8_MIN)>);
    static_assert(INT8_MAX > 0);
    static_assert(std::is_integral_v<decltype(INT8_MAX)>);
    static_assert(UINT8_MAX > 0);
    static_assert(std::is_integral_v<decltype(UINT8_MAX)>);

    static_assert(INT_FAST8_MIN <= 0);
    static_assert(std::is_integral_v<decltype(INT_FAST8_MIN)>);
    static_assert(INT_FAST8_MAX > 0);
    static_assert(std::is_integral_v<decltype(INT_FAST8_MAX)>);
    static_assert(UINT_FAST8_MAX > 0);
    static_assert(std::is_integral_v<decltype(UINT_FAST8_MAX)>);

    static_assert(INT_LEAST8_MIN <= 0);
    static_assert(std::is_integral_v<decltype(INT_LEAST8_MIN)>);
    static_assert(INT_LEAST8_MAX > 0);
    static_assert(std::is_integral_v<decltype(INT_LEAST8_MAX)>);
    static_assert(UINT_LEAST8_MAX > 0);
    static_assert(std::is_integral_v<decltype(UINT_LEAST8_MAX)>);

    static_assert(INT16_MIN <= 0);
    static_assert(std::is_integral_v<decltype(INT16_MIN)>);
    static_assert(INT16_MAX > 0);
    static_assert(std::is_integral_v<decltype(INT16_MAX)>);
    static_assert(UINT16_MAX > 0);
    static_assert(std::is_integral_v<decltype(UINT16_MAX)>);

    static_assert(INT_FAST16_MIN <= 0);
    static_assert(std::is_integral_v<decltype(INT_FAST16_MIN)>);
    static_assert(INT_FAST16_MAX > 0);
    static_assert(std::is_integral_v<decltype(INT_FAST16_MAX)>);
    static_assert(UINT_FAST16_MAX > 0);
    static_assert(std::is_integral_v<decltype(UINT_FAST16_MAX)>);

    static_assert(INT_LEAST16_MIN <= 0);
    static_assert(std::is_integral_v<decltype(INT_LEAST16_MIN)>);
    static_assert(INT_LEAST16_MAX > 0);
    static_assert(std::is_integral_v<decltype(INT_LEAST16_MAX)>);
    static_assert(UINT_LEAST16_MAX > 0);
    static_assert(std::is_integral_v<decltype(UINT_LEAST16_MAX)>);

    static_assert(INT32_MIN <= 0);
    static_assert(std::is_integral_v<decltype(INT32_MIN)>);
    static_assert(INT32_MAX > 0);
    static_assert(std::is_integral_v<decltype(INT32_MAX)>);
    static_assert(UINT32_MAX > 0);
    static_assert(std::is_integral_v<decltype(UINT32_MAX)>);

    static_assert(INT_FAST32_MIN <= 0);
    static_assert(std::is_integral_v<decltype(INT_FAST32_MIN)>);
    static_assert(INT_FAST32_MAX > 0);
    static_assert(std::is_integral_v<decltype(INT_FAST32_MAX)>);
    static_assert(UINT_FAST32_MAX > 0);
    static_assert(std::is_integral_v<decltype(UINT_FAST32_MAX)>);

    static_assert(INT_LEAST32_MIN <= 0);
    static_assert(std::is_integral_v<decltype(INT_LEAST32_MIN)>);
    static_assert(INT_LEAST32_MAX > 0);
    static_assert(std::is_integral_v<decltype(INT_LEAST32_MAX)>);
    static_assert(UINT_LEAST32_MAX > 0);
    static_assert(std::is_integral_v<decltype(UINT_LEAST32_MAX)>);

    static_assert(INT64_MIN <= 0);
    static_assert(std::is_integral_v<decltype(INT64_MIN)>);
    static_assert(INT64_MAX > 0);
    static_assert(std::is_integral_v<decltype(INT64_MAX)>);
    static_assert(UINT64_MAX > 0);
    static_assert(std::is_integral_v<decltype(UINT64_MAX)>);

    static_assert(INT_FAST64_MIN <= 0);
    static_assert(std::is_integral_v<decltype(INT_FAST64_MIN)>);
    static_assert(INT_FAST64_MAX > 0);
    static_assert(std::is_integral_v<decltype(INT_FAST64_MAX)>);
    static_assert(UINT_FAST64_MAX > 0);
    static_assert(std::is_integral_v<decltype(UINT_FAST64_MAX)>);

    static_assert(INT_LEAST64_MIN <= 0);
    static_assert(std::is_integral_v<decltype(INT_LEAST64_MIN)>);
    static_assert(INT_LEAST64_MAX > 0);
    static_assert(std::is_integral_v<decltype(INT_LEAST64_MAX)>);
    static_assert(UINT_LEAST64_MAX > 0);
    static_assert(std::is_integral_v<decltype(UINT_LEAST64_MAX)>);

    static_assert(std::is_integral_v<decltype(INTMAX_C(17))>);
    static_assert(INTMAX_C(17) == std::intmax_t(17));
    static_assert(INTMAX_C(-17) == std::intmax_t(-17));
    static_assert(std::is_integral_v<decltype(UINTMAX_C(17))>);
    static_assert(UINTMAX_C(17) == std::uintmax_t(17));

    static_assert(std::is_integral_v<decltype(INT8_C(17))>);
    static_assert(INT8_C(17) == std::int8_t(17));
    static_assert(INT8_C(-17) == std::int8_t(-17));
    static_assert(std::is_integral_v<decltype(UINT8_C(17))>);
    static_assert(UINT8_C(17) == std::uint8_t(17));

    static_assert(std::is_integral_v<decltype(INT16_C(17))>);
    static_assert(INT16_C(17) == std::int16_t(17));
    static_assert(INT16_C(-17) == std::int16_t(-17));
    static_assert(std::is_integral_v<decltype(UINT16_C(17))>);
    static_assert(UINT16_C(17) == std::uint16_t(17));

    static_assert(std::is_integral_v<decltype(INT32_C(17))>);
    static_assert(INT32_C(17) == std::int32_t(17));
    static_assert(INT32_C(-17) == std::int32_t(-17));
    static_assert(std::is_integral_v<decltype(UINT32_C(17))>);
    static_assert(UINT32_C(17) == std::uint32_t(17));

    static_assert(std::is_integral_v<decltype(INT64_C(17))>);
    static_assert(INT64_C(17) == std::int64_t(17));
    static_assert(INT64_C(-17) == std::int64_t(-17));
    static_assert(std::is_integral_v<decltype(UINT64_C(17))>);
    static_assert(UINT64_C(17) == std::uint64_t(17));
}
