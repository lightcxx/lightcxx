// REQUEST:NO_TEST_LIB "The testing library depends on <type_traits>."

#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_arithmetic_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_arithmetic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_arithmetic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_arithmetic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_arithmetic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_arithmetic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_arithmetic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, is_arithmetic);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, is_arithmetic);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_arithmetic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_arithmetic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_arithmetic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_arithmetic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_arithmetic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_arithmetic);

int main() {
    return 0;
}
