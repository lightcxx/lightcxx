// REQUEST:NO_TEST_LIB "The testing library depends on <type_traits>."
// REQUEST:EXTRA_DEFINITIONS _LIGHTCXX_DONT_USE_BUILTINS

#include <type_traits>

#include "meta/test_unary_trait.h"

TEST_UNARY_TRAIT_AGAINST_VOID(false, std::is_lvalue_reference);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, std::is_lvalue_reference);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, std::is_lvalue_reference);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, std::is_lvalue_reference);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, std::is_lvalue_reference);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, std::is_lvalue_reference);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(true, std::is_lvalue_reference);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, std::is_lvalue_reference);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, std::is_lvalue_reference);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, std::is_lvalue_reference);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, std::is_lvalue_reference);
TEST_UNARY_TRAIT_AGAINST_UNION(false, std::is_lvalue_reference);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, std::is_lvalue_reference);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, std::is_lvalue_reference);

int main() {
    return 0;
}
