#include <new>

#include "testing.h"

TEST() {
    const auto const_ptr = ::operator new[](256, std::nothrow);
    expect_type<void* const&>(const_ptr);
    ::operator delete[](const_ptr);

    auto ptr = ::operator new[](256, std::nothrow);
    expect_type<void*&>(ptr);
    ::operator delete[](ptr);
}
