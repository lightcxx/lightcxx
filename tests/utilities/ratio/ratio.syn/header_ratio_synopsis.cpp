#include "../test_ratio_helpers.h"

static_assert(std::ratio<3, 4>::num == 3 && std::ratio<3, 4>::den == 4);
static_assert(std::is_same_v<std::ratio<3, 4>, std::ratio<3, 4>::type>);

static_assert(is_ratio<std::ratio_add<std::ratio<13>, std::ratio<2, 5>>>);
static_assert(is_ratio<std::ratio_subtract<std::ratio<13>, std::ratio<2, 5>>>);
static_assert(is_ratio<std::ratio_multiply<std::ratio<13>, std::ratio<2, 5>>>);
static_assert(is_ratio<std::ratio_divide<std::ratio<13>, std::ratio<2, 5>>>);

static_assert(std::ratio_equal<std::ratio<3, 4>, std::ratio<6, 8>>::value);
static_assert(std::ratio_equal_v<std::ratio<3, 4>, std::ratio<6, 8>>);

static_assert(std::ratio_not_equal<std::ratio<3, 4>, std::ratio<3, 8>>::value);
static_assert(std::ratio_not_equal_v<std::ratio<3, 4>, std::ratio<3, 8>>);

static_assert(std::ratio_less<std::ratio<3, 4>, std::ratio<7, 8>>::value);
static_assert(std::ratio_less_v<std::ratio<3, 4>, std::ratio<7, 8>>);

static_assert(std::ratio_less_equal<std::ratio<3, 4>, std::ratio<7, 8>>::value);
static_assert(std::ratio_less_equal_v<std::ratio<3, 4>, std::ratio<7, 8>>);

static_assert(std::ratio_greater<std::ratio<3, 4>, std::ratio<3, 8>>::value);
static_assert(std::ratio_greater_v<std::ratio<3, 4>, std::ratio<3, 8>>);

static_assert(std::ratio_greater_equal<std::ratio<3, 4>, std::ratio<3, 8>>::value);
static_assert(std::ratio_greater_equal_v<std::ratio<3, 4>, std::ratio<3, 8>>);

static_assert(std::atto::num == 1);
static_assert(std::atto::den == 1'000'000'000'000'000'000);

static_assert(std::femto::num == 1);
static_assert(std::femto::den == 1'000'000'000'000'000);

static_assert(std::pico::num == 1);
static_assert(std::pico::den == 1'000'000'000'000);

static_assert(std::nano::num == 1);
static_assert(std::nano::den == 1'000'000'000);

static_assert(std::micro::num == 1);
static_assert(std::micro::den == 1'000'000);

static_assert(std::milli::num == 1);
static_assert(std::milli::den == 1'000);

static_assert(std::centi::num == 1);
static_assert(std::centi::den == 100);

static_assert(std::deci::num == 1);
static_assert(std::deci::den == 10);

static_assert(std::deca::num == 10);
static_assert(std::deca::den == 1);

static_assert(std::hecto::num == 100);
static_assert(std::hecto::den == 1);

static_assert(std::kilo::num == 1'000);
static_assert(std::kilo::den == 1);

static_assert(std::mega::num == 1'000'000);
static_assert(std::mega::den == 1);

static_assert(std::giga::num == 1'000'000'000);
static_assert(std::giga::den == 1);

static_assert(std::tera::num == 1'000'000'000'000);
static_assert(std::tera::den == 1);

static_assert(std::peta::num == 1'000'000'000'000'000);
static_assert(std::peta::den == 1);

static_assert(std::exa::num == 1'000'000'000'000'000'000);
static_assert(std::exa::den == 1);
