// REQUEST:NO_TEST_LIB "The testing library depends on <type_traits>."

#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_compound);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_compound, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_compound, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_compound, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_compound, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(true, is_compound, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_compound, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(true, is_compound);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(true, is_compound);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_compound, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_compound, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_compound, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(true, is_compound, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(true, is_compound, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(true, is_compound);

int main() {
    return 0;
}
