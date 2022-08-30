#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_nothrow_destructible_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_nothrow_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_nothrow_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_nothrow_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_nothrow_destructible, EVERY_CV);
// TEST_UNARY_TRAIT_AGAINST_ARRAY(true, is_nothrow_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_nothrow_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(true, is_nothrow_destructible);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(true, is_nothrow_destructible);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_nothrow_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_nothrow_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_nothrow_destructible, EVERY_CV);
// TEST_UNARY_TRAIT_AGAINST_UNION(true, is_nothrow_destructible, EVERY_CV); // Special tests
// TEST_UNARY_TRAIT_AGAINST_CLASS(true, is_nothrow_destructible, EVERY_CV); // Special tests
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_nothrow_destructible);

class ClassWithDeletedDtor {
  public:
    ~ClassWithDeletedDtor() = delete;
};

class ClassWithDeletedDtorMember {
  public:
    ClassWithDeletedDtor d;
};

class ClassWithProtectedDtor {
  protected:
    ~ClassWithProtectedDtor() {}
};

class ClassWithPrivateDtor {
  private:
    ~ClassWithPrivateDtor() {}
};

class ClassWithPrivateDtorBase : public ClassWithPrivateDtor {};

class ClassWithDefinedThrowingDtor {
  public:
    int x;
    int y;

    ~ClassWithDefinedThrowingDtor() noexcept(false) {}
};

class ClassWithThrowingDtorBase : public ClassWithDefinedThrowingDtor {};

class ClassWithThrowingDtorMember {
  public:
    ClassWithDefinedThrowingDtor member;
};

class IncompleteClass;

union UnionWithDeletedDtor {
    int x;
    char c[4];

    ~UnionWithDeletedDtor() = delete;
};

union UnionWithProtectedDtor {
    int x;
    char c[4];

  protected:
    ~UnionWithProtectedDtor() {}
};

union UnionWithPrivateDtor {
    int x;
    char c[4];

  protected:
    ~UnionWithPrivateDtor() {}
};

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_nothrow_destructible, EVERY_CV, ClassWithDeletedDtor, ClassWithDeletedDtorMember, ClassWithProtectedDtor,
                               ClassWithPrivateDtor, ClassWithPrivateDtorBase, ClassWithDefinedThrowingDtor, ClassWithThrowingDtorBase,
                               ClassWithThrowingDtorMember, IncompleteClass, UnionWithDeletedDtor, UnionWithProtectedDtor, UnionWithPrivateDtor,
                               ClassWithDeletedDtor[], ClassWithDeletedDtorMember[], ClassWithProtectedDtor[], ClassWithPrivateDtor[],
                               ClassWithPrivateDtorBase[], ClassWithDefinedThrowingDtor[], ClassWithThrowingDtorBase[], ClassWithThrowingDtorMember[],
                               IncompleteClass[], UnionWithDeletedDtor[], UnionWithProtectedDtor[], UnionWithPrivateDtor[], ClassWithDeletedDtor[10],
                               ClassWithDeletedDtorMember[10], ClassWithProtectedDtor[10], ClassWithPrivateDtor[10], ClassWithPrivateDtorBase[10],
                               ClassWithDefinedThrowingDtor[10], ClassWithThrowingDtorBase[10], ClassWithThrowingDtorMember[10], IncompleteClass[10],
                               UnionWithDeletedDtor[10], UnionWithProtectedDtor[10], UnionWithPrivateDtor[10], ClassWithDeletedDtor[][10],
                               ClassWithDeletedDtorMember[][10], ClassWithProtectedDtor[][10], ClassWithPrivateDtor[][10], ClassWithPrivateDtorBase[][10],
                               ClassWithDefinedThrowingDtor[][10], ClassWithThrowingDtorBase[][10], ClassWithThrowingDtorMember[][10], IncompleteClass[][10],
                               UnionWithDeletedDtor[][10], UnionWithProtectedDtor[][10], UnionWithPrivateDtor[][10]);

class ClassWithDefinedDtor {
  public:
    int x;
    int y;

    ~ClassWithDefinedDtor() {}
};

class ClassWithDefaultedDtor {
  public:
    int x;
    int y;

    ClassWithDefaultedDtor() = default;
};

union UnionWithDefinedDtor {
    int x;
    char c[4];

    ~UnionWithDefinedDtor() {}
};

union UnionWithDefaultedDtor {
    int x;
    char c[4];

    ~UnionWithDefaultedDtor() = default;
};

class ClassWithProtectedDtorBase : public ClassWithProtectedDtor {};

class ClassWithProtectedDtorBaseAndDefinedDtor : public ClassWithProtectedDtor {
  public:
    ~ClassWithProtectedDtorBaseAndDefinedDtor() {}
};

TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_nothrow_destructible, EVERY_CV, ClassWithDefinedDtor, ClassWithDefaultedDtor, UnionWithDefinedDtor,
                               UnionWithDefaultedDtor, ClassWithProtectedDtorBase, ClassWithProtectedDtorBaseAndDefinedDtor, ClassWithDefinedDtor[],
                               ClassWithDefaultedDtor[], UnionWithDefinedDtor[], UnionWithDefaultedDtor[], ClassWithProtectedDtorBase[],
                               ClassWithProtectedDtorBaseAndDefinedDtor[], ClassWithDefinedDtor[10], ClassWithDefaultedDtor[10], UnionWithDefinedDtor[10],
                               UnionWithDefaultedDtor[10], ClassWithProtectedDtorBase[10], ClassWithProtectedDtorBaseAndDefinedDtor[10],
                               ClassWithDefinedDtor[][10], ClassWithDefaultedDtor[][10], UnionWithDefinedDtor[][10], UnionWithDefaultedDtor[][10],
                               ClassWithProtectedDtorBase[][10], ClassWithProtectedDtorBaseAndDefinedDtor[][10]);
