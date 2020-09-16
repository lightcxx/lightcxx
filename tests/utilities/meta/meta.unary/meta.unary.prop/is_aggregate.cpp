// REQUEST:NO_TEST_LIB "The testing library depends on <type_traits>."

#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_aggregate_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_aggregate, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_aggregate, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_aggregate, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_aggregate, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_aggregate, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, is_aggregate);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, is_aggregate);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_aggregate, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_aggregate, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_aggregate, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_aggregate);

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

class NonAggregateMember {
  public:
    [[maybe_unused]] Virtual3 x;
};

class NonAggregateBase final : public Virtual3 {
    ~NonAggregateBase() override;
};

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

class PublicCtor {
  public:
    [[maybe_unused]] int x, y;

    PublicCtor() {}
};

class ProtectedCtor {
  public:
    [[maybe_unused]] int x, y;

  protected:
    ProtectedCtor() {}
};

class PrivateCtor {
  public:
    [[maybe_unused]] int x, y;

  private:
    PrivateCtor() {}
};

class InheritedPublicCtor : public PublicCtor {};

class InheritedProtectedCtor : public ProtectedCtor {};

class InheritedPrivateCtor : public PrivateCtor {};

class DeletedPublicCtor {
  public:
    [[maybe_unused]] int x, y;

    DeletedPublicCtor() = delete;
};

class DeletedProtectedCtor {
  public:
    [[maybe_unused]] int x, y;

  protected:
    DeletedProtectedCtor() = delete;
};

class DeletedPrivateCtor {
  public:
    [[maybe_unused]] int x, y;

  private:
    DeletedPrivateCtor() = delete;
};

// All types of arrays I could think of.
TEST_UNARY_TRAIT_AGAINST_ARRAY(true, is_aggregate, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_TYPES(
  true, is_aggregate, EVERY_CV, Empty[10], EmptyDerived[10], Bits[10], AllPublic[10],
  AllPublicDerived[10], AllPublicDerivedTwice[10], AllProtectedDerived[10], AllPrivateDerived[10],
  AllPrivateDerivedTwice[10], AllPublicWrapper[10], AllProtectedWrapper[10], AllPrivateWrapper[10],
  MixedWrapper[10], ArrayElemBaseAsBase[10], Ref1[10], Ref2[10], Ref3[10], Ref4[10], Ref5[10],
  Ref6[10], Ref7[10], Ref8[10], DuplicateBaseClass[10], TwoBasesWithMembers[10],
  MembersAndBaseWithMembers[10], ArrayElemAsBase[10], ArrayElemAsIndirectBase[10],
  NonAggregateMember[10], UnionMemberAsBase[10], AllProtected[10], AllPrivate[10], PublicCtor[10],
  ProtectedCtor[10], PrivateCtor[10], InheritedPublicCtor[10], InheritedProtectedCtor[10],
  InheritedPrivateCtor[10], DeletedPublicCtor[10], DeletedProtectedCtor[10], DeletedPrivateCtor[10],
  Empty[], EmptyDerived[], Bits[], AllPublic[], AllPublicDerived[], AllPublicDerivedTwice[],
  AllProtectedDerived[], AllPrivateDerived[], AllPrivateDerivedTwice[], AllPublicWrapper[],
  AllProtectedWrapper[], AllPrivateWrapper[], MixedWrapper[], ArrayElemBaseAsBase[], Ref1[], Ref2[],
  Ref3[], Ref4[], Ref5[], Ref6[], Ref7[], Ref8[], DuplicateBaseClass[], TwoBasesWithMembers[],
  MembersAndBaseWithMembers[], ArrayElemAsBase[], ArrayElemAsIndirectBase[], NonAggregateMember[],
  UnionMemberAsBase[], AllProtected[], AllPrivate[], PublicCtor[], ProtectedCtor[], PrivateCtor[],
  InheritedPublicCtor[], InheritedProtectedCtor[], InheritedPrivateCtor[], DeletedPublicCtor[],
  DeletedProtectedCtor[], DeletedPrivateCtor[]);

TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_aggregate, EVERY_CV, Empty, EmptyDerived, Bits, AllPublic,
                               AllPublicDerived, AllPublicDerivedTwice, AllProtectedDerived,
                               AllPrivateDerived, AllPrivateDerivedTwice, AllPublicWrapper,
                               AllProtectedWrapper, AllPrivateWrapper, MixedWrapper,
                               ArrayElemBaseAsBase, Ref1, Ref2, Ref3, Ref4, Ref5, Ref6, Ref7, Ref8,
                               DuplicateBaseClass, TwoBasesWithMembers, MembersAndBaseWithMembers,
                               ArrayElemAsBase, ArrayElemAsIndirectBase, NonAggregateMember,
                               UnionMemberAsBase);

TEST_UNARY_TRAIT_AGAINST_TYPES(
  false, is_aggregate, EVERY_CV, AllProtected, AllPrivate, Mixed1, Mixed2, Mixed3, Mixed4, Virtual1,
  Virtual2, Virtual3, Virtual4, VirtualBase1, VirtualBase2, NonAggregateBase, PublicCtor,
  ProtectedCtor, PrivateCtor, DeletedPublicCtor, DeletedProtectedCtor, DeletedPrivateCtor
  // TODO: Double-check if these should be aggregates or not. All tested implementations (at the
  //  time of writing), when compiling in any C++ standard mode say that
  //  std::is_aggregate_v<X> == true for all three.
//   , InheritedPublicCtor, InheritedProtectedCtor, InheritedPrivateCtor
);

union OneIntVariant {
    [[maybe_unused]] int x;
};

union AggregateVariant {
    [[maybe_unused]] int x, y, z;
    [[maybe_unused]] AllPublicDerived pub;
};

union AggregateArrayVariant {
    [[maybe_unused]] int x, y, z[10];
    [[maybe_unused]] AllPublicDerived pub[10];
};

union NonAggregateVariant {
    [[maybe_unused]] int x, y, z;
    [[maybe_unused]] VirtualBase2 invalid;
};

union NonAggregateAndArrayVariant {
    [[maybe_unused]] int x, y, z[10];
    [[maybe_unused]] VirtualBase2 invalid;
};

union NonAggregateArrayVariant {
    [[maybe_unused]] int x, y, z;
    [[maybe_unused]] VirtualBase2 invalid[10];
};

TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_aggregate, EVERY_CV, OneIntVariant, AggregateVariant,
                               AggregateArrayVariant, NonAggregateVariant,
                               NonAggregateAndArrayVariant, NonAggregateArrayVariant);

int main() {
    return 0;
}
