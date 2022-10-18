#include <type_traits>

#include "test_unary_trait.h"
#include "testing.h"

template<class T>
constexpr bool test_add_volatile() {
    static_assert(std::is_same_v<std::add_volatile_t<T>, volatile T>);
    static_assert(std::is_same_v<typename std::add_volatile<T>::type, volatile T>);

    static_assert(std::is_same_v<std::add_volatile_t<const T>, const volatile T>);
    static_assert(std::is_same_v<typename std::add_volatile<const T>::type, const volatile T>);

    static_assert(std::is_same_v<std::add_volatile_t<volatile T>, volatile T>);
    static_assert(std::is_same_v<typename std::add_volatile<volatile T>::type, volatile T>);

    static_assert(std::is_same_v<std::add_volatile_t<const volatile T>, const volatile T>);
    static_assert(std::is_same_v<typename std::add_volatile<const volatile T>::type, const volatile T>);

    return true;
}

namespace std {

template<class T>
struct TEST : bool_constant<test_add_volatile<T>()> {};

template<class T>
inline constexpr bool TEST_v = test_add_volatile<T>();

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
