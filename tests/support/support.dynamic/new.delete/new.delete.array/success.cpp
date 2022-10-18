#include <new>

#include "testing.h"

TEST() {
    const auto const_ptr = ::operator new[](256);
    ASSERT_TYPE(void* const&, const_ptr);
    ::operator delete[](const_ptr);

    auto ptr = ::operator new[](256);
    ASSERT_TYPE(void*&, ptr);
    ::operator delete[](ptr);
}
