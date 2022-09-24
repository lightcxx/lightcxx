#include <errno.h>

#include "export.h"

namespace std::_Light {

_EXPORT int* __lib_c_errno() {
    return &errno;
}

}  // namespace std::_Light
