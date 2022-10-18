#include <new>

#include "testing.h"

TEST() {
    std::new_handler handler = nullptr;
    ASSERT_TYPE_AND_VALUE(handler, void (*&)(), nullptr);
    ASSERT_CT_RT((std::is_same_v<std::new_handler, void (*)()>));
}
