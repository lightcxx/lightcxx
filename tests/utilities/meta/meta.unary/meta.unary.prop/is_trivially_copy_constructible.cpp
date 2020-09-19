// REQUEST:NO_TEST_LIB "The testing library depends on <type_traits>."

#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_trivially_copy_constructible_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_trivially_copy_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_trivially_copy_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_trivially_copy_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_trivially_copy_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_trivially_copy_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_trivially_copy_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(true, is_trivially_copy_constructible);

// rvalue references -- false for everything except function references
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_copy_constructible, NO_CV, int&&, const int&&,
                               volatile int&&, const volatile int&&, int*&&, int* const&&,
                               int* volatile&&, int* const volatile&&, incomplete_type&&,
                               const incomplete_type&&, volatile incomplete_type&&,
                               const volatile incomplete_type&&);
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_trivially_copy_constructible, NO_CV, int(&&)(int));

TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_trivially_copy_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_trivially_copy_constructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_trivially_copy_constructible, EVERY_CV);

// union -- true for const, false for volatile
TEST_UNARY_TRAIT_AGAINST_UNION(true, is_trivially_copy_constructible, NO_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(true, is_trivially_copy_constructible, CONST);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_trivially_copy_constructible, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_trivially_copy_constructible, CONST_VOLATILE);

// class -- true for const, false for volatile
TEST_UNARY_TRAIT_AGAINST_CLASS(true, is_trivially_copy_constructible, NO_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(true, is_trivially_copy_constructible, CONST);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_trivially_copy_constructible, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_trivially_copy_constructible, CONST_VOLATILE);

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
struct NonTrivialCopyCtor {
    NonTrivialCopyCtor(const NonTrivialCopyCtor&) {}
    NonTrivialCopyCtor(NonTrivialCopyCtor&&) = default;
};
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_trivially_copy_constructible, NO_CV, NoMoveCtor);
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_trivially_copy_constructible, CONST, NoMoveCtor);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_copy_constructible, VOLATILE, NoMoveCtor);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_copy_constructible, CONST_VOLATILE, NoMoveCtor);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_copy_constructible, EVERY_CV, NoCopyCtor,
                               NoCopyNoMoveCtor, NonTrivialCopyCtor);

TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_trivially_copy_constructible);

int main() {
    return 0;
}
