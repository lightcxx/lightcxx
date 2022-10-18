#include "intercept_libc.h"

Testing::LibCInterceptors Testing::libc;

extern "C" void* malloc(size_t size) {
    return Testing::libc.malloc.invoke(size);
}

extern "C" void free(void* ptr) {
    return Testing::libc.free.invoke(ptr);
}

extern "C" void* aligned_alloc(size_t align, size_t size) {
    return Testing::libc.aligned_alloc.invoke(align, size);
}

extern "C" void abort() {
    Testing::libc.abort.invoke();
    printf("EXPECTATION FAILED: abort() did not abort.\n");
    ::_Exit(1);
}
