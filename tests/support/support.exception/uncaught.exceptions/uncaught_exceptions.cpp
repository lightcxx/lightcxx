#include <exception>

#include "testing.h"

struct CheckUncaughtExceptionsInDtor {
    int expected;

    ~CheckUncaughtExceptionsInDtor() {
        int u = std::uncaught_exceptions();
        ASSERT(u == expected);
        if (expected < 10) {
            try {
                ASSERT(u == expected);
                CheckUncaughtExceptionsInDtor c{expected + 1};
                throw 5;
            } catch (int) {
                ASSERT(u == expected);
            }
            ASSERT(u == expected);
        }
    }
};

TEST() {
    ASSERT(std::uncaught_exceptions() == 0);
    try {
        ASSERT(std::uncaught_exceptions() == 0);
        CheckUncaughtExceptionsInDtor c{1};
        throw 5;
    } catch (int) {
        ASSERT(std::uncaught_exceptions() == 0);
    }
    ASSERT(std::uncaught_exceptions() == 0);
}
