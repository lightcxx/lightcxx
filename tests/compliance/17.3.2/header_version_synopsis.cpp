#include <version>

#include "lightcxx_test.h"

void LightCXXTest::run() noexcept {
    expectTypeAndValue<long&&>(__cpp_lib_addressof_constexpr, 201603L, "addressof_constexpr");
    expectTypeAndValue<long&&>(
      __cpp_lib_allocator_traits_is_always_equal, 201411L, "allocator_traits_is_always_equal");
    expectTypeAndValue<long&&>(__cpp_lib_any, 201606L, "any");
    expectTypeAndValue<long&&>(__cpp_lib_apply, 201603L, "apply");
    expectTypeAndValue<long&&>(__cpp_lib_array_constexpr, 201811L, "array_constexpr");
    expectTypeAndValue<long&&>(__cpp_lib_as_const, 201510L, "as_const");
    expectTypeAndValue<long&&>(__cpp_lib_assume_aligned, 201811L, "assume_aligned");
    expectTypeAndValue<long&&>(__cpp_lib_atomic_flag_test, 201907L, "atomic_flag_test");
    expectTypeAndValue<long&&>(__cpp_lib_atomic_float, 201711L, "atomic_float");
    expectTypeAndValue<long&&>(
      __cpp_lib_atomic_is_always_lock_free, 201603L, "atomic_is_always_lock_free");
    expectTypeAndValue<long&&>(
      __cpp_lib_atomic_lock_free_type_aliases, 201907L, "atomic_lock_free_type_aliases");
    expectTypeAndValue<long&&>(__cpp_lib_atomic_ref, 201806L, "atomic_ref");
    expectTypeAndValue<long&&>(__cpp_lib_atomic_shared_ptr, 201711L, "atomic_shared_ptr");
    expectTypeAndValue<long&&>(
      __cpp_lib_atomic_value_initialization, 201911L, "atomic_value_initialization");
    expectTypeAndValue<long&&>(__cpp_lib_atomic_wait, 201907L, "atomic_wait");
    expectTypeAndValue<long&&>(__cpp_lib_barrier, 201907L, "barrier");
    expectTypeAndValue<long&&>(__cpp_lib_bind_front, 201907L, "bind_front");
    expectTypeAndValue<long&&>(__cpp_lib_bit_cast, 201806L, "bit_cast");
    expectTypeAndValue<long&&>(__cpp_lib_bitops, 201907L, "bitops");
    expectTypeAndValue<long&&>(__cpp_lib_bool_constant, 201505L, "bool_constant");
    expectTypeAndValue<long&&>(__cpp_lib_bounded_array_traits, 201902L, "bounded_array_traits");

    expectTypeAndValue<long&&>(__cpp_lib_boyer_moore_searcher, 201603L, "boyer_moore_searcher");
    expectTypeAndValue<long&&>(__cpp_lib_byte, 201603L, "byte");
    expectTypeAndValue<long&&>(__cpp_lib_char8_t, 201907L, "char8_t");
    expectTypeAndValue<long&&>(__cpp_lib_chrono, 201907L, "chrono");
    expectTypeAndValue<long&&>(__cpp_lib_chrono_udls, 201304L, "chrono_udls");
    expectTypeAndValue<long&&>(__cpp_lib_clamp, 201603L, "clamp");
    expectTypeAndValue<long&&>(__cpp_lib_complex_udls, 201309L, "complex_udls");
    expectTypeAndValue<long&&>(__cpp_lib_concepts, 202002L, "concepts");
    expectTypeAndValue<long&&>(__cpp_lib_constexpr_algorithms, 201806L, "constexpr_algorithms");
    expectTypeAndValue<long&&>(__cpp_lib_constexpr_complex, 201711L, "constexpr_complex");
    expectTypeAndValue<long&&>(
      __cpp_lib_constexpr_dynamic_alloc, 201907L, "constexpr_dynamic_alloc");
    expectTypeAndValue<long&&>(__cpp_lib_constexpr_functional, 201907L, "constexpr_functional");
    expectTypeAndValue<long&&>(__cpp_lib_constexpr_iterator, 201811L, "constexpr_iterator");
    expectTypeAndValue<long&&>(__cpp_lib_constexpr_memory, 201811L, "constexpr_memory");
    expectTypeAndValue<long&&>(__cpp_lib_constexpr_numeric, 201911L, "constexpr_numeric");
    expectTypeAndValue<long&&>(__cpp_lib_constexpr_string, 201907L, "constexpr_string");
    expectTypeAndValue<long&&>(__cpp_lib_constexpr_string_view, 201811L, "constexpr_string_view");
    expectTypeAndValue<long&&>(__cpp_lib_constexpr_tuple, 201811L, "constexpr_tuple");
    expectTypeAndValue<long&&>(__cpp_lib_constexpr_utility, 201811L, "constexpr_utility");
    expectTypeAndValue<long&&>(__cpp_lib_constexpr_vector, 201907L, "constexpr_vector");
    expectTypeAndValue<long&&>(__cpp_lib_coroutine, 201902L, "coroutine");
    expectTypeAndValue<long&&>(__cpp_lib_destroying_delete, 201806L, "destroying_delete");
    expectTypeAndValue<long&&>(
      __cpp_lib_enable_shared_from_this, 201603L, "enable_shared_from_this");
    expectTypeAndValue<long&&>(__cpp_lib_endian, 201907L, "endian");
    expectTypeAndValue<long&&>(__cpp_lib_erase_if, 202002L, "erase_if");
    expectTypeAndValue<long&&>(__cpp_lib_exchange_function, 201304L, "exchange_function");
    expectTypeAndValue<long&&>(__cpp_lib_execution, 201902L, "execution");
    expectTypeAndValue<long&&>(__cpp_lib_filesystem, 201703L, "filesystem");
    expectTypeAndValue<long&&>(__cpp_lib_format, 201907L, "format");
    expectTypeAndValue<long&&>(__cpp_lib_gcd_lcm, 201606L, "gcd_lcm");
    expectTypeAndValue<long&&>(
      __cpp_lib_generic_associative_lookup, 201304L, "generic_associative_lookup");
    expectTypeAndValue<long&&>(
      __cpp_lib_generic_unordered_lookup, 201811L, "generic_unordered_lookup");
    expectTypeAndValue<long&&>(
      __cpp_lib_hardware_interference_size, 201703L, "hardware_interference_size");
    expectTypeAndValue<long&&>(
      __cpp_lib_has_unique_object_representations, 201606L, "has_unique_object_representations");
    expectTypeAndValue<long&&>(__cpp_lib_hypot, 201603L, "hypot");
    expectTypeAndValue<long&&>(
      __cpp_lib_incomplete_container_elements, 201505L, "incomplete_container_elements");
    expectTypeAndValue<long&&>(__cpp_lib_int_pow2, 202002L, "int_pow2");
    expectTypeAndValue<long&&>(
      __cpp_lib_integer_comparison_functions, 202002L, "integer_comparison_functions");
    expectTypeAndValue<long&&>(__cpp_lib_integer_sequence, 201304L, "integer_sequence");
    expectTypeAndValue<long&&>(
      __cpp_lib_integral_constant_callable, 201304L, "integral_constant_callable");
    expectTypeAndValue<long&&>(__cpp_lib_interpolate, 201902L, "interpolate");
    expectTypeAndValue<long&&>(__cpp_lib_invoke, 201411L, "invoke");
    expectTypeAndValue<long&&>(__cpp_lib_is_aggregate, 201703L, "is_aggregate");
    expectTypeAndValue<long&&>(__cpp_lib_is_constant_evaluated, 201811L, "is_constant_evaluated");
    expectTypeAndValue<long&&>(__cpp_lib_is_final, 201402L, "is_final");
    expectTypeAndValue<long&&>(__cpp_lib_is_invocable, 201703L, "is_invocable");
    expectTypeAndValue<long&&>(__cpp_lib_is_layout_compatible, 201907L, "is_layout_compatible");
    expectTypeAndValue<long&&>(__cpp_lib_is_nothrow_convertible, 201806L, "is_nothrow_convertible");
    expectTypeAndValue<long&&>(__cpp_lib_is_null_pointer, 201309L, "is_null_pointer");
    expectTypeAndValue<long&&>(
      __cpp_lib_is_pointer_interconvertible, 201907L, "is_pointer_interconvertible");
    expectTypeAndValue<long&&>(__cpp_lib_is_swappable, 201603L, "is_swappable");
    expectTypeAndValue<long&&>(__cpp_lib_jthread, 201911L, "jthread");
    expectTypeAndValue<long&&>(__cpp_lib_latch, 201907L, "latch");
    expectTypeAndValue<long&&>(__cpp_lib_launder, 201606L, "launder");
    expectTypeAndValue<long&&>(
      __cpp_lib_list_remove_return_type, 201806L, "list_remove_return_type");
    expectTypeAndValue<long&&>(__cpp_lib_logical_traits, 201510L, "logical_traits");
    expectTypeAndValue<long&&>(__cpp_lib_make_from_tuple, 201606L, "make_from_tuple");
    expectTypeAndValue<long&&>(__cpp_lib_make_reverse_iterator, 201402L, "make_reverse_iterator");
    expectTypeAndValue<long&&>(__cpp_lib_make_unique, 201304L, "make_unique");
    expectTypeAndValue<long&&>(__cpp_lib_map_try_emplace, 201411L, "map_try_emplace");
    expectTypeAndValue<long&&>(__cpp_lib_math_constants, 201907L, "math_constants");
    expectTypeAndValue<long&&>(__cpp_lib_math_special_functions, 201603L, "math_special_functions");
    expectTypeAndValue<long&&>(__cpp_lib_memory_resource, 201603L, "memory_resource");
    expectTypeAndValue<long&&>(__cpp_lib_node_extract, 201606L, "node_extract");
    expectTypeAndValue<long&&>(
      __cpp_lib_nonmember_container_access, 201411L, "nonmember_container_access");
    expectTypeAndValue<long&&>(__cpp_lib_not_fn, 201603L, "not_fn");
    expectTypeAndValue<long&&>(__cpp_lib_null_iterators, 201304L, "null_iterators");
    expectTypeAndValue<long&&>(__cpp_lib_optional, 201606L, "optional");
    expectTypeAndValue<long&&>(__cpp_lib_parallel_algorithm, 201603L, "parallel_algorithm");
    expectTypeAndValue<long&&>(__cpp_lib_polymorphic_allocator, 201902L, "polymorphic_allocator");
    expectTypeAndValue<long&&>(__cpp_lib_quoted_string_io, 201304L, "quoted_string_io");
    expectTypeAndValue<long&&>(__cpp_lib_ranges, 201911L, "ranges");
    expectTypeAndValue<long&&>(__cpp_lib_raw_memory_algorithms, 201606L, "raw_memory_algorithms");
    expectTypeAndValue<long&&>(__cpp_lib_remove_cvref, 201711L, "remove_cvref");
    expectTypeAndValue<long&&>(__cpp_lib_result_of_sfinae, 201210L, "result_of_sfinae");
    expectTypeAndValue<long&&>(
      __cpp_lib_robust_nonmodifying_seq_ops, 201304L, "robust_nonmodifying_seq_ops");
    expectTypeAndValue<long&&>(__cpp_lib_sample, 201603L, "sample");
    expectTypeAndValue<long&&>(__cpp_lib_scoped_lock, 201703L, "scoped_lock");
    expectTypeAndValue<long&&>(__cpp_lib_semaphore, 201907L, "semaphore");
    expectTypeAndValue<long&&>(__cpp_lib_shared_mutex, 201505L, "shared_mutex");
    expectTypeAndValue<long&&>(__cpp_lib_shared_ptr_arrays, 201707L, "shared_ptr_arrays");
    expectTypeAndValue<long&&>(__cpp_lib_shared_ptr_weak_type, 201606L, "shared_ptr_weak_type");
    expectTypeAndValue<long&&>(__cpp_lib_shared_timed_mutex, 201402L, "shared_timed_mutex");
    expectTypeAndValue<long&&>(__cpp_lib_shift, 201806L, "shift");
    expectTypeAndValue<long&&>(
      __cpp_lib_smart_ptr_for_overwrite, 202002L, "smart_ptr_for_overwrite");
    expectTypeAndValue<long&&>(__cpp_lib_source_location, 201907L, "source_location");
    expectTypeAndValue<long&&>(__cpp_lib_span, 202002L, "span");
    expectTypeAndValue<long&&>(__cpp_lib_ssize, 201902L, "ssize");
    expectTypeAndValue<long&&>(__cpp_lib_starts_ends_with, 201711L, "starts_ends_with");
    expectTypeAndValue<long&&>(__cpp_lib_string_udls, 201304L, "string_udls");
    expectTypeAndValue<long&&>(__cpp_lib_string_view, 201803L, "string_view");
    expectTypeAndValue<long&&>(__cpp_lib_syncbuf, 201803L, "syncbuf");
    expectTypeAndValue<long&&>(__cpp_lib_three_way_comparison, 201907L, "three_way_comparison");
    expectTypeAndValue<long&&>(__cpp_lib_to_address, 201711L, "to_address");
    expectTypeAndValue<long&&>(__cpp_lib_to_array, 201907L, "to_array");
    expectTypeAndValue<long&&>(__cpp_lib_to_chars, 201611L, "to_chars");
    expectTypeAndValue<long&&>(
      __cpp_lib_transformation_trait_aliases, 201304L, "transformation_trait_aliases");
    expectTypeAndValue<long&&>(__cpp_lib_transparent_operators, 201510L, "transparent_operators");
    expectTypeAndValue<long&&>(__cpp_lib_tuple_element_t, 201402L, "tuple_element_t");
    expectTypeAndValue<long&&>(__cpp_lib_tuples_by_type, 201304L, "tuples_by_type");
    expectTypeAndValue<long&&>(__cpp_lib_type_identity, 201806L, "type_identity");
    expectTypeAndValue<long&&>(
      __cpp_lib_type_trait_variable_templates, 201510L, "type_trait_variable_templates");
    expectTypeAndValue<long&&>(__cpp_lib_uncaught_exceptions, 201411L, "uncaught_exceptions");
    expectTypeAndValue<long&&>(
      __cpp_lib_unordered_map_try_emplace, 201411L, "unordered_map_try_emplace");
    expectTypeAndValue<long&&>(__cpp_lib_unwrap_ref, 201811L, "unwrap_ref");
    expectTypeAndValue<long&&>(__cpp_lib_variant, 201606L, "variant");
    expectTypeAndValue<long&&>(__cpp_lib_void_t, 201411L, "void_t");
}
