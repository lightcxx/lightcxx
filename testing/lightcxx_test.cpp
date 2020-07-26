#include "lightcxx_test.h"

#include <stdio.h>

void LightCXXTest::expect(bool condition, const char* message) noexcept {
    if (!condition) {
        fprintf(
          stderr, "Expectation failed.%s%s\n", (message[0] == '\0' ? "" : " Message: "), message);
        status_code = 1;
    }
}

int LightCXXTest::main() noexcept {
    run();
    return status_code;
}
