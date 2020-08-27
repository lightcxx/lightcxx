#include <new>

#include "testing/test.h"
#include <cstddef>

TEST() {
    STATIC_EXPECT(std::hardware_destructive_interference_size >= alignof(std::max_align_t),
                  "hardware_destructive_interference_size");
    STATIC_EXPECT(std::hardware_constructive_interference_size >= alignof(std::max_align_t),
                  "hardware_constructive_interference_size");
}
