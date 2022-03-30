#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_trivially_move_constructible_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_trivially_move_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_trivially_move_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_trivially_move_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_trivially_move_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_trivially_move_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_trivially_move_constructible, EVERY_CV);

// lvalue references -- false for everything except function & const references
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_move_constructible, NO_CV, int&, volatile int&, const volatile int&, int*&, int* volatile&,
                               int* const volatile&, incomplete_type&, volatile incomplete_type&, const volatile incomplete_type&);
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_trivially_move_constructible, NO_CV, const int&, int (&)(int), int* const&, const incomplete_type&);

TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(true, is_trivially_move_constructible);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_trivially_move_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_trivially_move_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_trivially_move_constructible, EVERY_CV);

// union -- true for const, false for volatile
TEST_UNARY_TRAIT_AGAINST_UNION(true, is_trivially_move_constructible, NO_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(true, is_trivially_move_constructible, CONST);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_trivially_move_constructible, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_trivially_move_constructible, CONST_VOLATILE);

// copy-constructible class -- true for const, false for volatile
TEST_UNARY_TRAIT_AGAINST_CLASS(true, is_trivially_move_constructible, NO_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(true, is_trivially_move_constructible, CONST);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_trivially_move_constructible, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_trivially_move_constructible, CONST_VOLATILE);

struct NoMoveCtor {
    NoMoveCtor(const NoMoveCtor&) = default;
    NoMoveCtor(NoMoveCtor&&) = delete;
};
struct NoCopyCtor {
    NoCopyCtor(const NoCopyCtor&) = delete;
    NoCopyCtor(NoCopyCtor&&) = default;
};
struct NoCopyNoMoveCtor {
    NoCopyNoMoveCtor(const NoCopyNoMoveCtor&) = delete;
    NoCopyNoMoveCtor(NoCopyNoMoveCtor&&) = delete;
};
struct NonTrivialMoveCtor {
    NonTrivialMoveCtor(const NonTrivialMoveCtor&) = default;
    NonTrivialMoveCtor(NonTrivialMoveCtor&&) {}
};
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_move_constructible, NO_CV, NoMoveCtor, NonTrivialMoveCtor);
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_trivially_move_constructible, CONST, NoMoveCtor, NonTrivialMoveCtor);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_move_constructible, VOLATILE, NoMoveCtor, NonTrivialMoveCtor);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_move_constructible, CONST_VOLATILE, NoMoveCtor, NonTrivialMoveCtor);
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_trivially_move_constructible, NO_CV, NoCopyCtor);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_move_constructible, CONST, NoCopyCtor);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_move_constructible, VOLATILE, NoCopyCtor);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_move_constructible, CONST_VOLATILE, NoCopyCtor);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_move_constructible, EVERY_CV, NoCopyNoMoveCtor);

TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_trivially_move_constructible);