// EXPECT:NO_COMPILE "std::has_virtual_destructor is not supported on this compiler."

#define _LIGHTCXX_BUILTINS_DONT_USE_ANY

#include <type_traits>

class WithVirtualDtor {
    virtual ~WithVirtualDtor() {}
};

static_assert(std::has_virtual_destructor<WithVirtualDtor>::value);
