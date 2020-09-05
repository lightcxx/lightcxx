// REQUEST:NO_TEST_LIB "The testing library depends on <type_traits>."
// REQUEST:EXTRA_DEFINITIONS _LIGHTCXX_DONT_USE_BUILTINS

#include <type_traits>

#include "meta/test_unary_trait.h"

TEST_UNARY_TRAIT_AGAINST_VOID(false, std::is_compound);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, std::is_compound);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, std::is_compound);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, std::is_compound);
TEST_UNARY_TRAIT_AGAINST_ARRAY(true, std::is_compound);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, std::is_compound);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(true, std::is_compound);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(true, std::is_compound);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, std::is_compound);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, std::is_compound);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, std::is_compound);
TEST_UNARY_TRAIT_AGAINST_UNION(true, std::is_compound);
TEST_UNARY_TRAIT_AGAINST_CLASS(true, std::is_compound);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(true, std::is_compound);

int main() {
    return 0;
}
