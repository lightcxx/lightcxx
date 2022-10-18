#include <any>

#include "testing.h"

TEST() {
    using std::bad_any_cast;

    ASSERT_NOEXCEPT(bad_any_cast{});
    ASSERT_NOEXCEPT(bad_any_cast{}.what());
    ASSERT_NOEXCEPT(bad_any_cast{}.~bad_any_cast());
    bad_any_cast cast{};
    ASSERT(cast.what() != nullptr);
    static_assert(std::is_base_of_v<std::bad_cast, bad_any_cast>);
}
