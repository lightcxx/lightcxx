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

static_assert(std::is_object_v<std::atto>);
static_assert(std::is_object_v<std::femto>);
static_assert(std::is_object_v<std::pico>);
static_assert(std::is_object_v<std::nano>);
static_assert(std::is_object_v<std::micro>);
static_assert(std::is_object_v<std::milli>);
static_assert(std::is_object_v<std::centi>);
static_assert(std::is_object_v<std::deci>);
static_assert(std::is_object_v<std::deca>);
static_assert(std::is_object_v<std::hecto>);
static_assert(std::is_object_v<std::kilo>);
static_assert(std::is_object_v<std::mega>);
static_assert(std::is_object_v<std::giga>);
static_assert(std::is_object_v<std::tera>);
static_assert(std::is_object_v<std::peta>);
static_assert(std::is_object_v<std::exa>);
