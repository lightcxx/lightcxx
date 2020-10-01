#include "libc.h"

namespace Testing {

LibCInterceptors libc{
  .malloc = {"malloc"},
  .free = {"free"},
  .aligned_alloc = {"aligned_alloc"},
};

}

extern "C" void* malloc(size_t size) {
    return Testing::libc.malloc.invoke(size);
}

extern "C" void free(void* ptr) {
    return Testing::libc.free.invoke(ptr);
}

extern "C" void* aligned_alloc(size_t align, size_t size) {
    return Testing::libc.aligned_alloc.invoke(align, size);
}
