#include <type_traits>

#include "meta/test_unary_trait.h"
#include "testing.h"

template<class T, class U>
constexpr bool test_remove_all_extents() {
    static_assert(std::is_same_v<std::remove_all_extents_t<T>, U>);
    static_assert(std::is_same_v<typename std::remove_all_extents<T>::type, U>);
    return true;
}

template<class T>
constexpr bool test_remove_all_extents_non_array_type() {
    return test_remove_all_extents<T, T>();
}

namespace std {

template<class T>
struct TEST : bool_constant<test_remove_all_extents_non_array_type<T>()> {};

template<class T>
inline constexpr bool TEST_v = test_remove_all_extents_non_array_type<T>();

}  // namespace std

DECLARE_TRAIT_V_READER(TEST_v);

TEST_UNARY_TRAIT_AGAINST_VOID(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, TEST, EVERY_CV);

static_assert(test_remove_all_extents<int[2], int>());
static_assert(test_remove_all_extents<int[2][3], int>());
static_assert(test_remove_all_extents<int[2][3][4], int>());
static_assert(test_remove_all_extents<int[], int>());
static_assert(test_remove_all_extents<int[][3], int>());
static_assert(test_remove_all_extents<int[][3][4], int>());
// Doesn't work for reference to array
static_assert(test_remove_all_extents<int (&)[][3][4], int (&)[][3][4]>());
static_assert(test_remove_all_extents<int (&)[2][3][4], int (&)[2][3][4]>());

TEST_UNARY_TRAIT_AGAINST_POINTER(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(true, TEST);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(true, TEST);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(true, TEST);

TEST(example_from_std) {
    static_assert(std::is_same_v<std::remove_all_extents_t<int>, int>);
    ;
    static_assert(std::is_same_v<std::remove_all_extents_t<int[2]>, int>);
    ;
    static_assert(std::is_same_v<std::remove_all_extents_t<int[2][3]>, int>);
    ;
    static_assert(std::is_same_v<std::remove_all_extents_t<int[][3]>, int>);
    ;
}
