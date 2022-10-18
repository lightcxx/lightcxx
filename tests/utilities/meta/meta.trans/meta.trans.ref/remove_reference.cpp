#include <type_traits>

#include "test_unary_trait.h"
#include "testing.h"

template<class T, class U>
constexpr bool test_remove_reference() {
    static_assert(std::is_same_v<std::remove_reference_t<T>, U>);
    static_assert(std::is_same_v<typename std::remove_reference<T>::type, U>);
    return true;
}

namespace std {

template<class T>
struct TEST : bool_constant<test_remove_reference<T, T>()> {};

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
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(true, TEST);

static_assert(test_remove_reference<int&, int>());
static_assert(test_remove_reference<const int&, const int>());
static_assert(test_remove_reference<volatile int&, volatile int>());
static_assert(test_remove_reference<const volatile int&, const volatile int>());
static_assert(test_remove_reference<int (&)(int), int(int)>());
static_assert(test_remove_reference<int*&, int*>());
static_assert(test_remove_reference<int* const&, int* const>());
static_assert(test_remove_reference<int* volatile&, int* volatile>());
static_assert(test_remove_reference<int* const volatile&, int* const volatile>());
static_assert(test_remove_reference<incomplete_type&, incomplete_type>());
static_assert(test_remove_reference<const incomplete_type&, const incomplete_type>());
static_assert(test_remove_reference<volatile incomplete_type&, volatile incomplete_type>());
static_assert(test_remove_reference<const volatile incomplete_type&, const volatile incomplete_type>());
static_assert(test_remove_reference<int&&, int>());
static_assert(test_remove_reference<const int&&, const int>());
static_assert(test_remove_reference<volatile int&&, volatile int>());
static_assert(test_remove_reference<const volatile int&&, const volatile int>());
static_assert(test_remove_reference<int (&&)(int), int(int)>());
static_assert(test_remove_reference<int*&&, int*>());
static_assert(test_remove_reference<int* const&&, int* const>());
static_assert(test_remove_reference<int* volatile&&, int* volatile>());
static_assert(test_remove_reference<int* const volatile&&, int* const volatile>());
static_assert(test_remove_reference<incomplete_type&&, incomplete_type>());
static_assert(test_remove_reference<const incomplete_type&&, const incomplete_type>());
static_assert(test_remove_reference<volatile incomplete_type&&, volatile incomplete_type>());
static_assert(test_remove_reference<const volatile incomplete_type&&, const volatile incomplete_type>());
