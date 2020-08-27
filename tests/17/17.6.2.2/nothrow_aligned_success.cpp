#include <new>

#include "testing/test.h"

TEST() {
    const auto const_ptr = ::operator new[](256, std::align_val_t{128}, std::nothrow);
    expectType<void* const&>(const_ptr);
    ::operator delete[](const_ptr);

    auto ptr = ::operator new[](256, std::align_val_t{128}, std::nothrow);
    expectType<void*&>(ptr);
    ::operator delete[](ptr);
}
