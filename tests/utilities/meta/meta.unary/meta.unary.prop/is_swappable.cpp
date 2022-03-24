#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_swappable_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_swappable, EVERY_CV);

TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_swappable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_swappable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_swappable, CONST);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_swappable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_swappable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_swappable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_swappable, CONST);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_swappable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_swappable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_swappable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_swappable, CONST);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_swappable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_swappable, NO_CV, int[10], int[10][10]);
TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_swappable, VOLATILE, int[10], int[10][10]);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_swappable, CONST, int[10], int[10][10]);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_swappable, CONST_VOLATILE, int[10], int[10][10]);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_swappable, EVERY_CV, int[], int[][10]);

TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_swappable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_swappable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_swappable, CONST);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_swappable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_swappable, NO_CV, int&, volatile int&, int*&,
                               int* volatile&);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_swappable, NO_CV, const int&, const volatile int&,
                               int* const&, int* const volatile&, int (&)(int));

TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_swappable, NO_CV, int&&, volatile int&&, int*&&,
                               int* volatile&&);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_swappable, NO_CV, const int&&, const volatile int&&,
                               int* const&&, int* const volatile&&, int(&&)(int));

TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_swappable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_swappable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_swappable, CONST);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_swappable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_swappable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_swappable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_swappable, CONST);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_swappable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_swappable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_swappable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_swappable, CONST);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_swappable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_UNION(true, is_swappable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_swappable, CONST);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_swappable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_swappable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_CLASS(true, is_swappable, NO_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_swappable, CONST);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_swappable, VOLATILE);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, is_swappable, CONST_VOLATILE);

TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_swappable);

struct NoMoveCtorNoMoveAssign {
    NoMoveCtorNoMoveAssign(NoMoveCtorNoMoveAssign&&) = delete;
    NoMoveCtorNoMoveAssign& operator=(NoMoveCtorNoMoveAssign&&) = delete;
};
struct NoMoveCtor {
    NoMoveCtor(NoMoveCtor&&) = delete;
    NoMoveCtor& operator=(NoMoveCtor&&) = default;
};
struct NoMoveAssign {
    NoMoveAssign(NoMoveAssign&&) = default;
    NoMoveCtorNoMoveAssign& operator=(NoMoveCtorNoMoveAssign&&) = delete;
};

namespace ns2 {

struct GlobalSwap {
    GlobalSwap(GlobalSwap&&) = delete;
    GlobalSwap& operator=(GlobalSwap&&) = delete;
};

}  // namespace ns2

void swap(ns2::GlobalSwap&, ns2::GlobalSwap&) {}

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_swappable, EVERY_CV, NoMoveCtorNoMoveAssign, NoMoveCtor,
                               NoMoveAssign, ns2::GlobalSwap);

struct HiddenFriendSwap {
    HiddenFriendSwap(HiddenFriendSwap&&) = delete;
    HiddenFriendSwap& operator=(HiddenFriendSwap&&) = delete;

    friend void swap(HiddenFriendSwap&, HiddenFriendSwap&) {}
};

namespace ns {

struct ADLSwap {
    ADLSwap(ADLSwap&&) = delete;
    ADLSwap& operator=(ADLSwap&&) = delete;
};

void swap(ADLSwap&, ADLSwap&) {}

}  // namespace ns

TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_swappable, NO_CV, HiddenFriendSwap, ns::ADLSwap);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_swappable, VOLATILE, HiddenFriendSwap, ns::ADLSwap);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_swappable, CONST, HiddenFriendSwap, ns::ADLSwap);
TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_swappable, CONST_VOLATILE, HiddenFriendSwap, ns::ADLSwap);
