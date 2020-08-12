#include "testing/test.h"

#include <stdio.h>

namespace {

int exit_code = 0;

}

namespace Testing {

void expect(bool condition, const char* message) noexcept {
    if (!condition) {
        fprintf(
          stderr, "Expectation failed.%s%s\n", (message[0] == '\0' ? "" : " Message: "), message);
        exit_code = 1;
    }
}

}  // namespace Testing

int main() {
    Testing::run();
    return exit_code;
}
