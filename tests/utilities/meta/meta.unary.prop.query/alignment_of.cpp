#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(alignment_of_v);

#define TEST_TYPE(TP, value) static_assert(test_unary_prop_query<std::alignment_of, alignment_of_v_reader, TP, value>())

TEST_TYPE(bool, 1);
TEST_TYPE(char, 1);
TEST_TYPE(signed char, 1);
TEST_TYPE(unsigned char, 1);
TEST_TYPE(short, 2);
TEST_TYPE(unsigned short, 2);
TEST_TYPE(int, 4);
TEST_TYPE(unsigned int, 4);
TEST_TYPE(long, 8);
TEST_TYPE(unsigned long, 8);
TEST_TYPE(long long, 8);
TEST_TYPE(unsigned long long, 8);

TEST_TYPE(bool&, 1);
TEST_TYPE(int&, 4);
TEST_TYPE(unsigned long long&, 8);

TEST_TYPE(bool&&, 1);
TEST_TYPE(int&&, 4);
TEST_TYPE(unsigned long long&&, 8);

TEST_TYPE(bool*, 8);
TEST_TYPE(int*, 8);
TEST_TYPE(unsigned long long*, 8);

TEST_TYPE(bool[10], 1);
TEST_TYPE(bool[], 1);
TEST_TYPE(bool[10][10], 1);
TEST_TYPE(bool[][10], 1);
TEST_TYPE(int[10], 4);
TEST_TYPE(int[], 4);
TEST_TYPE(int[10][10], 4);
TEST_TYPE(int[][10], 4);
TEST_TYPE(unsigned long long[10], 8);
TEST_TYPE(unsigned long long[], 8);
TEST_TYPE(unsigned long long[10][10], 8);
TEST_TYPE(unsigned long long[][10], 8);
