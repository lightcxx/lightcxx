#include <exception>

#include "testing/test.h"

TEST() {
    std::terminate_handler handler = nullptr;
    expectTypeAndValue<void (*&)()>(handler, nullptr);
    STATIC_EXPECT(std::is_same_v<std::terminate_handler, void (*)()>);
}
