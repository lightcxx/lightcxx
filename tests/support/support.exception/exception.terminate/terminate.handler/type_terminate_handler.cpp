#include <exception>

#include "testing.h"

TEST() {
    std::terminate_handler handler = nullptr;
    ASSERT_TYPE_AND_VALUE(handler, void (*&)(), nullptr);
    ASSERT_CT_RT((std::is_same_v<std::terminate_handler, void (*)()>));
}
