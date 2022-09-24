#include <stdexcept>

#include "testing.h"

TEST() {
    std::logic_error e1("error");
    std::domain_error e2("error");
    std::invalid_argument e3("error");
    std::length_error e4("error");
    std::out_of_range e5("error");
    std::runtime_error e6("error");
    std::range_error e7("error");
    std::overflow_error e8("error");
    std::underflow_error e9("error");
}
