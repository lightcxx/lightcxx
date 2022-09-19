#include <any>

#include "testing.h"

TEST() {
    using std::bad_any_cast;

    expect_is_noexcept(bad_any_cast{});
    expect_is_noexcept(bad_any_cast{}.what());
    expect_is_noexcept(bad_any_cast{}.~bad_any_cast());
    bad_any_cast cast{};
    expect(cast.what() != nullptr);
    static_assert(std::is_base_of_v<std::bad_cast, bad_any_cast>);
}
