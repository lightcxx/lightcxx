#include <cstdint>

#include "testing/test.h"

#ifndef INT_FAST8_MIN
#error "INT_FAST8_MIN is not defined."
#endif

#ifndef INT_FAST16_MIN
#error "INT_FAST16_MIN is not defined."
#endif

#ifndef INT_FAST32_MIN
#error "INT_FAST32_MIN is not defined."
#endif

#ifndef INT_FAST64_MIN
#error "INT_FAST64_MIN is not defined."
#endif

#ifndef INT_LEAST8_MIN
#error "INT_LEAST8_MIN is not defined."
#endif

#ifndef INT_LEAST16_MIN
#error "INT_LEAST16_MIN is not defined."
#endif

#ifndef INT_LEAST32_MIN
#error "INT_LEAST32_MIN is not defined."
#endif

#ifndef INT_LEAST64_MIN
#error "INT_LEAST64_MIN is not defined."
#endif

#ifndef INT_FAST8_MAX
#error "INT_FAST8_MAX is not defined."
#endif

#ifndef INT_FAST16_MAX
#error "INT_FAST16_MAX is not defined."
#endif

#ifndef INT_FAST32_MAX
#error "INT_FAST32_MAX is not defined."
#endif

#ifndef INT_FAST64_MAX
#error "INT_FAST64_MAX is not defined."
#endif

#ifndef INT_LEAST8_MAX
#error "INT_LEAST8_MAX is not defined."
#endif

#ifndef INT_LEAST16_MAX
#error "INT_LEAST16_MAX is not defined."
#endif

#ifndef INT_LEAST32_MAX
#error "INT_LEAST32_MAX is not defined."
#endif

#ifndef INT_LEAST64_MAX
#error "INT_LEAST64_MAX is not defined."
#endif

#ifndef UINT_FAST8_MAX
#error "UINT_FAST8_MAX is not defined."
#endif

#ifndef UINT_FAST16_MAX
#error "UINT_FAST16_MAX is not defined."
#endif

#ifndef UINT_FAST32_MAX
#error "UINT_FAST32_MAX is not defined."
#endif

#ifndef UINT_FAST64_MAX
#error "UINT_FAST64_MAX is not defined."
#endif

#ifndef UINT_LEAST8_MAX
#error "UINT_LEAST8_MAX is not defined."
#endif

#ifndef UINT_LEAST16_MAX
#error "UINT_LEAST16_MAX is not defined."
#endif

#ifndef UINT_LEAST32_MAX
#error "UINT_LEAST32_MAX is not defined."
#endif

#ifndef UINT_LEAST64_MAX
#error "UINT_LEAST64_MAX is not defined."
#endif

#ifndef INTMAX_MIN
#error "INTMAX_MIN is not defined."
#endif

#ifndef INTPTR_MIN
#error "INTPTR_MIN is not defined."
#endif

#ifndef INTMAX_MAX
#error "INTMAX_MAX is not defined."
#endif

#ifndef INTPTR_MAX
#error "INTPTR_MAX is not defined."
#endif

#ifndef UINTMAX_MAX
#error "UINTMAX_MAX is not defined."
#endif

#ifndef UINTPTR_MAX
#error "UINTPTR_MAX is not defined."
#endif

#ifndef PTRDIFF_MIN
#error "PTRDIFF_MIN is not defined."
#endif

#ifndef PTRDIFF_MAX
#error "PTRDIFF_MAX is not defined."
#endif

#ifndef SIG_ATOMIC_MIN
#error "SIG_ATOMIC_MIN is not defined."
#endif

#ifndef SIG_ATOMIC_MAX
#error "SIG_ATOMIC_MAX is not defined."
#endif

#ifndef WCHAR_MIN
#error "WCHAR_MIN is not defined."
#endif

#ifndef WCHAR_MAX
#error "WCHAR_MAX is not defined."
#endif

#ifndef WINT_MIN
#error "WINT_MIN is not defined."
#endif

#ifndef WINT_MAX
#error "WINT_MAX is not defined."
#endif

#ifndef SIZE_MAX
#error "SIZE_MAX is not defined."
#endif

#ifndef INT8_C
#error "INT8_C is not defined."
#endif

#ifndef INT16_C
#error "INT16_C is not defined."
#endif

#ifndef INT32_C
#error "INT32_C is not defined."
#endif

#ifndef INT64_C
#error "INT64_C is not defined."
#endif

#ifndef INTMAX_C
#error "INTMAX_C is not defined."
#endif

#ifndef UINT8_C
#error "UINT8_C is not defined."
#endif

#ifndef UINT16_C
#error "UINT16_C is not defined."
#endif

#ifndef UINT32_C
#error "UINT32_C is not defined."
#endif

#ifndef UINT64_C
#error "UINT64_C is not defined."
#endif

#ifndef UINTMAX_C
#error "UINTMAX_C is not defined."
#endif

