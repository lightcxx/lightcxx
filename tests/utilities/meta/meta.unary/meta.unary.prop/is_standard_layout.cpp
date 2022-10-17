#include <type_traits>

#include "meta/test_unary_trait.h"
#include "warnings.h"

DECLARE_TRAIT_V_READER(is_standard_layout_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_standard_layout, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_standard_layout, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_standard_layout, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_standard_layout, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(true, is_standard_layout, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_standard_layout, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, is_standard_layout);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, is_standard_layout);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_standard_layout, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_standard_layout, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_standard_layout, EVERY_CV);
// TEST_UNARY_TRAIT_AGAINST_UNION(true, is_standard_layout, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_standard_layout);

class Empty {};
class EmptyDerived : public Empty {};
class Bits {
  public:
    char : 4;
};
class AllPublic : public Empty {
  public:
    int x, y;
};
class AllProtected {
  protected:
    int x, y;
};
class AllPrivate {
  private:
    [[maybe_unused]] int x, y;
};
class AllPublicDerived : public AllPublic {};
class AllPublicDerivedTwice : public AllPublicDerived {};
class AllProtectedDerived : public AllProtected {};
class AllPrivateDerived : public AllPrivate, public Empty {};
class AllPrivateDerivedTwice : public AllPrivateDerived {};
class AllPublicWrapper {
  public:
    AllPublicDerived d;
};
class AllProtectedWrapper {
  public:
    AllProtectedDerived d;
};
class AllPrivateWrapper {
  public:
    AllPrivateDerived d;
};
class MixedWrapper {
  public:
    AllPublicDerived d;
    AllProtectedDerived d2;
    AllPrivateDerived d3;
};

class ArrayElemBaseAsBase : public Empty {
  public:
    EmptyDerived arr[10];
};

TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_standard_layout, EVERY_CV, Empty, EmptyDerived, Bits, AllPublic, AllProtected, AllPrivate, AllPublicDerived,
                               AllPublicDerivedTwice, AllProtectedDerived, AllPrivateDerived, AllPrivateDerivedTwice, AllPublicWrapper, AllProtectedWrapper,
                               AllPrivateWrapper, MixedWrapper, ArrayElemBaseAsBase);

class Mixed1 {
  public:
    int x;

  private:
    [[maybe_unused]] int y;
};
class Mixed2 {
  public:
    int x;

  protected:
    int y;
};
class Mixed3 {
  protected:
    int x;

  private:
    [[maybe_unused]] int y;
};
class Mixed4 {
  public:
    int x;

  protected:
    int y;

  private:
    [[maybe_unused]] int z;
};

WARNINGS_IGNORE_NON_VIRTUAL_DTOR()
class Virtual1 {
    virtual void f();
};

class Virtual2 {
    virtual void f() = 0;
};

class Virtual3 {
    virtual ~Virtual3();
};

class Virtual4 {
    virtual ~Virtual4() = 0;
};

class VirtualBase1 : virtual Virtual2 {};

class VirtualBase2 : virtual Empty {};
WARNINGS_POP()

class Ref1 {
  public:
    int& x;
};

class Ref2 {
  public:
    const int& x;
};

class Ref3 {
  public:
    volatile int& x;
};

class Ref4 {
  public:
    const volatile int& x;
};

class Ref5 {
  public:
    int&& x;
};

class Ref6 {
  public:
    const int&& x;
};

class Ref7 {
  public:
    volatile int&& x;
};

class Ref8 {
  public:
    const volatile int&& x;
};

class NonStdLayoutMember {
  public:
    Ref1 x;
};

class NonStdLayoutBase : public Ref1 {};

struct DuplicateBaseClass : public EmptyDerived, public AllPublic {
    // Empty is a base class twice.
};

struct TwoBasesWithMembers : public AllPublicDerived, public Bits {};
struct MembersAndBaseWithMembers : public AllPublicDerived {
  public:
    int q;
};

class ArrayElemAsBase : public Empty {
  public:
    Empty arr[10];
};

class ArrayElemAsIndirectBase : public EmptyDerived {
  public:
    Empty arr[10];
};

class UnionMemberAsBase : public AllPublic {
  public:
    union {
        AllPublic p;
    };
};

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_standard_layout, EVERY_CV, Mixed1, Mixed2, Mixed3, Mixed4, Virtual1, Virtual2, Virtual3, Virtual4, VirtualBase1,
                               VirtualBase2, Ref1, Ref2, Ref3, Ref4, Ref5, Ref6, Ref7, Ref8, NonStdLayoutMember, NonStdLayoutBase, DuplicateBaseClass,
                               TwoBasesWithMembers, MembersAndBaseWithMembers, UnionMemberAsBase);
// TODO(@compilers): clang!=gcc
// TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_standard_layout, EVERY_CV, ArrayElemAsIndirectBase, ArrayElemAsBase);

union OneIntVariant {
    int x;
};

union StdLayoutVariant {
    int x, y, z;
    AllPublicDerived pub;
};

union StdLayoutArrayVariant {
    int x, y, z[10];
    AllPublicDerived pub[10];
};

TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_standard_layout, EVERY_CV, OneIntVariant, StdLayoutVariant, StdLayoutArrayVariant);

union NonStdLayoutVariant {
    int x, y, z;
    UnionMemberAsBase invalid;
};

union NonStdLayoutAndArrayVariant {
    int x, y, z[10];
    UnionMemberAsBase invalid;
};

union NonStdLayoutArrayVariant {
    int x, y, z;
    UnionMemberAsBase invalid[10];
};

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_standard_layout, EVERY_CV, NonStdLayoutVariant, NonStdLayoutAndArrayVariant, NonStdLayoutArrayVariant);