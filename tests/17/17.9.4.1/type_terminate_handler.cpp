#include <exception>

#include "testing/test.h"

void Testing::run() {
    std::terminate_handler handler = nullptr;
    expectTypeAndValue<void (*&)()>(handler, nullptr);
    STATIC_EXPECT(IsSameType<std::terminate_handler, void (*)()>::value);
}
