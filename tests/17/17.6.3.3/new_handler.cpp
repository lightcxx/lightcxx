#include <new>

#include "testing/test.h"

void Testing::run() {
    std::new_handler handler = nullptr;
    expectTypeAndValue<void (*&)()>(handler, nullptr);
    STATIC_EXPECT(IsSameType<std::new_handler, void (*)()>::value);
}
