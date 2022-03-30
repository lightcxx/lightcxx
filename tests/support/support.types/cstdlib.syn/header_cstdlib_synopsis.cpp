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
    expect_ct_and_rt(n == nullptr);
    [[maybe_unused]] const auto cur_max = MB_CUR_MAX;
    [[maybe_unused]] constexpr auto rand_max = RAND_MAX;
    [[maybe_unused]] constexpr auto exit_success = EXIT_SUCCESS;
    [[maybe_unused]] constexpr auto exit_failure = EXIT_FAILURE;
    expect(EXIT_SUCCESS != EXIT_FAILURE);
    expect_ct_and_rt((::std::size_t)5 == 5);

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
    expect_type(void* const&, malloc_ptr);
    const auto realloc_ptr = ::std::realloc(malloc_ptr, 32);
    expect_type(void* const&, realloc_ptr);
    ::std::free(realloc_ptr);
    const auto calloc_ptr = ::std::calloc(16, 32);
    expect_type(void* const&, calloc_ptr);
    ::std::free(calloc_ptr);
    const auto aligned_alloc_ptr = ::std::aligned_alloc(4096, 313);
    expect_type(void* const&, aligned_alloc_ptr);
    expect(((unsigned long long)aligned_alloc_ptr) % 4096 == 0);
    ::std::free(aligned_alloc_ptr);

    expect_type_and_value(::std::atof("3.14"), double, 3.14);
    expect_type_and_value(::std::atoi("-314"), int, -314);
    expect_type_and_value(::std::atol("-314"), long, -314L);
    expect_type_and_value(::std::atoll("-314"), long long, -314LL);
    char* end = nullptr;
    expect_type_and_value(::std::strtof("3.0#12", &end), float, 3.0);
    expect_type_and_value(::std::strtod("3.0#12", &end), double, 3.0);
    expect_type_and_value(::std::strtold("3.0#12", &end), long double, 3.0);
    expect_type_and_value(::std::strtol("-34#12", &end, 5), long, -19L);
    expect_type_and_value(::std::strtoll("-34#12", &end, 5), long long, -19LL);
    expect_type_and_value(::std::strtoul("34#12", &end, 5), unsigned long, 19UL);
    expect_type_and_value(::std::strtoull("34#12", &end, 5), unsigned long long, 19ULL);

    const char8_t* s = u8"z\u00df\u6c34\u0001f34c";
    ::std::mblen((const char*)s, 11);
    ::std::mbtowc((wchar_t*)nullptr, (const char*)s, 11);
    char* characters = (char*)::std::malloc(MB_CUR_MAX);
    ::std::wctomb(characters, L'A');
    const char* multibyte_string = "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9f\x8d\x8c";
    wchar_t wide_string[20];
    ::std::mbstowcs(wide_string, multibyte_string, 20);
    char multibyte_string_copy[20];
    ::std::wcstombs(multibyte_string_copy, wide_string, 20);
    ::std::free(characters);

    int a[] = {5, 2, 4, 1, 3};
    ::std::qsort(a, 5, sizeof(int), [](const void* a, const void* b) { return *((int*)a) - *((int*)b); });
    expect(a[0] == 1 && a[1] == 2 && a[2] == 3 && a[3] == 4 && a[4] == 5);

    int key = 2;
    auto ptr = ::std::bsearch(&key, a, 5, sizeof(int), [](const void* a, const void* b) { return *((int*)a) - *((int*)b); });
    expect(*((int*)ptr) == 2);
    expect(((int*)ptr - (int*)a) == 1);
    key = 16;
    ptr = ::std::bsearch(&key, a, 5, sizeof(int), [](const void* a, const void* b) { return *((int*)a) - *((int*)b); });
    expect(ptr == nullptr);

    ::std::srand(5);
    auto r = ::std::rand();
    ::std::srand(5);
    auto r2 = ::std::rand();
    expect_type_and_value(r, int&, r2);

    auto abs_result = ::std::abs(-4);
    expect_type_and_value(abs_result, int&, 4);

    auto abs_result_l = ::std::abs(-4L);
    expect_type_and_value(abs_result_l, long&, 4);

    auto abs_result_ll = ::std::abs(-4LL);
    expect_type_and_value(abs_result_ll, long long&, 4);

    auto abs_result_f = ::std::abs(-4.0F);
    expect_type_and_value(abs_result_f, float&, 4.0F);

    auto abs_result_d = ::std::abs(-4.0);
    expect_type_and_value(abs_result_d, double&, 4.0);

    auto abs_result_ld = ::std::abs(-4.0L);
    expect_type_and_value(abs_result_ld, long double&, 4.0L);

    auto labs_result = ::std::labs(-4);
    expect_type_and_value(labs_result, long&, 4);

    auto llabs_result = ::std::llabs(-4);
    expect_type_and_value(llabs_result, long long&, 4);

    auto div_result = ::std::div(7, 3);
    expect_type_and_value(div_result, ::std::div_t&, (::std::div_t{.quot = 2, .rem = 1}));

    auto div_result_l = ::std::div(7L, 3L);
    expect_type_and_value(div_result_l, ::std::ldiv_t&, (::std::ldiv_t{.quot = 2, .rem = 1}));

    auto div_result_ll = ::std::div(7LL, 3LL);
    expect_type_and_value(div_result_ll, ::std::lldiv_t&, (::std::lldiv_t{.quot = 2, .rem = 1}));

    auto ldiv_result = ::std::ldiv(7L, 3L);
    expect_type_and_value(ldiv_result, ::std::ldiv_t&, (::std::ldiv_t{.quot = 2, .rem = 1}));

    auto lldiv_result = ::std::lldiv(7LL, 3LL);
    expect_type_and_value(lldiv_result, ::std::lldiv_t&, (::std::lldiv_t{.quot = 2, .rem = 1}));
}
