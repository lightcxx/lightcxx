#include <type_traits>

#include "meta/test_unary_trait.h"
#include "testing.h"

template<class T>
constexpr bool test_add_cv() {
    static_assert(std::is_same_v<std::add_cv_t<T>, const volatile T>);
    static_assert(std::is_same_v<typename std::add_cv<T>::type, const volatile T>);

    static_assert(std::is_same_v<std::add_cv_t<const T>, const volatile T>);
    static_assert(std::is_same_v<typename std::add_cv<const T>::type, const volatile T>);

    static_assert(std::is_same_v<std::add_cv_t<volatile T>, const volatile T>);
    static_assert(std::is_same_v<typename std::add_cv<volatile T>::type, const volatile T>);

    static_assert(std::is_same_v<std::add_cv_t<const volatile T>, const volatile T>);
    static_assert(std::is_same_v<typename std::add_cv<const volatile T>::type, const volatile T>);

    return true;
}

namespace std {

template<class T>
struct TEST : bool_constant<test_add_cv<T>()> {};

template<class T>
inline constexpr bool TEST_v = test_add_cv<T>();

}  // namespace std

DECLARE_TRAIT_V_READER(TEST_v);

TEST_UNARY_TRAIT_AGAINST_VOID(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(true, TEST);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(true, TEST);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(true, TEST);
