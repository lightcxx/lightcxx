// EXPECT:NO_COMPILE "std::has_virtual_destructor is not supported on this compiler."

#define _LIGHTCXX_DONT_USE_BUILTINS

#include <type_traits>

class WithVirtualDtor {
    virtual ~WithVirtualDtor() {}
};

static_assert(std::has_virtual_destructor<WithVirtualDtor>::value);
