// REQUEST:NO_TEST_LIB "The testing library depends on <type_traits>."

#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_fundamental_v);

TEST_UNARY_TRAIT_AGAINST_VOID(true, is_fundamental, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_fundamental, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_fundamental, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_fundamental, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_fundamental, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_fundamental, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, is_fundamental);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, is_fundamental);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_fundamental, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_fundamental, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_fundamental, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_fundamental, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_fundamental, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_fundamental);

int main() {
    return 0;
}
