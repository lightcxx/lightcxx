#include <type_traits>

#include <cstdint>

template<class T, class U>
constexpr bool test_make_unsigned() {
    static_assert(std::is_same_v<typename std::make_unsigned<T>::type, U>);
    static_assert(std::is_same_v<std::make_unsigned_t<T>, U>);
    return true;
}

static_assert(test_make_unsigned<char, unsigned char>());
static_assert(test_make_unsigned<signed char, unsigned char>());
static_assert(test_make_unsigned<unsigned char, unsigned char>());

static_assert(test_make_unsigned<short, unsigned short>());
static_assert(test_make_unsigned<unsigned short, unsigned short>());

static_assert(test_make_unsigned<int, unsigned int>());
static_assert(test_make_unsigned<unsigned int, unsigned int>());

static_assert(test_make_unsigned<long, unsigned long>());
static_assert(test_make_unsigned<unsigned long, unsigned long>());

static_assert(test_make_unsigned<long long, unsigned long long>());
static_assert(test_make_unsigned<unsigned long long, unsigned long long>());

static_assert(test_make_unsigned<char8_t, uint_least8_t>());
static_assert(test_make_unsigned<char16_t, uint_least16_t>());
static_assert(test_make_unsigned<char32_t, uint_least32_t>());
static_assert(test_make_unsigned<wchar_t, uint_least32_t>());

enum E { a = 0 };
static_assert(test_make_unsigned<E, unsigned int>());

enum class EC { ac = 0 };
static_assert(test_make_unsigned<EC, unsigned int>());

enum class EC2 : unsigned short { ac2 = 0 };
static_assert(test_make_unsigned<EC2, unsigned short>());
