#include <new>

#include "testing.h"
#include <cstddef>

TEST() {
    ASSERT_CT_RT(std::hardware_destructive_interference_size >= alignof(std::max_align_t));
    ASSERT_CT_RT(std::hardware_constructive_interference_size >= alignof(std::max_align_t));
}
