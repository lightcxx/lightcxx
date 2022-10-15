#include <ratio>

#include "../test_ratio_helpers.h"

// ratio_add
static_assert(check_ratio_strict<std::ratio_add<std::ratio<1, 3>, std::ratio<1, 6>>, 1, 2>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<3, 18>, std::ratio<3, 9>>, 1, 2>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<4, 1>, std::ratio<6, 1>>, 10, 1>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<6, 1>, std::ratio<4, 1>>, 10, 1>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<0, 1>, std::ratio<2, 1>>, 2, 1>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<2, 1>, std::ratio<0, 1>>, 2, 1>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<0, 2>, std::ratio<2, 7>>, 2, 7>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<2, 7>, std::ratio<0, 2>>, 2, 7>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<0, 4>, std::ratio<0, 3>>, 0, 1>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<0, 3>, std::ratio<0, 4>>, 0, 1>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<-1, 2>, std::ratio<1, 2>>, 0, 1>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<-1, 2>, std::ratio<1, 4>>, -1, 4>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<1, 2>, std::ratio<-1, 4>>, 1, 4>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<-1, 2>, std::ratio<-1, 4>>, -3, 4>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<-4, 12>, std::ratio<-6, 12>>, -5, 6>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<-6, 12>, std::ratio<-4, 12>>, -5, 6>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<5, INTMAX_MAX>, std::ratio<7, INTMAX_MAX>>, 12, INTMAX_MAX>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<INTMAX_MAX - 4, 5>, std::ratio<4, 5>>, INTMAX_MAX, 5>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<INTMAX_MAX - 3, 5>, std::ratio<2, 5>>, INTMAX_MAX - 1, 5>());
static_assert(check_ratio_strict<std::ratio_add<std::ratio<4 - INTMAX_MAX, 5>, std::ratio<INTMAX_MAX - 1, 5>>, 3, 5>());

// ratio_subtract
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<1, 3>, std::ratio<1, 6>>, 1, 6>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<3, 18>, std::ratio<3, 9>>, -1, 6>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<4, 1>, std::ratio<6, 1>>, -2, 1>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<6, 1>, std::ratio<4, 1>>, 2, 1>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<0, 1>, std::ratio<2, 1>>, -2, 1>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<2, 1>, std::ratio<0, 1>>, 2, 1>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<0, 2>, std::ratio<2, 7>>, -2, 7>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<2, 7>, std::ratio<0, 2>>, 2, 7>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<0, 4>, std::ratio<0, 3>>, 0, 1>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<0, 3>, std::ratio<0, 4>>, 0, 1>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<-1, 2>, std::ratio<1, 2>>, -1, 1>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<-1, 2>, std::ratio<1, 4>>, -3, 4>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<1, 2>, std::ratio<-1, 4>>, 3, 4>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<-1, 2>, std::ratio<-1, 4>>, -1, 4>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<-4, 12>, std::ratio<-6, 12>>, 1, 6>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<-6, 12>, std::ratio<-4, 12>>, -1, 6>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<5, INTMAX_MAX>, std::ratio<7, INTMAX_MAX>>, -2, INTMAX_MAX>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<INTMAX_MAX - 4, 5>, std::ratio<4, 5>>, INTMAX_MAX - 8, 5>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<INTMAX_MAX - 3, 5>, std::ratio<2, 5>>, INTMAX_MAX - 5, 5>());
static_assert(check_ratio_strict<std::ratio_subtract<std::ratio<4 - INTMAX_MAX, 5>, std::ratio<-1, 5>>, 5 - INTMAX_MAX, 5>());

