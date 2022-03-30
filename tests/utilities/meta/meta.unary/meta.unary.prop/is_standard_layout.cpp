#include <type_traits>

#include "meta/test_unary_trait.h"

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
    [[maybe_unused]] int x, y;
};
class AllProtected {
  protected:
    [[maybe_unused]] int x, y;
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
    [[maybe_unused]] AllPublicDerived d;
};
class AllProtectedWrapper {
  public:
    [[maybe_unused]] AllProtectedDerived d;
};
class AllPrivateWrapper {
  public:
    [[maybe_unused]] AllPrivateDerived d;
};
class MixedWrapper {
  public:
    [[maybe_unused]] AllPublicDerived d;
    [[maybe_unused]] AllProtectedDerived d2;
    [[maybe_unused]] AllPrivateDerived d3;
};

class ArrayElemBaseAsBase : public Empty {
  public:
    [[maybe_unused]] EmptyDerived arr[10];
};

TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_standard_layout, EVERY_CV, Empty, EmptyDerived, Bits, AllPublic, AllProtected, AllPrivate, AllPublicDerived,
                               AllPublicDerivedTwice, AllProtectedDerived, AllPrivateDerived, AllPrivateDerivedTwice, AllPublicWrapper, AllProtectedWrapper,
                               AllPrivateWrapper, MixedWrapper, ArrayElemBaseAsBase);

class Mixed1 {
  public:
    [[maybe_unused]] int x;

  private:
    [[maybe_unused]] int y;
};
class Mixed2 {
  public:
    [[maybe_unused]] int x;

  protected:
    [[maybe_unused]] int y;
};
class Mixed3 {
  protected:
    [[maybe_unused]] int x;

  private:
    [[maybe_unused]] int y;
};
class Mixed4 {
  public:
    [[maybe_unused]] int x;

  protected:
    [[maybe_unused]] int y;

  private:
    [[maybe_unused]] int z;
};

class Virtual1 {
    [[maybe_unused]] virtual void f();
};

class Virtual2 {
    [[maybe_unused]] virtual void f() = 0;
};

class Virtual3 {
    virtual ~Virtual3();
};

class Virtual4 {
    virtual ~Virtual4() = 0;
};

class VirtualBase1 : virtual Virtual2 {};

class VirtualBase2 : virtual Empty {};

class Ref1 {
  public:
    [[maybe_unused]] int& x;
};

class Ref2 {
  public:
    [[maybe_unused]] const int& x;
};

class Ref3 {
  public:
    [[maybe_unused]] volatile int& x;
};

class Ref4 {
  public:
    [[maybe_unused]] const volatile int& x;
};

class Ref5 {
  public:
    [[maybe_unused]] int&& x;
};

class Ref6 {
  public:
    [[maybe_unused]] const int&& x;
};

class Ref7 {
  public:
    [[maybe_unused]] volatile int&& x;
};

class Ref8 {
  public:
    [[maybe_unused]] const volatile int&& x;
};

class NonStdLayoutMember {
  public:
    [[maybe_unused]] Ref1 x;
};

class NonStdLayoutBase : public Ref1 {};

struct DuplicateBaseClass : public EmptyDerived, public AllPublic {
    // Empty is a base class twice.
};

struct TwoBasesWithMembers : public AllPublicDerived, public Bits {};
struct MembersAndBaseWithMembers : public AllPublicDerived {
  public:
    [[maybe_unused]] int q;
};

class ArrayElemAsBase : public Empty {
  public:
    [[maybe_unused]] Empty arr[10];
};

class ArrayElemAsIndirectBase : public EmptyDerived {
  public:
    [[maybe_unused]] Empty arr[10];
};

class UnionMemberAsBase : public AllPublic {
  public:
    union {
        [[maybe_unused]] AllPublic p;
    };
};

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_standard_layout, EVERY_CV, Mixed1, Mixed2, Mixed3, Mixed4, Virtual1, Virtual2, Virtual3, Virtual4, VirtualBase1,
                               VirtualBase2, Ref1, Ref2, Ref3, Ref4, Ref5, Ref6, Ref7, Ref8, NonStdLayoutMember, NonStdLayoutBase, DuplicateBaseClass,
                               TwoBasesWithMembers, MembersAndBaseWithMembers, ArrayElemAsBase, ArrayElemAsIndirectBase, UnionMemberAsBase);

union OneIntVariant {
    [[maybe_unused]] int x;
};

union StdLayoutVariant {
    [[maybe_unused]] int x, y, z;
    [[maybe_unused]] AllPublicDerived pub;
};

union StdLayoutArrayVariant {
    [[maybe_unused]] int x, y, z[10];
    [[maybe_unused]] AllPublicDerived pub[10];
};

TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_standard_layout, EVERY_CV, OneIntVariant, StdLayoutVariant, StdLayoutArrayVariant);

union NonStdLayoutVariant {
    [[maybe_unused]] int x, y, z;
    [[maybe_unused]] UnionMemberAsBase invalid;
};

union NonStdLayoutAndArrayVariant {
    [[maybe_unused]] int x, y, z[10];
    [[maybe_unused]] UnionMemberAsBase invalid;
};

union NonStdLayoutArrayVariant {
    [[maybe_unused]] int x, y, z;
    [[maybe_unused]] UnionMemberAsBase invalid[10];
};

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_standard_layout, EVERY_CV, NonStdLayoutVariant, NonStdLayoutAndArrayVariant, NonStdLayoutArrayVariant);