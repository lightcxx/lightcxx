#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_unbounded_array_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_unbounded_array, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_unbounded_array, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_unbounded_array, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_unbounded_array, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_unbounded_array, EVERY_CV, int[10], int[10][10]);
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_unbounded_array, EVERY_CV, int[], int[][10], int[][10][10]);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_unbounded_array, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, is_unbounded_array);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, is_unbounded_array);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_unbounded_array, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_unbounded_array, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_unbounded_array, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_unbounded_array, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_unbounded_array, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_unbounded_array);