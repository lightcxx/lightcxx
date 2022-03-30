#include "../intseq.intseq/test_integer_sequence.h"

TEST() {
    test_integer_sequence<std::make_integer_sequence<std::size_t, 0>, 0, std::size_t>();
    static_assert(std::is_same_v<std::make_integer_sequence<std::size_t, 0>, std::integer_sequence<std::size_t>>);
    test_integer_sequence<std::make_index_sequence<0>, 0, std::size_t>();
    static_assert(std::is_same_v<std::make_index_sequence<0>, std::integer_sequence<std::size_t>>);
    test_integer_sequence<std::index_sequence_for<>, 0, std::size_t>();
    static_assert(std::is_same_v<std::index_sequence_for<>, std::integer_sequence<std::size_t>>);
    test_integer_sequence<std::make_integer_sequence<int, 0>, 0, int>();
    static_assert(std::is_same_v<std::make_integer_sequence<int, 0>, std::integer_sequence<int>>);
    test_integer_sequence<std::make_integer_sequence<long long, 0>, 0, long long>();
    static_assert(std::is_same_v<std::make_integer_sequence<long long, 0>, std::integer_sequence<long long>>);

    test_integer_sequence<std::make_integer_sequence<std::size_t, 1>, 1, std::size_t>();
    static_assert(std::is_same_v<std::make_integer_sequence<std::size_t, 1>, std::integer_sequence<std::size_t, 0>>);
    test_integer_sequence<std::make_index_sequence<1>, 1, std::size_t>();
    static_assert(std::is_same_v<std::make_index_sequence<1>, std::integer_sequence<std::size_t, 0>>);
    test_integer_sequence<std::index_sequence_for<long>, 1, std::size_t>();
    static_assert(std::is_same_v<std::index_sequence_for<long>, std::integer_sequence<std::size_t, 0>>);
    test_integer_sequence<std::make_integer_sequence<int, 1>, 1, int>();
    static_assert(std::is_same_v<std::make_integer_sequence<int, 1>, std::integer_sequence<int, 0>>);
    test_integer_sequence<std::make_integer_sequence<long long, 1>, 1, long long>();
    static_assert(std::is_same_v<std::make_integer_sequence<long long, 1>, std::integer_sequence<long long, 0>>);

    test_integer_sequence<std::make_integer_sequence<std::size_t, 3>, 3, std::size_t>();
    static_assert(std::is_same_v<std::make_integer_sequence<std::size_t, 3>, std::integer_sequence<std::size_t, 0, 1, 2>>);
    test_integer_sequence<std::make_index_sequence<3>, 3, std::size_t>();
    static_assert(std::is_same_v<std::make_index_sequence<3>, std::integer_sequence<std::size_t, 0, 1, 2>>);
    test_integer_sequence<std::index_sequence_for<long, char, bool>, 3, std::size_t>();
    static_assert(std::is_same_v<std::index_sequence_for<long, char, bool>, std::integer_sequence<std::size_t, 0, 1, 2>>);
    test_integer_sequence<std::make_integer_sequence<int, 3>, 3, int>();
    static_assert(std::is_same_v<std::make_integer_sequence<int, 3>, std::integer_sequence<int, 0, 1, 2>>);
    test_integer_sequence<std::make_integer_sequence<long long, 3>, 3, long long>();
    static_assert(std::is_same_v<std::make_integer_sequence<long long, 3>, std::integer_sequence<long long, 0, 1, 2>>);

    test_integer_sequence<std::make_integer_sequence<std::size_t, 7>, 7, std::size_t>();
    static_assert(std::is_same_v<std::make_integer_sequence<std::size_t, 7>, std::integer_sequence<std::size_t, 0, 1, 2, 3, 4, 5, 6>>);
    test_integer_sequence<std::make_index_sequence<7>, 7, std::size_t>();
    static_assert(std::is_same_v<std::make_index_sequence<7>, std::integer_sequence<std::size_t, 0, 1, 2, 3, 4, 5, 6>>);
    test_integer_sequence<std::index_sequence_for<long, char, bool, int, double, float, wchar_t>, 7, std::size_t>();
    static_assert(
      std::is_same_v<std::index_sequence_for<long, char, bool, int, double, float, wchar_t>, std::integer_sequence<std::size_t, 0, 1, 2, 3, 4, 5, 6>>);
    test_integer_sequence<std::make_integer_sequence<int, 7>, 7, int>();
    static_assert(std::is_same_v<std::make_integer_sequence<int, 7>, std::integer_sequence<int, 0, 1, 2, 3, 4, 5, 6>>);
    test_integer_sequence<std::make_integer_sequence<long long, 7>, 7, long long>();
    static_assert(std::is_same_v<std::make_integer_sequence<long long, 7>, std::integer_sequence<long long, 0, 1, 2, 3, 4, 5, 6>>);
}
