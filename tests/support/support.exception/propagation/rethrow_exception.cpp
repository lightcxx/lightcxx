#include <exception>

#include "testing.h"

int num_exception_instances = 0;
struct CountedException {
    int data;

    CountedException() {
        ++num_exception_instances;
    }

    explicit CountedException(int data)
            : data(data) {
        ++num_exception_instances;
    }

    CountedException(const CountedException&) {
        ++num_exception_instances;
    }

    ~CountedException() {
        --num_exception_instances;
    }
};

TEST(common_case) {
    std::exception_ptr p;
    try {
        throw CountedException(3);
    } catch (...) {
        p = std::current_exception();
    }

    expect(num_exception_instances == 1);

    try {
        std::rethrow_exception(p);
    } catch (const CountedException& a) {
        expect(num_exception_instances == 1);
        expect(p != nullptr);
        p = nullptr;
        expect(p == nullptr);
        expect(a.data == 3);
        expect(num_exception_instances == 1);
    }
    expect(num_exception_instances == 0);
}

TEST(keep_exception_ptr_instance) {
    std::exception_ptr p;
    try {
        throw CountedException(3);
    } catch (const CountedException&) {
        p = std::current_exception();
    } catch (...) {
        fail();
    }

    expect(num_exception_instances == 1);

    try {
        std::rethrow_exception(p);
    } catch (const CountedException& a) {
        expect(num_exception_instances == 1);
        expect(p != nullptr);
        expect(a.data == 3);
        expect(num_exception_instances == 1);
    } catch (...) {
        fail();
    }

    expect(num_exception_instances == 1);
    p = nullptr;
    expect(num_exception_instances == 0);
}
