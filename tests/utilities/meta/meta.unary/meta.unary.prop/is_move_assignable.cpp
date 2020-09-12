// REQUEST:NO_TEST_LIB "The testing library depends on <type_traits>."

#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_move_assignable);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_move_assignable, EVERY_CV);

TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_move_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_move_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_move_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_move_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_move_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_move_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_move_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_move_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_move_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_move_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_move_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_move_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_move_assignable, EVERY_CV);

TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_move_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_move_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_move_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_move_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_move_assignable, NO_CV, const int&, const volatile int&,
                               int (&)(int), int* const&, int* const volatile&, incomplete_type&,
                               const incomplete_type&, volatile incomplete_type&,
                               const volatile incomplete_type&);
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_move_assignable, NO_CV, int&, volatile int&, int*&,
                               int* volatile&);

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_move_assignable, NO_CV, const int&&, const volatile int&&,
                               int* const&&, int* const volatile&&, incomplete_type&&,
                               const incomplete_type&&, volatile incomplete_type&&,
                               const volatile incomplete_type&&, int(&&)(int));
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_move_assignable, NO_CV, int&&, volatile int&&, int*&&,
                               int* volatile&&);

TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_move_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_move_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_move_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_move_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_move_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_move_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_move_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_move_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_move_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_move_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_move_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_move_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_UNION(true, is_move_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_move_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_move_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_move_assignable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_CLASS(true, is_move_assignable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_move_assignable, CONST);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_move_assignable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_move_assignable, CONST_VOLATILE);

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
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_move_assignable, NO_CV, NoCopyAssignOp);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_move_assignable, CONST, NoCopyAssignOp);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_move_assignable, VOLATILE, NoCopyAssignOp);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_move_assignable, CONST_VOLATILE, NoCopyAssignOp);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_move_assignable, EVERY_CV, NoMoveAssignOp,
                               NoCopyNoMoveAssignOp);

TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_move_assignable);

int main() {
    return 0;
}
