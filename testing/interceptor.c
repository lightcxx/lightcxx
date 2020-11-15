#define _GNU_SOURCE
#include <dlfcn.h>

void* testing_find_next_symbol(const char* name) {
    return dlsym(RTLD_NEXT, name);
}
