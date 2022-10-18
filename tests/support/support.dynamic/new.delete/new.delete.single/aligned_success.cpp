#include <new>

#include "testing.h"

TEST() {
    const auto const_ptr = ::operator new (256, std::align_val_t{128});
    ASSERT_TYPE(void* const&, const_ptr);
    ::operator delete(const_ptr);

    auto ptr = ::operator new (256, std::align_val_t{128});
    ASSERT_TYPE(void*&, ptr);
    ::operator delete(ptr);
}
