// This is example 1 from 20.16.4 [ratio.arithmetic], paragraph 3.

#include <ratio>

static_assert(std::ratio_add<std::ratio<1, 3>, std::ratio<1, 6>>::num == 1, "1/3+1/6 == 1/2");
static_assert(std::ratio_add<std::ratio<1, 3>, std::ratio<1, 6>>::den == 2, "1/3+1/6 == 1/2");
static_assert(std::ratio_multiply<std::ratio<1, 3>, std::ratio<3, 2>>::num == 1, "1/3*3/2 == 1/2");
static_assert(std::ratio_multiply<std::ratio<1, 3>, std::ratio<3, 2>>::den == 2, "1/3*3/2 == 1/2");

static_assert(std::ratio_add<std::ratio<1, INTMAX_MAX>, std::ratio<1, INTMAX_MAX>>::num == 2, "1/MAX+1/MAX == 2/MAX");
static_assert(std::ratio_add<std::ratio<1, INTMAX_MAX>, std::ratio<1, INTMAX_MAX>>::den == INTMAX_MAX, "1/MAX+1/MAX == 2/MAX");
static_assert(std::ratio_multiply<std::ratio<1, INTMAX_MAX>, std::ratio<INTMAX_MAX, 2>>::num == 1, "1/MAX * MAX/2 == 1/2");
static_assert(std::ratio_multiply<std::ratio<1, INTMAX_MAX>, std::ratio<INTMAX_MAX, 2>>::den == 2, "1/MAX * MAX/2 == 1/2");
