// REQUEST:NO_TEST_LIB "The testing library depends on <type_traits>."

#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_enum_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_enum, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_enum, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_enum, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_enum, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_enum, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_enum, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, is_enum);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, is_enum);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_enum, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_enum, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_enum, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_enum, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_enum, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_enum);

int main() {
    return 0;
}
