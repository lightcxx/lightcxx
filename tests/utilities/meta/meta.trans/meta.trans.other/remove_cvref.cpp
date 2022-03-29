#include <type_traits>

#include "meta/test_unary_trait.h"
#include "testing.h"

template<class T, class U>
constexpr bool test_remove_cvref() {
    static_assert(std::is_same_v<std::remove_cvref_t<T>, U>);
    static_assert(std::is_same_v<typename std::remove_cvref<T>::type, U>);
    static_assert(std::is_same_v<std::remove_cvref_t<const T>, U>);
    static_assert(std::is_same_v<typename std::remove_cvref<const T>::type, U>);
    static_assert(std::is_same_v<std::remove_cvref_t<volatile T>, U>);
    static_assert(std::is_same_v<typename std::remove_cvref<volatile T>::type, U>);
    static_assert(std::is_same_v<std::remove_cvref_t<const volatile T>, U>);
    static_assert(std::is_same_v<typename std::remove_cvref<const volatile T>::type, U>);
    return true;
}

namespace std {

template<class T>
struct TEST : bool_constant<test_remove_cvref<T, T>()> {};

template<class T>
inline constexpr bool TEST_v = TEST<T>::value;

}  // namespace std

DECLARE_TRAIT_V_READER(TEST_v);

TEST_UNARY_TRAIT_AGAINST_VOID(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(true, TEST);

static_assert(test_remove_cvref<int&, int>());
static_assert(test_remove_cvref<const int&, int>());
static_assert(test_remove_cvref<volatile int&, int>());
static_assert(test_remove_cvref<const volatile int&, int>());
static_assert(test_remove_cvref<int (&)(int), int(int)>());
static_assert(test_remove_cvref<int*&, int*>());
static_assert(test_remove_cvref<int* const&, int*>());
static_assert(test_remove_cvref<int* volatile&, int*>());
static_assert(test_remove_cvref<int* const volatile&, int*>());
static_assert(test_remove_cvref<incomplete_type&, incomplete_type>());
static_assert(test_remove_cvref<const incomplete_type&, incomplete_type>());
static_assert(test_remove_cvref<volatile incomplete_type&, incomplete_type>());
static_assert(test_remove_cvref<const volatile incomplete_type&, incomplete_type>());
static_assert(test_remove_cvref<int&&, int>());
static_assert(test_remove_cvref<const int&&, int>());
static_assert(test_remove_cvref<volatile int&&, int>());
static_assert(test_remove_cvref<const volatile int&&, int>());
static_assert(test_remove_cvref<int(&&)(int), int(int)>());
static_assert(test_remove_cvref<int*&&, int*>());
static_assert(test_remove_cvref<int* const&&, int*>());
static_assert(test_remove_cvref<int* volatile&&, int*>());
static_assert(test_remove_cvref<int* const volatile&&, int*>());
static_assert(test_remove_cvref<incomplete_type&&, incomplete_type>());
static_assert(test_remove_cvref<const incomplete_type&&, incomplete_type>());
static_assert(test_remove_cvref<volatile incomplete_type&&, incomplete_type>());
static_assert(test_remove_cvref<const volatile incomplete_type&&, incomplete_type>());
