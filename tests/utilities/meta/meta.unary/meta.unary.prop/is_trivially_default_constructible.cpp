#include <type_traits>

#include "test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_trivially_default_constructible_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_trivially_default_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_trivially_default_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_trivially_default_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_trivially_default_constructible, EVERY_CV);

class NoDfltCtor {
  public:
    NoDfltCtor() = delete;
};
class NonTrivialDfltCtor {
  public:
    NonTrivialDfltCtor() {}
};
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_trivially_default_constructible, EVERY_CV, int[10], int[10][10], Class[10], Class[10][10], Enum[10], Enum[10][10],
                               Union[10], Union[10][10]);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_default_constructible, EVERY_CV, int[], int[][10], int[][10][10], Class[], Class[][10], Enum[], Enum[][10],
                               Union[], Union[][10], NoDfltCtor[10], NoDfltCtor[10][10], NoDfltCtor[], NoDfltCtor[][10], NonTrivialDfltCtor[10],
                               NonTrivialDfltCtor[10][10], NonTrivialDfltCtor[], NonTrivialDfltCtor[][10]);

TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_trivially_default_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, is_trivially_default_constructible);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, is_trivially_default_constructible);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_trivially_default_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_trivially_default_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_trivially_default_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(true, is_trivially_default_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(true, is_trivially_default_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_default_constructible, EVERY_CV, NoDfltCtor, NonTrivialDfltCtor);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_trivially_default_constructible);