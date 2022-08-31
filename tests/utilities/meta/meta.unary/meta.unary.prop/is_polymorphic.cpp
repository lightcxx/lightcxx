// REQUEST:COMPILE_OPTIONS "-Wno-non-virtual-dtor"

#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_polymorphic_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_polymorphic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_polymorphic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_polymorphic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_polymorphic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_polymorphic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_polymorphic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, is_polymorphic);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, is_polymorphic);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_polymorphic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_polymorphic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_polymorphic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_polymorphic, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_polymorphic);

class VirtualBase : virtual Class {};

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_polymorphic, EVERY_CV, Class, VirtualBase);

class VirtualDtor {
  public:
    virtual ~VirtualDtor();
};

class PureVirtualDtor {
  public:
    virtual ~PureVirtualDtor() = 0;
};

class VirtualMethod {
  public:
    virtual void f();
};

class PureVirtualMethod {
  public:
    virtual void f() = 0;
};

class PublicPolymorphicBase : public VirtualMethod {};

class ProtectedPolymorphicBase : protected VirtualMethod {};

class PrivatePolymorphicBase : private VirtualMethod {};

class VirtualPolymorphicBase : virtual PureVirtualMethod {};

TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_polymorphic, EVERY_CV, VirtualDtor, PureVirtualDtor, VirtualMethod, PureVirtualMethod, PublicPolymorphicBase,
                               ProtectedPolymorphicBase, PrivatePolymorphicBase, VirtualPolymorphicBase);