// EXPECT:NO_COMPILE "std::is_abstract is not supported on this compiler."

#define _LIGHTCXX_DONT_USE_BUILTINS

#include <type_traits>

class Abstract {
    virtual void f() = 0;
};

static_assert(std::is_abstract<Abstract>::value);
