#include "interceptor.h"

#include <dlfcn.h>

namespace Testing {

void* find_next_symbol(const char* name) {
    return dlsym(RTLD_NEXT, name);
}

}  // namespace Testing
