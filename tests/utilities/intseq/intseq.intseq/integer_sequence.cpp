#include "test_integer_sequence.h"

TEST() {
    test_integer_sequence<std::integer_sequence<std::size_t>, 0, std::size_t>();
    test_integer_sequence<std::index_sequence<>, 0, std::size_t>();

    test_integer_sequence<std::integer_sequence<std::size_t, 7>, 1, std::size_t>();
    test_integer_sequence<std::index_sequence<7>, 1, std::size_t>();

    test_integer_sequence<std::integer_sequence<std::size_t, 7, 1>, 2, std::size_t>();
    test_integer_sequence<std::index_sequence<7, 1>, 2, std::size_t>();

    test_integer_sequence<std::integer_sequence<std::size_t, 7, 1, 5>, 3, std::size_t>();
    test_integer_sequence<std::index_sequence<7, 1, 5>, 3, std::size_t>();

    test_integer_sequence<std::integer_sequence<int>, 0, int>();
    test_integer_sequence<std::integer_sequence<int, 7>, 1, int>();
    test_integer_sequence<std::integer_sequence<int, 7, 1>, 2, int>();
    test_integer_sequence<std::integer_sequence<int, 7, 1, 5>, 3, int>();

    test_integer_sequence<std::integer_sequence<bool>, 0, bool>();
    test_integer_sequence<std::integer_sequence<bool, false>, 1, bool>();
    test_integer_sequence<std::integer_sequence<bool, false, true>, 2, bool>();
    test_integer_sequence<std::integer_sequence<bool, false, true, false>, 3, bool>();
}
