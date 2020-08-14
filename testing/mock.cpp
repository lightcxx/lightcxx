#include "mock.h"

#include <dlfcn.h>
#include <stdio.h>

namespace Testing {

void* find_next_symbol(const char* name) {
    return dlsym(RTLD_NEXT, name);
}

}  // namespace Testing

#define DEFINE_MOCK(NAME, R, ARGS, ARGN)                                                           \
    namespace Testing {                                                                            \
    CFunctionMock<R ARGS> mock_##NAME{#NAME};                                                      \
    }                                                                                              \
    extern "C" R NAME ARGS { return Testing::mock_##NAME.invoke ARGN; }

DEFINE_MOCK(malloc, void*, (::size_t sz), (sz))
DEFINE_MOCK(free, void, (void* ptr), (ptr))
DEFINE_MOCK(aligned_alloc, void*, (::size_t align, ::size_t size), (align, size))
