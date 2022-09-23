#include <typeindex>

#include "testing.h"

TEST(ctor_and_assign) {
    const std::type_index h1(typeid(int));
    std::type_index h2(typeid(void));
    const std::type_index h3(typeid(void));
    const std::type_index h4(h3);  // Copy constructor
    expect(h2 == h4);
    std::type_index h5(std::move(h2));
    expect(h3 == h5);
    expect_is_noexcept(std::type_index(h1));             // copy ctor
    expect_is_noexcept(std::type_index(std::move(h2)));  // move ctor
    expect_is_noexcept(h5 = h1);                         // copy assign
    expect_type(std::type_index&, h5 = h1);              // copy assign
    expect_is_noexcept(h5 = std::move(h2));              // move assign
    expect_type(std::type_index&, h5 = std::move(h2));   // move assign
    h2 = h1;
    expect(h2 == h1);
    expect(h2 != h3);
    expect(h1 == std::type_index(typeid(int)));
    h5 = std::move(h2);
    expect(h5 != h3);
    expect(h5 == h1);
    expect(h3 == h4);

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
    expect_type(bool, h1 == h2);
    expect_is_noexcept(h1 == h2);
    expect((!(h1 == h2)));
    expect((!(h2 == h1)));
    expect(h2 == h2);
    expect(h2 == h3);
    expect(h3 == h2);
}

TEST(operator_lt) {
    const auto h1 = std::type_index(typeid(int));
    const auto h2 = std::type_index(typeid(void));
    const auto h3 = std::type_index(typeid(void));
    expect_type(bool, h1 < h2);
    expect_is_noexcept(h1 < h2);
    expect(((h1 < h2) ^ (h2 < h1)));  // One or the other.
    expect(!(h2 < h2));
    expect(!(h2 < h3));
    expect(!(h3 < h2));
}

TEST(operator_gt) {
    const auto h1 = std::type_index(typeid(int));
    const auto h2 = std::type_index(typeid(void));
    const auto h3 = std::type_index(typeid(void));
    expect_type(bool, h1 > h2);
    expect_is_noexcept(h1 > h2);
    expect(((h1 > h2) ^ (h2 > h1)));  // One or the other.
    expect(!(h2 > h2));
    expect(!(h2 > h3));
    expect(!(h3 > h2));
}

TEST(operator_lt_eq) {
    const auto h1 = std::type_index(typeid(int));
    const auto h2 = std::type_index(typeid(void));
    const auto h3 = std::type_index(typeid(void));
    expect_type(bool, h1 <= h2);
    expect_is_noexcept(h1 <= h2);
    expect(((h1 <= h2) ^ (h2 <= h1)));  // One or the other.
    expect(h2 <= h2);
    expect(h2 <= h3);
    expect(h3 <= h2);
}

TEST(operator_gt_eq) {
    const auto h1 = std::type_index(typeid(int));
    const auto h2 = std::type_index(typeid(void));
    const auto h3 = std::type_index(typeid(void));
    expect_type(bool, h1 >= h2);
    expect_is_noexcept(h1 >= h2);
    expect(((h1 >= h2) ^ (h2 >= h1)));  // One or the other.
    expect(h2 >= h2);
    expect(h2 >= h3);
    expect(h3 >= h2);
}

TEST(operator_spaceship) {
    const auto h1 = std::type_index(typeid(int));
    const auto h2 = std::type_index(typeid(void));
    const auto h3 = std::type_index(typeid(void));
    expect_type(std::strong_ordering, h1 <=> h2);
    expect_is_noexcept(h1 <=> h2);
    expect((h1 <=> h2) != std::strong_ordering::equal);
    expect((h2 <=> h3) == std::strong_ordering::equal);
    expect((h3 <=> h2) == std::strong_ordering::equal);
    expect((h1 <=> h2) != (h2 <=> h1));
    expect((h1 <=> h2) == (h1 <=> h3));
    expect((h2 <=> h1) == (h3 <=> h1));
}

TEST(hash_code) {
    expect_type(std::size_t, std::type_index(typeid(void)).hash_code());
    expect_is_noexcept(std::type_index(typeid(void)).hash_code());
    expect_is_noexcept(static_cast<const std::type_index&>(std::type_index(typeid(void))).hash_code());
    expect(std::type_index(typeid(void)).hash_code() == typeid(void).hash_code());
    expect(std::type_index(typeid(int)).hash_code() == typeid(int).hash_code());
    expect(std::type_index(typeid(const char* const)).hash_code() == typeid(const char* const).hash_code());
    expect(std::type_index(typeid(std::type_index)).hash_code() == typeid(std::type_index).hash_code());

    expect(std::type_index(typeid(int)).hash_code() == std::type_index(typeid(int)).hash_code());
    expect(std::type_index(typeid(int)).hash_code() != std::type_index(typeid(void)).hash_code());
}

TEST(name) {
    expect_type(const char*, std::type_index(typeid(void)).name());
    expect_is_noexcept(std::type_index(typeid(void)).name());
    expect_is_noexcept(static_cast<const std::type_index&>(std::type_index(typeid(void))).name());
    expect(std::type_index(typeid(void)).name() == typeid(void).name());
    expect(std::type_index(typeid(int)).name() == typeid(int).name());
    expect(std::type_index(typeid(const char* const)).name() == typeid(const char* const).name());
    expect(std::type_index(typeid(std::type_index)).name() == typeid(std::type_index).name());
}
