#include <cerrno>

#include "testing.h"

TEST() {
    expect_type(int&, errno);
    errno = 0;
    expect(errno == 0);
    errno = ENODATA;
    expect(errno == ENODATA);
}
