#include <type_traits>

#include "meta/test_unary_trait.h"
#include "testing.h"

static_assert(std::is_same_v<std::add_rvalue_reference_t<int&>, int&&>);

template<class T, class U>
constexpr bool test_add_rvalue_reference() {
    static_assert(std::is_same_v<std::add_rvalue_reference_t<T>, U>);
    static_assert(std::is_same_v<typename std::add_rvalue_reference<T>::type, U>);
    return true;
}

namespace std {

template<class T>
struct TEST : bool_constant<test_add_rvalue_reference<T, T&&>()> {};

template<class T>
requires std::is_void_v<T>
struct TEST<T> : bool_constant<test_add_rvalue_reference<T, T>()> {
};

template<class T>
struct TEST<T&> : bool_constant<test_add_rvalue_reference<T&, T&&>()> {};

template<class T>
inline constexpr bool TEST_v = TEST<T>::value;

}  // namespace std

DECLARE_TRAIT_V_READER(TEST_v);

TEST_UNARY_TRAIT_AGAINST_VOID(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(true, TEST);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(true, TEST);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(true, TEST);
static_assert(test_add_rvalue_reference<int() const, int() const>());
static_assert(test_add_rvalue_reference<int() volatile, int() volatile>());
static_assert(test_add_rvalue_reference<int() const volatile, int() const volatile>());
