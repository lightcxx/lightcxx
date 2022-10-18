#include <type_traits>

#include "test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_floating_point_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_floating_point, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_floating_point, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_floating_point, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_floating_point, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_floating_point, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_floating_point, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, is_floating_point);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, is_floating_point);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_floating_point, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_floating_point, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_floating_point, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_floating_point, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_floating_point, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_floating_point);
