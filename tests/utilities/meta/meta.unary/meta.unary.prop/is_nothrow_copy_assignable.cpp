#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_nothrow_copy_assignable_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_nothrow_copy_assignable, EVERY_CV);

TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_nothrow_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_nothrow_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_nothrow_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_nothrow_copy_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_nothrow_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_nothrow_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_nothrow_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_nothrow_copy_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_nothrow_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_nothrow_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_nothrow_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_nothrow_copy_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_nothrow_copy_assignable, EVERY_CV);

TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_nothrow_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_nothrow_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_nothrow_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_nothrow_copy_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_nothrow_copy_assignable, NO_CV, const int&, const volatile int&, int (&)(int), int* const&, int* const volatile&,
                               incomplete_type&, const incomplete_type&, volatile incomplete_type&, const volatile incomplete_type&);
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_nothrow_copy_assignable, NO_CV, int&, volatile int&, int*&, int* volatile&);

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_nothrow_copy_assignable, NO_CV, const int&&, const volatile int&&, int* const&&, int* const volatile&&,
                               incomplete_type&&, const incomplete_type&&, volatile incomplete_type&&, const volatile incomplete_type&&, int(&&)(int));
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_nothrow_copy_assignable, NO_CV, int&&, volatile int&&, int*&&, int* volatile&&);

TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_nothrow_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_nothrow_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_nothrow_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_nothrow_copy_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_nothrow_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_nothrow_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_nothrow_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_nothrow_copy_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_nothrow_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_nothrow_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_nothrow_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_nothrow_copy_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_UNION(true, is_nothrow_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_nothrow_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_nothrow_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_nothrow_copy_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_CLASS(true, is_nothrow_copy_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_nothrow_copy_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_nothrow_copy_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_nothrow_copy_assignable, CONST_VOLATILE);

struct NoMoveAssignOp {
    void operator=(const NoMoveAssignOp&) {}
    NoMoveAssignOp& operator=(NoMoveAssignOp&&) = delete;
};
struct NoCopyAssignOp {
    NoCopyAssignOp& operator=(const NoCopyAssignOp&) = delete;
    void operator=(NoCopyAssignOp&&) {}
};
struct NoCopyNoMoveAssignOp {
    NoCopyNoMoveAssignOp& operator=(const NoCopyNoMoveAssignOp&) = delete;
    NoCopyNoMoveAssignOp& operator=(NoCopyNoMoveAssignOp&&) = delete;
};
struct NoThrowCopyNoMoveAssignOp {
    NoThrowCopyNoMoveAssignOp& operator=(const NoThrowCopyNoMoveAssignOp&) noexcept {
        return *this;
    }
    NoThrowCopyNoMoveAssignOp& operator=(NoThrowCopyNoMoveAssignOp&&) = delete;
};
struct NoCopyNoThrowMoveAssignOp {
    NoCopyNoThrowMoveAssignOp& operator=(const NoCopyNoThrowMoveAssignOp&) = delete;
    NoCopyNoThrowMoveAssignOp& operator=(NoCopyNoThrowMoveAssignOp&&) noexcept {
        return *this;
    }
};
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_nothrow_copy_assignable, NO_CV, NoThrowCopyNoMoveAssignOp);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_nothrow_copy_assignable, CONST, NoThrowCopyNoMoveAssignOp);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_nothrow_copy_assignable, VOLATILE, NoThrowCopyNoMoveAssignOp);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_nothrow_copy_assignable, CONST_VOLATILE, NoThrowCopyNoMoveAssignOp);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_nothrow_copy_assignable, EVERY_CV, NoCopyNoThrowMoveAssignOp);

TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_nothrow_copy_assignable);