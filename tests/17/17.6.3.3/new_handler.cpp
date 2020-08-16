#include <new>

#include "testing/test.h"

void Testing::run() {
    STATIC_EXPECT(IsSameType<std::new_handler, void (*)()>::value);
}
