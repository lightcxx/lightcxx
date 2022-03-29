#include <type_traits>

#include "meta/test_unary_trait.h"
#include "testing.h"

template<class T, class U>
constexpr bool test_add_pointer_base() {
    static_assert(std::is_same_v<std::add_pointer_t<T>, U>);
    static_assert(std::is_same_v<typename std::add_pointer<T>::type, U>);
    return true;
}

template<class T>
constexpr bool test_add_pointer() {
    return test_add_pointer_base<T, T*>();
}

template<class T>
constexpr bool test_add_pointer_to_ref_type() {
    return test_add_pointer_base<T, std::remove_reference_t<T>*>();
}

namespace std {

template<class T>
struct TEST : bool_constant<test_add_pointer<T>()> {};

template<class T>
inline constexpr bool TEST_v = test_add_pointer<T>();

template<class T>
struct TEST_ref : bool_constant<test_add_pointer_to_ref_type<T>()> {};

template<class T>
inline constexpr bool TEST_ref_v = test_add_pointer_to_ref_type<T>();

}  // namespace std

DECLARE_TRAIT_V_READER(TEST_v);
DECLARE_TRAIT_V_READER(TEST_ref_v);

TEST_UNARY_TRAIT_AGAINST_VOID(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_NULLPTR_T(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_INTEGRAL(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FLOATING_POINT(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ARRAY(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_POINTER(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_LVALUE_REFERENCE(true, TEST_ref);
TEST_UNARY_TRAIT_AGAINST_RVALUE_REFERENCE(true, TEST_ref);
TEST_UNARY_TRAIT_AGAINST_MEMBER_OBJECT_POINTER(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_MEMBER_FUNCTION_POINTER(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_ENUM(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_UNION(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_CLASS(true, TEST, EVERY_CV);
TEST_UNARY_TRAIT_AGAINST_FUNCTION(true, TEST);
static_assert(test_add_pointer_base<int() const, int() const>());
static_assert(test_add_pointer_base<int() volatile, int() volatile>());
static_assert(test_add_pointer_base<int() const volatile, int() const volatile>());
