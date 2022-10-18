#include <type_traits>

#include "test_unary_trait.h"

DECLARE_TRAIT_V_READER(rank_v);

#define TEST_TYPE(TP, value) static_assert(test_unary_prop_query<std::rank, rank_v_reader, TP, value>())

TEST_TYPE(bool, 0);
TEST_TYPE(bool&, 0);
TEST_TYPE(bool&&, 0);
TEST_TYPE(bool[10], 1);
TEST_TYPE(bool[], 1);
TEST_TYPE(bool[10][10], 2);
TEST_TYPE(bool[][10], 2);
TEST_TYPE(bool[10][10][10], 3);
TEST_TYPE(bool[][10][10], 3);
TEST_TYPE(bool*, 0);
TEST_TYPE(bool* [10], 1);
TEST_TYPE(bool*[], 1);
TEST_TYPE(bool* [10][10], 2);
TEST_TYPE(bool*[][10], 2);
TEST_TYPE(bool* [10][10][10], 3);
TEST_TYPE(bool*[][10][10], 3);

TEST_TYPE(int, 0);
TEST_TYPE(int&, 0);
TEST_TYPE(int&&, 0);
TEST_TYPE(int[10], 1);
TEST_TYPE(int[], 1);
TEST_TYPE(int[10][10], 2);
TEST_TYPE(int[][10], 2);
TEST_TYPE(int[10][10][10], 3);
TEST_TYPE(int[][10][10], 3);
TEST_TYPE(int*, 0);
TEST_TYPE(int* [10], 1);
TEST_TYPE(int*[], 1);
TEST_TYPE(int* [10][10], 2);
TEST_TYPE(int*[][10], 2);
TEST_TYPE(int* [10][10][10], 3);
TEST_TYPE(int*[][10][10], 3);

TEST_TYPE(unsigned long long, 0);
TEST_TYPE(unsigned long long&, 0);
TEST_TYPE(unsigned long long&&, 0);
TEST_TYPE(unsigned long long[10], 1);
TEST_TYPE(unsigned long long[], 1);
TEST_TYPE(unsigned long long[10][10], 2);
TEST_TYPE(unsigned long long[][10], 2);
TEST_TYPE(unsigned long long[10][10][10], 3);
TEST_TYPE(unsigned long long[][10][10], 3);
TEST_TYPE(unsigned long long*, 0);
TEST_TYPE(unsigned long long* [10], 1);
TEST_TYPE(unsigned long long*[], 1);
TEST_TYPE(unsigned long long* [10][10], 2);
TEST_TYPE(unsigned long long*[][10], 2);
TEST_TYPE(unsigned long long* [10][10][10], 3);
TEST_TYPE(unsigned long long*[][10][10], 3);
