#include <exception>

#include "testing.h"

struct CheckUncaughtExceptionsInDtor {
    int expected;

    ~CheckUncaughtExceptionsInDtor() {
        int u = std::uncaught_exceptions();
        expect(u == expected);
        if (expected < 10) {
            try {
                expect(u == expected);
                CheckUncaughtExceptionsInDtor c{expected + 1};
                throw 5;
            } catch (int) {
                expect(u == expected);
            }
            expect(u == expected);
        }
    }
};

TEST() {
    expect(std::uncaught_exceptions() == 0);
    try {
        expect(std::uncaught_exceptions() == 0);
        [[maybe_unused]] CheckUncaughtExceptionsInDtor c{1};
        throw 5;
    } catch (int) {
        expect(std::uncaught_exceptions() == 0);
    }
    expect(std::uncaught_exceptions() == 0);
}
