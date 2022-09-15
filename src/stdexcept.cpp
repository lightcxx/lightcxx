#include "stdexcept"

#include "cstdlib"
#include "export.h"

namespace std {

_EXPORT logic_error::~logic_error() {
    free(__what);
}

_EXPORT domain_error::~domain_error() {}

_EXPORT invalid_argument::~invalid_argument() {}

_EXPORT length_error::~length_error() {}

_EXPORT out_of_range::~out_of_range() {}

_EXPORT runtime_error::~runtime_error() {
    free(__what);
}

_EXPORT range_error::~range_error() {}

_EXPORT overflow_error::~overflow_error() {}

_EXPORT underflow_error::~underflow_error() {}

}  // namespace std
