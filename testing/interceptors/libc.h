#ifndef TESTING_INTERCEPTORS_LIBC_H
#define TESTING_INTERCEPTORS_LIBC_H

#include "interceptor.h"

#include <stdlib.h>

namespace Testing {

struct LibCInterceptors {
    CFunctionInterceptor<void*(::size_t)> malloc;
    CFunctionInterceptor<void(void*)> free;
    CFunctionInterceptor<void*(::size_t, ::size_t)> aligned_alloc;
};

extern LibCInterceptors libc;

}  // namespace Testing

#endif
