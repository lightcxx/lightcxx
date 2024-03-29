#include <type_traits>

#include "test_unary_trait.h"
#include "warnings.h"

DECLARE_TRAIT_V_READER(is_empty_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_empty, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_empty, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_empty, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_empty, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_empty, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_empty, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, is_empty);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, is_empty);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_empty, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_empty, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_empty, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_empty, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_empty);

class Empty {};
class EmptyDerived : public Empty {};
class EmptyDerivedTwo : public Empty {};
class EmptyDerivedTwice : public EmptyDerived {};
class DoubleEmptyDerived : public EmptyDerived, public EmptyDerivedTwo {};

class ZeroBits {
  public:
    signed char : 0;
    int : 0;
    short : 0;
};

class NoUniqueAddrEmptyMember {
  public:
    [[no_unique_address]] Empty e;
};

class FinalBoss : public DoubleEmptyDerived, private NoUniqueAddrEmptyMember {
  public:
    [[no_unique_address]] Empty e;
    [[no_unique_address]] EmptyDerived ed;
    [[no_unique_address]] ZeroBits z;
    [[no_unique_address]] NoUniqueAddrEmptyMember nua_mem;
};

TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_empty, EVERY_CV, Empty, EmptyDerived, EmptyDerivedTwo, EmptyDerivedTwice, DoubleEmptyDerived, ZeroBits,
                               NoUniqueAddrEmptyMember, FinalBoss);

class NonEmpty {
  public:
    int x, y;
};

// TODO: Clang returns true that this is_empty, investigate.
class Bits {
  public:
    char : 4;
};

WARNINGS_IGNORE_NON_VIRTUAL_DTOR()
class VirtualDtor {
  public:
    virtual ~VirtualDtor();
};

class VirtualMethod {
  public:
    virtual void f();
};

class PureVirtualMethod {
  public:
    virtual void f() = 0;
};

class VirtualBase : virtual Empty {};

class VirtualPolymorphicBase : virtual PureVirtualMethod {};

class PolymorphicBase : public VirtualMethod {};
WARNINGS_POP()

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_empty, EVERY_CV, NonEmpty, VirtualDtor, VirtualMethod, PureVirtualMethod, VirtualBase, VirtualPolymorphicBase,
                               PolymorphicBase);