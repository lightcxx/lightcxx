#include <type_traits>

#include "test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_trivially_copy_assignable_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_trivially_copy_assignable, EVERY_CV);

TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_trivially_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_trivially_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_trivially_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_trivially_copy_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_trivially_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_trivially_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_trivially_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_trivially_copy_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_trivially_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_trivially_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_trivially_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_trivially_copy_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_trivially_copy_assignable, EVERY_CV);

TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_trivially_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_trivially_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_trivially_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_trivially_copy_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_copy_assignable, NO_CV, const int&, const volatile int&, int (&)(int), int* const&, int* const volatile&,
                               incomplete_type&, const incomplete_type&, volatile incomplete_type&, const volatile incomplete_type&);
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_trivially_copy_assignable, NO_CV, int&, volatile int&, int*&, int* volatile&);

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_copy_assignable, NO_CV, const int&&, const volatile int&&, int* const&&, int* const volatile&&,
                               incomplete_type&&, const incomplete_type&&, volatile incomplete_type&&, const volatile incomplete_type&&, int (&&)(int));
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_trivially_copy_assignable, NO_CV, int&&, volatile int&&, int*&&, int* volatile&&);

TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_trivially_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_trivially_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_trivially_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_trivially_copy_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_trivially_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_trivially_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_trivially_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_trivially_copy_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_trivially_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_trivially_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_trivially_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_trivially_copy_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_UNION(true, is_trivially_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_trivially_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_trivially_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_trivially_copy_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_CLASS(true, is_trivially_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_trivially_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_trivially_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_trivially_copy_assignable, CONST_VOLATILE);

struct NoMoveAssignOp {
    NoMoveAssignOp& operator=(const NoMoveAssignOp&) = default;
    NoMoveAssignOp& operator=(NoMoveAssignOp&&) = delete;
};
struct NoCopyAssignOp {
    NoCopyAssignOp& operator=(const NoCopyAssignOp&) = delete;
    NoCopyAssignOp& operator=(NoCopyAssignOp&&) = default;
};
struct NoCopyNoMoveAssignOp {
    NoCopyNoMoveAssignOp& operator=(const NoCopyNoMoveAssignOp&) = delete;
    NoCopyNoMoveAssignOp& operator=(NoCopyNoMoveAssignOp&&) = delete;
};

struct NonTrivialCopyAssignOp {
    NonTrivialCopyAssignOp& operator=(const NonTrivialCopyAssignOp&) {
        return *this;
    }
    NonTrivialCopyAssignOp& operator=(NonTrivialCopyAssignOp&&) = delete;
};
struct NonTrivialMoveAssignOp {
    NonTrivialMoveAssignOp& operator=(const NonTrivialMoveAssignOp&) = delete;
    NonTrivialMoveAssignOp& operator=(NonTrivialMoveAssignOp&&) {
        return *this;
    }
};
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_trivially_copy_assignable, NO_CV, NoMoveAssignOp);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_copy_assignable, CONST, NoMoveAssignOp);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_copy_assignable, VOLATILE, NoMoveAssignOp);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_copy_assignable, CONST_VOLATILE, NoMoveAssignOp);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_trivially_copy_assignable, EVERY_CV, NoCopyAssignOp, NoCopyNoMoveAssignOp, NonTrivialCopyAssignOp,
                               NonTrivialMoveAssignOp);

TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_trivially_copy_assignable);