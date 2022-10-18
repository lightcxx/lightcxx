#include <cerrno>

#include "testing.h"

TEST() {
    ASSERT_TYPE(int&, errno);
    errno = 0;
    ASSERT(errno == 0);
    errno = ENODATA;
    ASSERT(errno == ENODATA);
}
