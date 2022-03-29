#include <type_traits>

#include <cstdint>

template<class T, class U>
constexpr bool test_make_signed() {
    static_assert(std::is_same_v<typename std::make_signed<T>::type, U>);
    static_assert(std::is_same_v<std::make_signed_t<T>, U>);
    return true;
}

static_assert(test_make_signed<char, signed char>());
static_assert(test_make_signed<signed char, signed char>());
static_assert(test_make_signed<unsigned char, signed char>());

static_assert(test_make_signed<short, short>());
static_assert(test_make_signed<unsigned short, short>());

static_assert(test_make_signed<int, int>());
static_assert(test_make_signed<unsigned int, int>());

static_assert(test_make_signed<long, long>());
static_assert(test_make_signed<unsigned long, long>());

static_assert(test_make_signed<long long, long long>());
static_assert(test_make_signed<unsigned long long, long long>());

static_assert(test_make_signed<char8_t, int_least8_t>());
static_assert(test_make_signed<char16_t, int_least16_t>());
static_assert(test_make_signed<char32_t, int_least32_t>());
static_assert(test_make_signed<wchar_t, int_least32_t>());

enum E { a = 0 };
static_assert(test_make_signed<E, int>());

enum class EC { ac = 0 };
static_assert(test_make_signed<EC, int>());

enum class EC2 : unsigned short { ac2 = 0 };
static_assert(test_make_signed<EC2, short>());
