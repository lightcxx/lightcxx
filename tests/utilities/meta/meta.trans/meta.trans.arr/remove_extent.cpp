#include <type_traits>

#include "meta/test_unary_trait.h"
#include "testing.h"

template<class T, class U>
constexpr bool test_remove_extent() {
    static_assert(std::is_same_v<std::remove_extent_t<T>, U>);
    static_assert(std::is_same_v<typename std::remove_extent<T>::type, U>);
    return true;
}

template<class T>
constexpr bool test_remove_extent_non_array_type() {
    return test_remove_extent<T, T>();
}

namespace std {

template<class T>
struct TEST : bool_constant<test_remove_extent_non_array_type<T>()> {};

template<class T>
inline constexpr bool TEST_v = test_remove_extent_non_array_type<T>();

}  // namespace std

DECLARE_TRAIT_V_READER(TEST_v);

TEST_UNARY_TRAIT_AGAINST_VOID(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, TEST, NO_CV);

static_assert(test_remove_extent<int[2], int>());
static_assert(test_remove_extent<int[2][3], int[3]>());
static_assert(test_remove_extent<int[2][3][4], int[3][4]>());
static_assert(test_remove_extent<int[], int>());
static_assert(test_remove_extent<int[][3], int[3]>());
static_assert(test_remove_extent<int[][3][4], int[3][4]>());
// Doesn't work for reference to array
static_assert(test_remove_extent<int(&)[][3][4], int(&)[][3][4]>());
static_assert(test_remove_extent<int(&)[2][3][4], int(&)[2][3][4]>());

TEST_UNARY_TRAIT_AGAINST_POINTER(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(true, TEST);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(true, TEST);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(true, TEST, NO_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(true, TEST);
