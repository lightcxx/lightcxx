#include "../test_ratio_helpers.h"

// Simple cases
static_assert(check_ratio<std::ratio<1, 2>, 1, 2>());
static_assert(check_ratio<std::ratio<17, 13>, 17, 13>());
static_assert(check_ratio<std::ratio<7>, 7, 1>());  // Default den = 1
static_assert(check_ratio<std::ratio<INTMAX_MAX, 1>, INTMAX_MAX, 1>());
static_assert(check_ratio<std::ratio<1, INTMAX_MAX>, 1, INTMAX_MAX>());
static_assert(check_ratio<std::ratio<0, 1>, 0, 1>());
static_assert(check_ratio<std::ratio<0, 2>, 0, 1>());
static_assert(check_ratio<std::ratio<0, INTMAX_MAX>, 0, 1>());
static_assert(check_ratio<std::ratio<0>, 0, 1>());  // Default den = 1

// GCD reduction
static_assert(check_ratio<std::ratio<6, 6>, 1, 1>());
static_assert(check_ratio<std::ratio<3, 6>, 1, 2>());
static_assert(check_ratio<std::ratio<6, 3>, 2, 1>());
static_assert(check_ratio<std::ratio<24, 112>, 3, 14>());
static_assert(check_ratio<std::ratio<112, 24>, 14, 3>());
static_assert(check_ratio<std::ratio<9'223'372'036'854'775'806, 5'726'623'064>, 6'442'450'941, 4>());
static_assert(check_ratio<std::ratio<2 * 5'726'623'064, 9'223'372'036'854'775'806>, 8, 6'442'450'941>());

// Sign normalization
static_assert(check_ratio<std::ratio<-6, 6>, -1, 1>());
static_assert(check_ratio<std::ratio<3, -6>, -1, 2>());
static_assert(check_ratio<std::ratio<-6, -3>, 2, 1>());
static_assert(check_ratio<std::ratio<-24, 112>, -3, 14>());
static_assert(check_ratio<std::ratio<-112, -24>, 14, 3>());
static_assert(check_ratio<std::ratio<9'223'372'036'854'775'806, -5'726'623'064>, -6'442'450'941, 4>());
static_assert(check_ratio<std::ratio<2 * 5'726'623'064, -9'223'372'036'854'775'806>, -8, 6'442'450'941>());