void Testing::run() {
    [[maybe_unused]] constexpr ::std::int8_t i8{};
    static_assert(sizeof(i8) == 1);
    static_assert(Testing::IsSignedIntegerType<::std::int8_t>);

    [[maybe_unused]] constexpr ::std::int16_t i16{};
    static_assert(sizeof(i16) == 2);
    static_assert(Testing::IsSignedIntegerType<::std::int16_t>);

    [[maybe_unused]] constexpr ::std::int32_t i32{};
    static_assert(sizeof(i32) == 4);
    static_assert(Testing::IsSignedIntegerType<::std::int32_t>);

    [[maybe_unused]] constexpr ::std::int64_t i64{};
    static_assert(sizeof(i64) == 8);
    static_assert(Testing::IsSignedIntegerType<::std::int64_t>);

    [[maybe_unused]] constexpr ::std::int_fast8_t if8{};
    static_assert(sizeof(if8) >= 1);
    static_assert(Testing::IsSignedIntegerType<::std::int_fast8_t>);

    [[maybe_unused]] constexpr ::std::int_fast16_t if16{};
    static_assert(sizeof(if16) >= 2);
    static_assert(Testing::IsSignedIntegerType<::std::int_fast16_t>);

    [[maybe_unused]] constexpr ::std::int_fast32_t if32{};
    static_assert(sizeof(if32) >= 4);
    static_assert(Testing::IsSignedIntegerType<::std::int_fast32_t>);

    [[maybe_unused]] constexpr ::std::int_fast64_t if64{};
    static_assert(sizeof(if64) >= 8);
    static_assert(Testing::IsSignedIntegerType<::std::int_fast64_t>);

    [[maybe_unused]] constexpr ::std::int_least8_t il8{};
    static_assert(sizeof(il8) >= 1);
    static_assert(Testing::IsSignedIntegerType<::std::int_least8_t>);

    [[maybe_unused]] constexpr ::std::int_least16_t il16{};
    static_assert(sizeof(il16) >= 2);
    static_assert(Testing::IsSignedIntegerType<::std::int_least16_t>);

    [[maybe_unused]] constexpr ::std::int_least32_t il32{};
    static_assert(sizeof(il32) >= 4);
    static_assert(Testing::IsSignedIntegerType<::std::int_least32_t>);

    [[maybe_unused]] constexpr ::std::int_least64_t il64{};
    static_assert(sizeof(il64) >= 8);
    static_assert(Testing::IsSignedIntegerType<::std::int_least64_t>);

    [[maybe_unused]] constexpr ::std::intptr_t ip{};
    static_assert(sizeof(ip) >= 8);
    static_assert(Testing::IsSignedIntegerType<::std::intptr_t>);

    [[maybe_unused]] constexpr ::std::intmax_t im{};
    static_assert(sizeof(im) >= 8);
    static_assert(Testing::IsSignedIntegerType<::std::intmax_t>);

    [[maybe_unused]] constexpr ::std::uint8_t ui8{};
    static_assert(sizeof(ui8) == 1);
    static_assert(Testing::IsUnsignedIntegerType<::std::uint8_t>);

    [[maybe_unused]] constexpr ::std::uint16_t ui16{};
    static_assert(sizeof(ui16) == 2);
    static_assert(Testing::IsUnsignedIntegerType<::std::uint16_t>);

    [[maybe_unused]] constexpr ::std::uint32_t ui32{};
    static_assert(sizeof(ui32) == 4);
    static_assert(Testing::IsUnsignedIntegerType<::std::uint32_t>);

    [[maybe_unused]] constexpr ::std::uint64_t ui64{};
    static_assert(sizeof(ui64) == 8);
    static_assert(Testing::IsUnsignedIntegerType<::std::uint64_t>);

    [[maybe_unused]] constexpr ::std::uint_fast8_t uif8{};
    static_assert(sizeof(uif8) >= 1);
    static_assert(Testing::IsUnsignedIntegerType<::std::uint_fast8_t>);

    [[maybe_unused]] constexpr ::std::uint_fast16_t uif16{};
    static_assert(sizeof(uif16) >= 2);
    static_assert(Testing::IsUnsignedIntegerType<::std::uint_fast16_t>);

    [[maybe_unused]] constexpr ::std::uint_fast32_t uif32{};
    static_assert(sizeof(uif32) >= 4);
    static_assert(Testing::IsUnsignedIntegerType<::std::uint_fast32_t>);

    [[maybe_unused]] constexpr ::std::uint_fast64_t uif64{};
    static_assert(sizeof(uif64) >= 8);
    static_assert(Testing::IsUnsignedIntegerType<::std::uint_fast64_t>);

    [[maybe_unused]] constexpr ::std::uint_least8_t uil8{};
    static_assert(sizeof(uil8) >= 1);
    static_assert(Testing::IsUnsignedIntegerType<::std::uint_least8_t>);

    [[maybe_unused]] constexpr ::std::uint_least16_t uil16{};
    static_assert(sizeof(uil16) >= 2);
    static_assert(Testing::IsUnsignedIntegerType<::std::uint_least16_t>);

    [[maybe_unused]] constexpr ::std::uint_least32_t uil32{};
    static_assert(sizeof(uil32) >= 4);
    static_assert(Testing::IsUnsignedIntegerType<::std::uint_least32_t>);

    [[maybe_unused]] constexpr ::std::uint_least64_t uil64{};
    static_assert(sizeof(uil64) >= 8);
    static_assert(Testing::IsUnsignedIntegerType<::std::uint_least64_t>);

    [[maybe_unused]] constexpr ::std::uintptr_t uip{};
    static_assert(sizeof(uip) >= 8);
    static_assert(Testing::IsUnsignedIntegerType<::std::uintptr_t>);

    [[maybe_unused]] constexpr ::std::uintmax_t uim{};
    static_assert(sizeof(uim) >= 8);
    static_assert(Testing::IsUnsignedIntegerType<::std::uintmax_t>);
}
