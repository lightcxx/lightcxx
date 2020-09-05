// REQUEST:NO_TEST_LIB "The testing library depends on <type_traits>."

#include <type_traits>

#include "meta/test_unary_trait.h"

TEST_UNARY_TRAIT_AGAINST_VOID(false, std::is_object);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, std::is_object);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, std::is_object);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, std::is_object);
TEST_UNARY_TRAIT_AGAINST_ARRAY(true, std::is_object);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, std::is_object);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, std::is_object);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, std::is_object);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, std::is_object);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, std::is_object);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, std::is_object);
TEST_UNARY_TRAIT_AGAINST_UNION(true, std::is_object);
TEST_UNARY_TRAIT_AGAINST_CLASS(true, std::is_object);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, std::is_object);

int main() {
    return 0;
}
