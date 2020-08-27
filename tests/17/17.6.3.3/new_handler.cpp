#include <new>

#include "testing/test.h"

TEST() {
    std::new_handler handler = nullptr;
    expectTypeAndValue<void (*&)()>(handler, nullptr);
    STATIC_EXPECT(std::is_same_v<std::new_handler, void (*)()>);
}
