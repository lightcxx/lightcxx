#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(has_unique_object_representations_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, has_unique_object_representations, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, has_unique_object_representations, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, has_unique_object_representations, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, has_unique_object_representations);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, has_unique_object_representations);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, has_unique_object_representations);

TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, has_unique_object_representations, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, has_unique_object_representations, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, has_unique_object_representations, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, has_unique_object_representations, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, has_unique_object_representations, EVERY_CV);

TEST_UNARY_TRAIT_AGAINST_TYPES(true, has_unique_object_representations, EVERY_CV, int[10], int[10][10], int[], int[][10], int[][10][10]);

union UniqueUnion {
    int x;
    unsigned int y;
    char z[sizeof(int)];
};
union NotUniqueUnion {
    unsigned char x;
    long long y;
};
TEST_UNARY_TRAIT_AGAINST_TYPES(true, has_unique_object_representations, EVERY_CV, UniqueUnion, UniqueUnion[10], UniqueUnion[], UniqueUnion[10][10],
                               UniqueUnion[][10]);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, has_unique_object_representations, EVERY_CV, NotUniqueUnion, NotUniqueUnion[10], NotUniqueUnion[], NotUniqueUnion[10][10],
                               NotUniqueUnion[][10]);

struct UniqueClass {
    int x;
    int y;
};
struct NonUniqueClass {
    int x;
    long long y;
    char z;
};
struct WithBits {
    int x : 4;
    int y : 4;
};
TEST_UNARY_TRAIT_AGAINST_TYPES(true, has_unique_object_representations, EVERY_CV, UniqueClass, UniqueClass[10], UniqueClass[], UniqueClass[10][10],
                               UniqueClass[][10]);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, has_unique_object_representations, EVERY_CV, NonUniqueClass, NonUniqueClass[10], NonUniqueClass[], NonUniqueClass[10][10],
                               NonUniqueClass[][10], WithBits, WithBits[10], WithBits[], WithBits[10][10], WithBits[][10]);
