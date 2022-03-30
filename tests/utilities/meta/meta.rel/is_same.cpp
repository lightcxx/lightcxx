#include <type_traits>

#include "meta/test_unary_trait.h"

namespace std {
template<class T>
using test_is_same_true = std::is_same<T, T>;

template<class T>
inline constexpr auto test_is_same_true_v = std::is_same_v<T, T>;

template<class T>
using test_is_same_different_cv1 = is_same<T, const T>;

template<class T>
inline constexpr auto test_is_same_different_cv1_v = is_same_v<T, const T>;

template<class T>
using test_is_same_different_cv2 = std::is_same<const volatile T, T>;

template<class T>
inline constexpr auto test_is_same_different_cv2_v = is_same_v<const volatile T, T>;
}  // namespace std

DECLARE_TRAIT_V_READER(test_is_same_true_v);
DECLARE_TRAIT_V_READER(test_is_same_different_cv1_v);
DECLARE_TRAIT_V_READER(test_is_same_different_cv2_v);

TEST_UNARY_TRAIT_AGAINST_VOID(true, test_is_same_true, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, test_is_same_true, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, test_is_same_true, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, test_is_same_true, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(true, test_is_same_true, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, test_is_same_true, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(true, test_is_same_true);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(true, test_is_same_true);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, test_is_same_true, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, test_is_same_true, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, test_is_same_true, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(true, test_is_same_true, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(true, test_is_same_true, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(true, test_is_same_true);

TEST_UNARY_TRAIT_AGAINST_VOID(false, test_is_same_different_cv1, NO_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, test_is_same_different_cv1, NO_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, test_is_same_different_cv1, NO_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, test_is_same_different_cv1, NO_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, test_is_same_different_cv1, NO_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, test_is_same_different_cv1, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, test_is_same_different_cv1, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, test_is_same_different_cv1, NO_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, test_is_same_different_cv1, NO_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, test_is_same_different_cv1, NO_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, test_is_same_different_cv1, NO_CV);

TEST_UNARY_TRAIT_AGAINST_VOID(false, test_is_same_different_cv2, NO_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(false, test_is_same_different_cv2, NO_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(false, test_is_same_different_cv2, NO_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(false, test_is_same_different_cv2, NO_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(false, test_is_same_different_cv2, NO_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(false, test_is_same_different_cv2, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(false, test_is_same_different_cv2, NO_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(false, test_is_same_different_cv2, NO_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(false, test_is_same_different_cv2, NO_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(false, test_is_same_different_cv2, NO_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(false, test_is_same_different_cv2, NO_CV);

// Test some conversion/similar type cases
static_assert(!std::is_same_v<void*, std::nullptr_t>);
static_assert(!std::is_same_v<int, long>);
static_assert(!std::is_same_v<int(), int (&)()>);
static_assert(!std::is_same_v<int (*)(), int (&)()>);
static_assert(!std::is_same_v<int (*)(), int()>);
static_assert(!std::is_same_v<int (*)(int), int (*)(long)>);
static_assert(!std::is_same_v<int (*)(int), long (*)(int)>);
static_assert(!std::is_same_v<int*, int[]>);
static_assert(!std::is_same_v<int*, int[10]>);
static_assert(!std::is_same_v<int*, int[][10]>);
static_assert(!std::is_same_v<int[], int[10]>);
