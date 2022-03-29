#include "testing.h"

#include <type_traits>

TEST() {
    static_assert(std::integral_constant<int, 3>::value == 3);
    static_assert(std::integral_constant<bool, true>::value == true);
    static_assert(std::bool_constant<true>::value == true);
    static_assert(std::bool_constant<false>::value == false);
    static_assert(std::true_type::value == true);
    static_assert(std::false_type::value == false);

    static_assert(std::is_void<void>::value == true);
    static_assert(std::is_void_v<void> == true);

    static_assert(std::is_null_pointer<std::nullptr_t>::value == true);
    static_assert(std::is_null_pointer_v<std::nullptr_t> == true);

    static_assert(std::is_integral<int>::value == true);
    static_assert(std::is_integral_v<int> == true);

    static_assert(std::is_floating_point<float>::value == true);
    static_assert(std::is_floating_point_v<float> == true);

    static_assert(std::is_array<int[10]>::value == true);
    static_assert(std::is_array_v<int[10]> == true);

    static_assert(std::is_pointer<int*>::value == true);
    static_assert(std::is_pointer_v<int*> == true);

    static_assert(std::is_lvalue_reference<int&>::value == true);
    static_assert(std::is_lvalue_reference_v<int&> == true);

    static_assert(std::is_rvalue_reference<int&&>::value == true);
    static_assert(std::is_rvalue_reference_v<int&&> == true);

    static_assert(std::is_same_v<std::void_t<>, void>);
    static_assert(std::is_same_v<std::void_t<int>, void>);
    static_assert(std::is_same_v<std::void_t<int, long>, void>);
    static_assert(std::is_same_v<std::void_t<int, long, double>, void>);
}
