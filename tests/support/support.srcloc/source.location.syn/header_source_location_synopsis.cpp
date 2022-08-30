#include "testing.h"

#include <source_location>

TEST() {
    std::source_location location = std::source_location::current();
}