// ratio_multiply
static_assert(check_ratio_strict<std::ratio_multiply<std::ratio<1, 3>, std::ratio<1, 6>>, 1, 18>());
static_assert(check_ratio_strict<std::ratio_multiply<std::ratio<4, 6>, std::ratio<18, 3>>, 4, 1>());
static_assert(check_ratio_strict<std::ratio_multiply<std::ratio<2, 3>, std::ratio<0, 7>>, 0, 1>());
static_assert(check_ratio_strict<std::ratio_multiply<std::ratio<-2, 4>, std::ratio<0, 7>>, 0, 1>());
static_assert(check_ratio_strict<std::ratio_multiply<std::ratio<0, 7>, std::ratio<0, 3>>, 0, 1>());
static_assert(check_ratio_strict<std::ratio_multiply<std::ratio<0, 7>, std::ratio<2, 3>>, 0, 1>());
static_assert(check_ratio_strict<std::ratio_multiply<std::ratio<0, 7>, std::ratio<-2, 3>>, 0, 1>());
static_assert(check_ratio_strict<std::ratio_multiply<std::ratio<-5, 3>, std::ratio<2, 6>>, -5, 9>());
static_assert(check_ratio_strict<std::ratio_multiply<std::ratio<-5, 3>, std::ratio<-2, 6>>, 5, 9>());
static_assert(check_ratio_strict<std::ratio_multiply<std::ratio<5, 3>, std::ratio<-2, 6>>, -5, 9>());
static_assert(check_ratio_strict<std::ratio_multiply<std::ratio<INTMAX_MAX, INTMAX_MAX>, std::ratio<1, 1>>, 1, 1>());
static_assert(check_ratio_strict<std::ratio_multiply<std::ratio<INTMAX_MAX, 1>, std::ratio<1, INTMAX_MAX>>, 1, 1>());
static_assert(check_ratio_strict<std::ratio_multiply<std::ratio<INTMAX_MAX, 3>, std::ratio<7, INTMAX_MAX>>, 7, 3>());
static_assert(check_ratio_strict<std::ratio_multiply<std::ratio<-INTMAX_MAX, -INTMAX_MAX>, std::ratio<-1, 1>>, -1, 1>());
static_assert(check_ratio_strict<std::ratio_multiply<std::ratio<-INTMAX_MAX, 1>, std::ratio<1, INTMAX_MAX>>, -1, 1>());
static_assert(check_ratio_strict<std::ratio_multiply<std::ratio<INTMAX_MAX, 3>, std::ratio<7, -INTMAX_MAX>>, -7, 3>());

// ratio_divide
static_assert(check_ratio_strict<std::ratio_divide<std::ratio<1, 3>, std::ratio<6, 1>>, 1, 18>());
static_assert(check_ratio_strict<std::ratio_divide<std::ratio<4, 6>, std::ratio<3, 18>>, 4, 1>());
static_assert(check_ratio_strict<std::ratio_divide<std::ratio<0, 7>, std::ratio<3, 2>>, 0, 1>());
static_assert(check_ratio_strict<std::ratio_divide<std::ratio<0, 7>, std::ratio<3, -2>>, 0, 1>());
static_assert(check_ratio_strict<std::ratio_divide<std::ratio<-5, 3>, std::ratio<6, 2>>, -5, 9>());
static_assert(check_ratio_strict<std::ratio_divide<std::ratio<-5, 3>, std::ratio<6, -2>>, 5, 9>());
static_assert(check_ratio_strict<std::ratio_divide<std::ratio<5, 3>, std::ratio<6, -2>>, -5, 9>());
static_assert(check_ratio_strict<std::ratio_divide<std::ratio<INTMAX_MAX, INTMAX_MAX>, std::ratio<1, 1>>, 1, 1>());
static_assert(check_ratio_strict<std::ratio_divide<std::ratio<INTMAX_MAX, 1>, std::ratio<INTMAX_MAX, 1>>, 1, 1>());
static_assert(check_ratio_strict<std::ratio_divide<std::ratio<INTMAX_MAX, 3>, std::ratio<INTMAX_MAX, 7>>, 7, 3>());
static_assert(check_ratio_strict<std::ratio_divide<std::ratio<-INTMAX_MAX, -INTMAX_MAX>, std::ratio<1, -1>>, -1, 1>());
static_assert(check_ratio_strict<std::ratio_divide<std::ratio<-INTMAX_MAX, 1>, std::ratio<INTMAX_MAX, 1>>, -1, 1>());
static_assert(check_ratio_strict<std::ratio_divide<std::ratio<INTMAX_MAX, 3>, std::ratio<-INTMAX_MAX, 7>>, -7, 3>());
