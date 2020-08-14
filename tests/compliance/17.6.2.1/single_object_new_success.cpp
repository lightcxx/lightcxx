#include <new>

#include "testing/test.h"

void Testing::run() {
    const auto const_ptr = ::operator new(256);
    expectType<void* const&>(const_ptr);
    ::operator delete(const_ptr);

    auto ptr = ::operator new(256);
    expectType<void*&>(ptr);
    ::operator delete(ptr);
}
