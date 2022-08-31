// REQUEST:COMPILE_OPTIONS "-Wno-non-virtual-dtor"

#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_final_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_final, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, is_final, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, is_final, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, is_final, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, is_final, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, is_final, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(false, is_final);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(false, is_final);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, is_final, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, is_final, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, is_final, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, is_final, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_final);

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

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_final, EVERY_CV, Class, VirtualBase, VirtualDtor, VirtualMethod, PublicPolymorphicBase, ProtectedPolymorphicBase,
                               PrivatePolymorphicBase, VirtualPolymorphicBase, PureVirtualDtor, PureVirtualMethod, PublicAbstractBase, ProtectedAbstractBase,
                               PrivateAbstractBase, VirtualAbstractBase);

class FinalNoBase final {};

class FinalPublicBase final : public Class {};

class FinalProtectedBase final : protected Class {};

class FinalPrivateBase final : private Class {};

class FinalVirtualBase final : virtual Class {};

TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_final, EVERY_CV, FinalNoBase, FinalPublicBase, FinalProtectedBase, FinalPrivateBase, FinalVirtualBase);