#include "interceptor.h"

#include <dlfcn.h>
#include <stdio.h>

namespace Testing {

void* find_next_symbol(const char* name) {
    return dlsym(RTLD_NEXT, name);
}

LibCInterceptors libc{
  .malloc = {"malloc"},
  .free = {"free"},
  .aligned_alloc = {"aligned_alloc"},
};

}  // namespace Testing

extern "C" {

void* malloc(size_t size) {
    return Testing::libc.malloc.invoke(size);
}
void free(void* ptr) {
    return Testing::libc.free.invoke(ptr);
}
void* aligned_alloc(size_t align, size_t size) {
    return Testing::libc.aligned_alloc.invoke(align, size);
}
}
