#include <new>

#include "testing.h"

TEST() {
    std::new_handler handler = nullptr;
    expect_type_and_value(handler, void (*&)(), nullptr);
    expect_ct_and_rt(std::is_same_v<std::new_handler, void (*)()>);
}
