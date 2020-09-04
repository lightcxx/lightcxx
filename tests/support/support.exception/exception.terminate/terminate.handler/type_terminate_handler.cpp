#include <exception>

#include "testing.h"

TEST() {
    std::terminate_handler handler = nullptr;
    expect_type_and_value<void (*&)()>(handler, nullptr);
    expect_ct_and_rt(std::is_same_v<std::terminate_handler, void (*)()>);
}
