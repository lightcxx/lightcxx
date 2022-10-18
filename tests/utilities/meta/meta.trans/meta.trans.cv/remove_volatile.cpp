#include <type_traits>

#include "test_unary_trait.h"
#include "testing.h"

template<class T>
constexpr bool test_remove_volatile() {
    static_assert(std::is_same_v<std::remove_volatile_t<T>, T>);
    static_assert(std::is_same_v<typename std::remove_volatile<T>::type, T>);

    static_assert(std::is_same_v<std::remove_volatile_t<const T>, const T>);
    static_assert(std::is_same_v<typename std::remove_volatile<const T>::type, const T>);

    static_assert(std::is_same_v<std::remove_volatile_t<volatile T>, T>);
    static_assert(std::is_same_v<typename std::remove_volatile<volatile T>::type, T>);

    static_assert(std::is_same_v<std::remove_volatile_t<const volatile T>, const T>);
    static_assert(std::is_same_v<typename std::remove_volatile<const volatile T>::type, const T>);

    return true;
}

namespace std {

template<class T>
struct TEST : bool_constant<test_remove_volatile<T>()> {};

template<class T>
inline constexpr bool TEST_v = test_remove_volatile<T>();

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
