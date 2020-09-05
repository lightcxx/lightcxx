// REQUEST:NO_TEST_LIB "The testing library depends on <type_traits>."

#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_member_object_pointer);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_member_object_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_member_object_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_member_object_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_member_object_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_member_object_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_member_object_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, is_member_object_pointer);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, is_member_object_pointer);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_member_object_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_member_object_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_member_object_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_member_object_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_member_object_pointer, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_member_object_pointer);

int main() {
    return 0;
}
