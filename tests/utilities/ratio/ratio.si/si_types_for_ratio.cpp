#include "../test_ratio_helpers.h"

static_assert(check_ratio<std::atto, 1, 1'000'000'000'000'000'000>());
static_assert(check_ratio<std::femto, 1, 1'000'000'000'000'000>());
static_assert(check_ratio<std::pico, 1, 1'000'000'000'000>());
static_assert(check_ratio<std::nano, 1, 1'000'000'000>());
static_assert(check_ratio<std::micro, 1, 1'000'000>());
static_assert(check_ratio<std::milli, 1, 1'000>());
static_assert(check_ratio<std::centi, 1, 100>());
static_assert(check_ratio<std::deci, 1, 10>());
static_assert(check_ratio<std::deca, 10, 1>());
static_assert(check_ratio<std::hecto, 100, 1>());
static_assert(check_ratio<std::kilo, 1'000, 1>());
static_assert(check_ratio<std::mega, 1'000'000, 1>());
static_assert(check_ratio<std::giga, 1'000'000'000, 1>());
static_assert(check_ratio<std::tera, 1'000'000'000'000, 1>());
static_assert(check_ratio<std::peta, 1'000'000'000'000'000, 1>());
static_assert(check_ratio<std::exa, 1'000'000'000'000'000'000, 1>());
