#include <exception>

#include "testing/test.h"

struct CheckUncaughtExceptionsInDtor {
    int expected;

    ~CheckUncaughtExceptionsInDtor() {
        int u = std::uncaught_exceptions();
        Testing::expect(u == expected, "In destructor expected %d, got %d\n", expected, u);
        if (expected < 10) {
            try {
                Testing::expect(
                  u == expected, "In destructor try clause expected %d, got %d\n", expected, u);
                CheckUncaughtExceptionsInDtor c{expected + 1};
                throw 5;
            } catch (int) {
                Testing::expect(
                  u == expected, "In destructor catch clause expected %d, got %d\n", expected, u);
            }
            Testing::expect(
              u == expected, "In destructor after catch expected %d, got %d\n", expected, u);
        }
    }
};

TEST() {
    expect(std::uncaught_exceptions() == 0, "outside any EH clause");
    try {
        expect(std::uncaught_exceptions() == 0, "inside try clause");
        CheckUncaughtExceptionsInDtor c{1};
        throw 5;
    } catch (int) { expect(std::uncaught_exceptions() == 0, "inside first-level catch clause"); }
    expect(std::uncaught_exceptions() == 0, "after all EH clauses");
}
