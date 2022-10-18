#include <type_traits>

#include "test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_null_pointer_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_null_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_null_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_null_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_null_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_null_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_null_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, is_null_pointer);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, is_null_pointer);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_null_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_null_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_null_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_null_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_null_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_null_pointer);