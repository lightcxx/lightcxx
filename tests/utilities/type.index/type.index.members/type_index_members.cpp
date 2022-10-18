#include <typeindex>

#include "testing.h"

TEST(ctor_and_assign) {
    const std::type_index h1(typeid(int));
    std::type_index h2(typeid(void));
    const std::type_index h3(typeid(void));
    const std::type_index h4(h3);  // Copy constructor
    ASSERT(h2 == h4);
    std::type_index h5(std::move(h2));
    ASSERT(h3 == h5);
    ASSERT_NOEXCEPT(std::type_index(h1));             // copy ctor
    ASSERT_NOEXCEPT(std::type_index(std::move(h2)));  // move ctor
    ASSERT_NOEXCEPT(h5 = h1);                         // copy assign
    ASSERT_TYPE(std::type_index&, h5 = h1);              // copy assign
    ASSERT_NOEXCEPT(h5 = std::move(h2));              // move assign
    ASSERT_TYPE(std::type_index&, h5 = std::move(h2));   // move assign
    h2 = h1;
    ASSERT(h2 == h1);
    ASSERT(h2 != h3);
    ASSERT(h1 == std::type_index(typeid(int)));
    h5 = std::move(h2);
    ASSERT(h5 != h3);
    ASSERT(h5 == h1);
    ASSERT(h3 == h4);

    static_assert(std::is_trivially_copyable_v<std::type_index>);

    static_assert(std::is_nothrow_constructible_v<std::type_index, const std::type_info&>);

    static_assert(std::is_trivially_copy_constructible_v<std::type_index>);
    static_assert(std::is_trivially_move_constructible_v<std::type_index>);
    static_assert(std::is_trivially_copy_assignable_v<std::type_index>);
    static_assert(std::is_trivially_move_assignable_v<std::type_index>);
    static_assert(std::is_trivially_destructible_v<std::type_index>);
}

TEST(operator_eq) {
    const auto h1 = std::type_index(typeid(int));
    const auto h2 = std::type_index(typeid(void));
    const auto h3 = std::type_index(typeid(void));
    ASSERT_TYPE(bool, h1 == h2);
    ASSERT_NOEXCEPT(h1 == h2);
    ASSERT((!(h1 == h2)));
    ASSERT((!(h2 == h1)));
    ASSERT(h2 == h2);
    ASSERT(h2 == h3);
    ASSERT(h3 == h2);
}

TEST(operator_lt) {
    const auto h1 = std::type_index(typeid(int));
    const auto h2 = std::type_index(typeid(void));
    const auto h3 = std::type_index(typeid(void));
    ASSERT_TYPE(bool, h1 < h2);
    ASSERT_NOEXCEPT(h1 < h2);
    ASSERT(((h1 < h2) ^ (h2 < h1)));  // One or the other.
    ASSERT(!(h2 < h2));
    ASSERT(!(h2 < h3));
    ASSERT(!(h3 < h2));
}

TEST(operator_gt) {
    const auto h1 = std::type_index(typeid(int));
    const auto h2 = std::type_index(typeid(void));
    const auto h3 = std::type_index(typeid(void));
    ASSERT_TYPE(bool, h1 > h2);
    ASSERT_NOEXCEPT(h1 > h2);
    ASSERT(((h1 > h2) ^ (h2 > h1)));  // One or the other.
    ASSERT(!(h2 > h2));
    ASSERT(!(h2 > h3));
    ASSERT(!(h3 > h2));
}

TEST(operator_lt_eq) {
    const auto h1 = std::type_index(typeid(int));
    const auto h2 = std::type_index(typeid(void));
    const auto h3 = std::type_index(typeid(void));
    ASSERT_TYPE(bool, h1 <= h2);
    ASSERT_NOEXCEPT(h1 <= h2);
    ASSERT(((h1 <= h2) ^ (h2 <= h1)));  // One or the other.
    ASSERT(h2 <= h2);
    ASSERT(h2 <= h3);
    ASSERT(h3 <= h2);
}

TEST(operator_gt_eq) {
    const auto h1 = std::type_index(typeid(int));
    const auto h2 = std::type_index(typeid(void));
    const auto h3 = std::type_index(typeid(void));
    ASSERT_TYPE(bool, h1 >= h2);
    ASSERT_NOEXCEPT(h1 >= h2);
    ASSERT(((h1 >= h2) ^ (h2 >= h1)));  // One or the other.
    ASSERT(h2 >= h2);
    ASSERT(h2 >= h3);
    ASSERT(h3 >= h2);
}

TEST(operator_spaceship) {
    const auto h1 = std::type_index(typeid(int));
    const auto h2 = std::type_index(typeid(void));
    const auto h3 = std::type_index(typeid(void));
    ASSERT_TYPE(std::strong_ordering, h1 <=> h2);
    ASSERT_NOEXCEPT(h1 <=> h2);
    ASSERT((h1 <=> h2) != std::strong_ordering::equal);
    ASSERT((h2 <=> h3) == std::strong_ordering::equal);
    ASSERT((h3 <=> h2) == std::strong_ordering::equal);
    ASSERT((h1 <=> h2) != (h2 <=> h1));
    ASSERT((h1 <=> h2) == (h1 <=> h3));
    ASSERT((h2 <=> h1) == (h3 <=> h1));
}

TEST(hash_code) {
    ASSERT_TYPE(std::size_t, std::type_index(typeid(void)).hash_code());
    ASSERT_NOEXCEPT(std::type_index(typeid(void)).hash_code());
    ASSERT_NOEXCEPT(static_cast<const std::type_index&>(std::type_index(typeid(void))).hash_code());
    ASSERT(std::type_index(typeid(void)).hash_code() == typeid(void).hash_code());
    ASSERT(std::type_index(typeid(int)).hash_code() == typeid(int).hash_code());
    ASSERT(std::type_index(typeid(const char* const)).hash_code() == typeid(const char* const).hash_code());
    ASSERT(std::type_index(typeid(std::type_index)).hash_code() == typeid(std::type_index).hash_code());

    ASSERT(std::type_index(typeid(int)).hash_code() == std::type_index(typeid(int)).hash_code());
    ASSERT(std::type_index(typeid(int)).hash_code() != std::type_index(typeid(void)).hash_code());
}

TEST(name) {
    ASSERT_TYPE(const char*, std::type_index(typeid(void)).name());
    ASSERT_NOEXCEPT(std::type_index(typeid(void)).name());
    ASSERT_NOEXCEPT(static_cast<const std::type_index&>(std::type_index(typeid(void))).name());
    ASSERT(std::type_index(typeid(void)).name() == typeid(void).name());
    ASSERT(std::type_index(typeid(int)).name() == typeid(int).name());
    ASSERT(std::type_index(typeid(const char* const)).name() == typeid(const char* const).name());
    ASSERT(std::type_index(typeid(std::type_index)).name() == typeid(std::type_index).name());
}
