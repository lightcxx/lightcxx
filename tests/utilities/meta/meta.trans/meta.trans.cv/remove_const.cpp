#include <type_traits>

#include "test_unary_trait.h"
#include "testing.h"

template<class T>
constexpr bool test_remove_const() {
    static_assert(std::is_same_v<std::remove_const_t<T>, T>);
    static_assert(std::is_same_v<typename std::remove_const<T>::type, T>);

    static_assert(std::is_same_v<std::remove_const_t<const T>, T>);
    static_assert(std::is_same_v<typename std::remove_const<const T>::type, T>);

    static_assert(std::is_same_v<std::remove_const_t<volatile T>, volatile T>);
    static_assert(std::is_same_v<typename std::remove_const<volatile T>::type, volatile T>);

    static_assert(std::is_same_v<std::remove_const_t<const volatile T>, volatile T>);
    static_assert(std::is_same_v<typename std::remove_const<const volatile T>::type, volatile T>);

    return true;
}

namespace std {

template<class T>
struct TEST : bool_constant<test_remove_const<T>()> {};

template<class T>
inline constexpr bool TEST_v = test_remove_const<T>();

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
