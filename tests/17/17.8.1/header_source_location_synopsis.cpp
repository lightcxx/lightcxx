#include <source_location>

#include "testing/test.h"

void Testing::run() {
    [[maybe_unused]] std::source_location location = std::source_location::current();
}
