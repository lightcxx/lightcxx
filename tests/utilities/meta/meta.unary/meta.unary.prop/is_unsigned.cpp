#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_unsigned_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_unsigned, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_unsigned, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_unsigned, EVERY_CV, signed char, short int, int, long int, long long int, char, wchar_t);
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_unsigned, EVERY_CV, bool, unsigned char, unsigned short int, unsigned int, unsigned long int, unsigned long long int,
                               char8_t, char16_t, char32_t);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_unsigned, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_unsigned, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_unsigned, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, is_unsigned);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, is_unsigned);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_unsigned, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_unsigned, EVERY_CV);
enum [[maybe_unused]] EnumUnsigned : unsigned{eu1, eu2};
enum [[maybe_unused]] EnumSigned : int{es1, es2};
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_unsigned, EVERY_CV, Enum, EnumUnsigned, EnumSigned, EnumClass);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_unsigned, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_unsigned, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_unsigned);