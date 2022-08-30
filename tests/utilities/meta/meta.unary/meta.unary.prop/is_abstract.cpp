#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_abstract_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_abstract, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_abstract, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_abstract, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_abstract, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_abstract, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_abstract, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, is_abstract);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, is_abstract);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_abstract, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_abstract, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_abstract, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_abstract, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_abstract);

class VirtualBase : virtual Class {};

class VirtualDtor {
  public:
    virtual ~VirtualDtor();
};

class VirtualMethod {
  public:
    virtual void f();
};

class PublicPolymorphicBase : public VirtualMethod {};

class ProtectedPolymorphicBase : protected VirtualMethod {};

class PrivatePolymorphicBase : private VirtualMethod {};

class VirtualPolymorphicBase : virtual VirtualMethod {};

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_abstract, EVERY_CV, Class, VirtualBase, VirtualDtor, VirtualMethod, PublicPolymorphicBase, ProtectedPolymorphicBase,
                               PrivatePolymorphicBase, VirtualPolymorphicBase);

class PureVirtualDtor {
  public:
    virtual ~PureVirtualDtor() = 0;
};

class PureVirtualMethod {
  public:
    virtual void f() = 0;
};

class PublicAbstractBase : public PureVirtualMethod {};

class ProtectedAbstractBase : protected PureVirtualMethod {};

class PrivateAbstractBase : private PureVirtualMethod {};

class VirtualAbstractBase : virtual PureVirtualMethod {};

TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_abstract, EVERY_CV, PureVirtualDtor, PureVirtualMethod, PublicAbstractBase, ProtectedAbstractBase, PrivateAbstractBase,
                               VirtualAbstractBase);