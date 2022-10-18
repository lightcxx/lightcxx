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

    ASSERT(num_exception_instances == 1);

    try {
        std::rethrow_exception(p);
    } catch (const CountedException& a) {
        ASSERT(num_exception_instances == 1);
        ASSERT(p != nullptr);
        p = nullptr;
        ASSERT(p == nullptr);
        ASSERT(a.data == 3);
        ASSERT(num_exception_instances == 1);
    }
    ASSERT(num_exception_instances == 0);
}

TEST(keep_exception_ptr_instance) {
    std::exception_ptr p;
    try {
        throw CountedException(3);
    } catch (const CountedException&) {
        p = std::current_exception();
    } catch (...) {
        FAIL();
    }

    ASSERT(num_exception_instances == 1);

    try {
        std::rethrow_exception(p);
    } catch (const CountedException& a) {
        ASSERT(num_exception_instances == 1);
        ASSERT(p != nullptr);
        ASSERT(a.data == 3);
        ASSERT(num_exception_instances == 1);
    } catch (...) {
        FAIL();
    }

    ASSERT(num_exception_instances == 1);
    p = nullptr;
    ASSERT(num_exception_instances == 0);
}
