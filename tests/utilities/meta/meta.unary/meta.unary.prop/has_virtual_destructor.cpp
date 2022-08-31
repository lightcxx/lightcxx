// REQUEST:COMPILE_OPTIONS "-Wno-non-virtual-dtor"

#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(has_virtual_destructor_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, has_virtual_destructor, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, has_virtual_destructor, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, has_virtual_destructor, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, has_virtual_destructor, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, has_virtual_destructor, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, has_virtual_destructor, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, has_virtual_destructor);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, has_virtual_destructor);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, has_virtual_destructor, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, has_virtual_destructor, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, has_virtual_destructor, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, has_virtual_destructor, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, has_virtual_destructor);

class VirtualBase : virtual Class {};

class VirtualMethod {
  public:
    virtual void f();
};

class PublicPolymorphicBase : public VirtualMethod {};

class ProtectedPolymorphicBase : protected VirtualMethod {};

class PrivatePolymorphicBase : private VirtualMethod {};

class VirtualPolymorphicBase : virtual VirtualMethod {};

class PureVirtualMethod {
  public:
    virtual void f() = 0;
};

class PublicAbstractBase : public PureVirtualMethod {};

class ProtectedAbstractBase : protected PureVirtualMethod {};

class PrivateAbstractBase : private PureVirtualMethod {};

class VirtualAbstractBase : virtual PureVirtualMethod {};

TEST_UNARY_TRAIT_AGAINST_TYPES(false, has_virtual_destructor, EVERY_CV, Class, VirtualBase, VirtualMethod, PublicPolymorphicBase, ProtectedPolymorphicBase,
                               PrivatePolymorphicBase, VirtualPolymorphicBase, PureVirtualMethod, PublicAbstractBase, ProtectedAbstractBase,
                               PrivateAbstractBase, VirtualAbstractBase);

class VirtualDtor {
  public:
    virtual ~VirtualDtor();
};

class PureVirtualDtor {
  public:
    virtual ~PureVirtualDtor() = 0;
};

class PublicVirtualDtorBase : public VirtualDtor {};
class ProtectedVirtualDtorBase : protected VirtualDtor {};
class PrivateVirtualDtorBase : private VirtualDtor {};
class VirtualVirtualDtorBase : virtual VirtualDtor {};

TEST_UNARY_TRAIT_AGAINST_TYPES(true, has_virtual_destructor, EVERY_CV, PureVirtualDtor, VirtualDtor, PublicVirtualDtorBase, ProtectedVirtualDtorBase,
                               PrivateVirtualDtorBase, VirtualVirtualDtorBase);
