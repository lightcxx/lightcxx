#include <new>

#include "testing.h"
#include <cstddef>

TEST() {
    expect_ct_and_rt(std::hardware_destructive_interference_size >= alignof(std::max_align_t));
    expect_ct_and_rt(std::hardware_constructive_interference_size >= alignof(std::max_align_t));
}
