#include "testing.h"

#include <source_location>

TEST() {
    [[maybe_unused]] std::source_location location = std::source_location::current();
}
