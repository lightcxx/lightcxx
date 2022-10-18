#include <cstdlib>

#include "testing.h"

namespace std {

bool operator==(const div_t& d1, const div_t& d2) {
    return d1.quot == d2.quot && d1.rem == d2.rem;
}

bool operator==(const ldiv_t& d1, const ldiv_t& d2) {
    return d1.quot == d2.quot && d1.rem == d2.rem;
}

bool operator==(const lldiv_t& d1, const lldiv_t& d2) {
    return d1.quot == d2.quot && d1.rem == d2.rem;
}

}  // namespace std

TEST() {
    constexpr void* n = NULL;
    ASSERT_CT_RT(n == nullptr);
    [[maybe_unused]] const auto cur_max = MB_CUR_MAX;
    [[maybe_unused]] constexpr auto rand_max = RAND_MAX;
    [[maybe_unused]] constexpr auto exit_success = EXIT_SUCCESS;
    [[maybe_unused]] constexpr auto exit_failure = EXIT_FAILURE;
    ASSERT(EXIT_SUCCESS != EXIT_FAILURE);
    ASSERT_CT_RT(static_cast<::std::size_t>(5) == 5);

    [[maybe_unused]] const auto env_var = ::std::getenv("ENV_VAR");
    [[maybe_unused]] const auto system_lambda = []() { return ::std::system("echo ::std::system"); };

    // We don't actually want to call these, just see that they compile.
    [[maybe_unused]] auto abort_lambda = []() { ::std::abort(); };
    [[maybe_unused]] auto exit_lambda = []() {
        ::std::atexit([]() { ::std::system("echo exited"); });
        ::std::exit(10);
    };
    [[maybe_unused]] auto quick_exit_lambda = []() {
        ::std::at_quick_exit([]() { ::std::system("echo exited"); });
        ::std::quick_exit(10);
    };
    [[maybe_unused]] auto Exit_lambda = []() { ::std::_Exit(10); };

    const auto malloc_ptr = ::std::malloc(16);
    ASSERT_TYPE(void* const&, malloc_ptr);
    const auto realloc_ptr = ::std::realloc(malloc_ptr, 32);
    ASSERT_TYPE(void* const&, realloc_ptr);
    ::std::free(realloc_ptr);
    const auto calloc_ptr = ::std::calloc(16, 32);
    ASSERT_TYPE(void* const&, calloc_ptr);
    ::std::free(calloc_ptr);
    const auto aligned_alloc_ptr = ::std::aligned_alloc(4096, 313);
    ASSERT_TYPE(void* const&, aligned_alloc_ptr);
    ASSERT(reinterpret_cast<unsigned long long>(aligned_alloc_ptr) % 4096 == 0);
    ::std::free(aligned_alloc_ptr);

    ASSERT_TYPE_AND_VALUE(::std::atof("3.14"), double, 3.14);
    ASSERT_TYPE_AND_VALUE(::std::atoi("-314"), int, -314);
    ASSERT_TYPE_AND_VALUE(::std::atol("-314"), long, -314L);
    ASSERT_TYPE_AND_VALUE(::std::atoll("-314"), long long, -314LL);
    char* end = nullptr;
    ASSERT_TYPE_AND_VALUE(::std::strtof("3.0#12", &end), float, 3.0f);
    ASSERT_TYPE_AND_VALUE(::std::strtod("3.0#12", &end), double, 3.0);
    ASSERT_TYPE_AND_VALUE(::std::strtold("3.0#12", &end), long double, 3.0L);
    ASSERT_TYPE_AND_VALUE(::std::strtol("-34#12", &end, 5), long, -19L);
    ASSERT_TYPE_AND_VALUE(::std::strtoll("-34#12", &end, 5), long long, -19LL);
    ASSERT_TYPE_AND_VALUE(::std::strtoul("34#12", &end, 5), unsigned long, 19UL);
    ASSERT_TYPE_AND_VALUE(::std::strtoull("34#12", &end, 5), unsigned long long, 19ULL);

    const char8_t* s = u8"z\u00df\u6c34\u0001f34c";
    ::std::mblen(reinterpret_cast<const char*>(s), 11);
    ::std::mbtowc(static_cast<wchar_t*>(nullptr), reinterpret_cast<const char*>(s), 11);
    char* characters = static_cast<char*>(::std::malloc(std::size_t(MB_CUR_MAX)));
    ::std::wctomb(characters, L'A');
    const char* multibyte_string = "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9f\x8d\x8c";
    wchar_t wide_string[20];
    ::std::mbstowcs(wide_string, multibyte_string, 20);
    char multibyte_string_copy[20];
    ::std::wcstombs(multibyte_string_copy, wide_string, 20);
    ::std::free(characters);

    const auto cmp = [](const void* a, const void* b) -> int { return *(static_cast<const int*>(a)) - *(static_cast<const int*>(b)); };

    int a[] = {5, 2, 4, 1, 3};
    ::std::qsort(a, 5, sizeof(int), cmp);
    ASSERT(a[0] == 1 && a[1] == 2 && a[2] == 3 && a[3] == 4 && a[4] == 5);

    int key = 2;
    auto ptr = ::std::bsearch(&key, a, 5, sizeof(int), cmp);
    ASSERT(*(static_cast<int*>(ptr)) == 2);
    ASSERT(((static_cast<int*>(ptr)) - (static_cast<int*>(a))) == 1);
    key = 16;
    ptr = ::std::bsearch(&key, a, 5, sizeof(int), cmp);
    ASSERT(ptr == nullptr);

    ::std::srand(5);
    auto r = ::std::rand();
    ::std::srand(5);
    auto r2 = ::std::rand();
    ASSERT_TYPE_AND_VALUE(r, int&, r2);

    auto abs_result = ::std::abs(-4);
    ASSERT_TYPE_AND_VALUE(abs_result, int&, 4);

    auto abs_result_l = ::std::abs(-4L);
    ASSERT_TYPE_AND_VALUE(abs_result_l, long&, 4);

    auto abs_result_ll = ::std::abs(-4LL);
    ASSERT_TYPE_AND_VALUE(abs_result_ll, long long&, 4);

    auto abs_result_f = ::std::abs(-4.0F);
    ASSERT_TYPE_AND_VALUE(abs_result_f, float&, 4.0F);

    auto abs_result_d = ::std::abs(-4.0);
    ASSERT_TYPE_AND_VALUE(abs_result_d, double&, 4.0);

    auto abs_result_ld = ::std::abs(-4.0L);
    ASSERT_TYPE_AND_VALUE(abs_result_ld, long double&, 4.0L);

    auto labs_result = ::std::labs(-4);
    ASSERT_TYPE_AND_VALUE(labs_result, long&, 4);

    auto llabs_result = ::std::llabs(-4);
    ASSERT_TYPE_AND_VALUE(llabs_result, long long&, 4);

    auto div_result = ::std::div(7, 3);
    ASSERT_TYPE_AND_VALUE(div_result, ::std::div_t&, (::std::div_t{.quot = 2, .rem = 1}));

    auto div_result_l = ::std::div(7L, 3L);
    ASSERT_TYPE_AND_VALUE(div_result_l, ::std::ldiv_t&, (::std::ldiv_t{.quot = 2, .rem = 1}));

    auto div_result_ll = ::std::div(7LL, 3LL);
    ASSERT_TYPE_AND_VALUE(div_result_ll, ::std::lldiv_t&, (::std::lldiv_t{.quot = 2, .rem = 1}));

    auto ldiv_result = ::std::ldiv(7L, 3L);
    ASSERT_TYPE_AND_VALUE(ldiv_result, ::std::ldiv_t&, (::std::ldiv_t{.quot = 2, .rem = 1}));

    auto lldiv_result = ::std::lldiv(7LL, 3LL);
    ASSERT_TYPE_AND_VALUE(lldiv_result, ::std::lldiv_t&, (::std::lldiv_t{.quot = 2, .rem = 1}));
}
