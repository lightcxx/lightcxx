// REQUEST:NO_TEST_LIB "The testing library depends on <type_traits>."

#include <type_traits>

#include "meta/test_unary_trait.h"

DECLARE_TRAIT_V_READER(is_destructible_v);

TEST_UNARY_TRAIT_AGAINST_VOID(false, is_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, is_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, is_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, is_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(true, is_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, is_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(true, is_destructible);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(true, is_destructible);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, is_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, is_destructible, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, is_destructible, EVERY_CV);
// TEST_UNARY_TRAIT_AGAINST_UNION(true, is_destructible, EVERY_CV); // Special tests
// TEST_UNARY_TRAIT_AGAINST_CLASS(true, is_destructible, EVERY_CV); // Special tests
TEST_UNARY_TRAIT_AGAINST_FUNCTION(false, is_destructible);

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

class IncompleteClass;

union UnionWithDeletedDtor {
    [[maybe_unused]] int x;
    [[maybe_unused]] char c[4];

    ~UnionWithDeletedDtor() = delete;
};

union UnionWithProtectedDtor {
    [[maybe_unused]] int x;
    [[maybe_unused]] char c[4];

  protected:
    ~UnionWithProtectedDtor() {}
};

union UnionWithPrivateDtor {
    [[maybe_unused]] int x;
    [[maybe_unused]] char c[4];

  protected:
    ~UnionWithPrivateDtor() {}
};

TEST_UNARY_TRAIT_AGAINST_TYPES(false, is_destructible, EVERY_CV, ClassWithDeletedDtor,
                               ClassWithDeletedDtorMember, ClassWithProtectedDtor,
                               ClassWithPrivateDtor, ClassWithPrivateDtorBase, IncompleteClass,
                               UnionWithDeletedDtor, UnionWithProtectedDtor, UnionWithPrivateDtor);

class ClassWithDefinedDtor {
  public:
    [[maybe_unused]] int x;
    [[maybe_unused]] int y;

    ~ClassWithDefinedDtor() {}
};

class ClassWithDefaultedDtor {
  public:
    [[maybe_unused]] int x;
    [[maybe_unused]] int y;

    ClassWithDefaultedDtor() = default;
};

union UnionWithDefinedDtor {
    [[maybe_unused]] int x;
    [[maybe_unused]] char c[4];

    ~UnionWithDefinedDtor() {}
};

union UnionWithDefaultedDtor {
    [[maybe_unused]] int x;
    [[maybe_unused]] char c[4];

    ~UnionWithDefaultedDtor() = default;
};

class ClassWithProtectedDtorBase : public ClassWithProtectedDtor {};

class ClassWithProtectedDtorBaseAndDefinedDtor : public ClassWithProtectedDtor {
  public:
    ~ClassWithProtectedDtorBaseAndDefinedDtor() {}
};

TEST_UNARY_TRAIT_AGAINST_TYPES(true, is_destructible, EVERY_CV, ClassWithDefinedDtor,
                               ClassWithDefaultedDtor, UnionWithDefinedDtor, UnionWithDefaultedDtor,
                               ClassWithProtectedDtorBase,
                               ClassWithProtectedDtorBaseAndDefinedDtor);

int main() {
    return 0;
}