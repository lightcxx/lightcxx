#include <limits>

#include "testing.h"

struct Custom {
    int x;
    int y;
};

TEST() {
    constexpr ::std::float_round_style fr_style{};
    constexpr ::std::float_denorm_style fd_style{};

    constexpr ::std::numeric_limits<Custom> custom_limits;
    constexpr ::std::numeric_limits<const Custom> c_custom_limits;
    constexpr ::std::numeric_limits<volatile Custom> v_custom_limits;
    constexpr ::std::numeric_limits<const volatile Custom> cv_custom_limits;
    constexpr ::std::numeric_limits<bool> bool_limits;
    constexpr ::std::numeric_limits<char> char_limits;
    constexpr ::std::numeric_limits<signed char> schar_limits;
    constexpr ::std::numeric_limits<unsigned char> uchar_limits;
    constexpr ::std::numeric_limits<char8_t> char8_limits;
    constexpr ::std::numeric_limits<char16_t> char16_limits;
    constexpr ::std::numeric_limits<char32_t> char32_limits;
    constexpr ::std::numeric_limits<wchar_t> wchar_limits;
    constexpr ::std::numeric_limits<short> short_limits;
    constexpr ::std::numeric_limits<int> int_limits;
    constexpr ::std::numeric_limits<long> long_limits;
    constexpr ::std::numeric_limits<long long> longlong_limits;
    constexpr ::std::numeric_limits<unsigned short> ushort_limits;
    constexpr ::std::numeric_limits<unsigned int> uint_limits;
    constexpr ::std::numeric_limits<unsigned long> ulong_limits;
    constexpr ::std::numeric_limits<unsigned long long> ulonglong_limits;
}
