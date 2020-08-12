#include <limits>

#include "testing/test.h"

struct Custom {
    [[maybe_unused]] int x;
    [[maybe_unused]] int y;
};

void Testing::run() {
    [[maybe_unused]] constexpr ::std::float_round_style fr_style{};
    [[maybe_unused]] constexpr ::std::float_denorm_style fd_style{};

    [[maybe_unused]] constexpr ::std::numeric_limits<Custom> custom_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<const Custom> c_custom_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<volatile Custom> v_custom_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<const volatile Custom> cv_custom_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<bool> bool_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<char> char_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<signed char> schar_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<unsigned char> uchar_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<char8_t> char8_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<char16_t> char16_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<char32_t> char32_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<wchar_t> wchar_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<short> short_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<int> int_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<long> long_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<long long> longlong_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<unsigned short> ushort_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<unsigned int> uint_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<unsigned long> ulong_limits{};
    [[maybe_unused]] constexpr ::std::numeric_limits<unsigned long long> ulonglong_limits{};
}
