#include <cstdlib>
#include <stdio.h>

#include "export.h"

namespace std::_Light {

_EXPORT void __assert_failed(const char* __func, const char* __file, int __line, const char* __expr) {
    fprintf(stderr, "assertion failed at %s (%s:%d): %s\n", __func, __file, __line, __expr);
    std::abort();
}

}  // namespace std::_Light
