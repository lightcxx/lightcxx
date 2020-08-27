//REQUEST:NO_TEST_LIB "The testing library depends on <source_location>."

#include <source_location>

int main() {
    [[maybe_unused]] std::source_location location = std::source_location::current();
    return 0;
}
