#include <exception>

#include "testing/test.h"

int num_exception_instances = 0;
struct CountedException {
    CountedException() {
        ++num_exception_instances;
    }

    CountedException(const CountedException&) {
        ++num_exception_instances;
    }

    ~CountedException() {
        --num_exception_instances;
    }
};

TEST(throwing_CountedException_helper) {
    try {
        expect(num_exception_instances == 0);
        throw CountedException();
    } catch (...) { expect(num_exception_instances == 1); }
    expect(num_exception_instances == 0);
}

TEST(rethrowing_CountedException_helper) {
    try {
        expect(num_exception_instances == 0);
        throw CountedException();
    } catch (...) {
        expect(num_exception_instances == 1);
        try {
            expect(num_exception_instances == 1);
            throw;
        } catch (...) { expect(num_exception_instances == 1); }
        expect(num_exception_instances == 1);
    }
    expect(num_exception_instances == 0);
}

TEST(before_eh_clauses) {
    expectTypeAndValue<std::exception_ptr&&>(std::current_exception(), nullptr);

    std::exception_ptr exc;
    expect(exc == nullptr);
    exc = std::current_exception();
    expect(exc == nullptr);
}

TEST(inside_try_clause) {
    try {
        expectTypeAndValue<std::exception_ptr&&>(std::current_exception(), nullptr);
        std::exception_ptr exc;
        expect(exc == nullptr);
        exc = std::current_exception();
        expect(exc == nullptr);

        throw 5;
    } catch (...) {}
}

TEST(inside_catch_by_ellipsis_clause) {
    std::exception_ptr p_copy;
    try {
        throw CountedException();
    } catch (...) {
        std::exception_ptr p = std::current_exception();
        expect(num_exception_instances == 1);
        expect(p != nullptr);
        p_copy = std::current_exception();
        expect(p == p_copy);
    }
    expect(num_exception_instances == 1);
    p_copy = nullptr;
    expect(num_exception_instances == 0);
}

TEST(inside_catch_by_reference_clause) {
    std::exception_ptr p_copy;
    try {
        throw CountedException();
    } catch (CountedException&) {
        std::exception_ptr p = std::current_exception();
        expect(num_exception_instances == 1);
        expect(p != nullptr);
        p_copy = std::current_exception();
        expect(p == p_copy);
    }
    expect(num_exception_instances == 1);
    p_copy = nullptr;
    expect(num_exception_instances == 0);
}

TEST(inside_catch_by_value_clause) {
    std::exception_ptr p_copy;
    try {
        throw CountedException();
    } catch (CountedException) {
        expect(num_exception_instances == 2);
        std::exception_ptr p = std::current_exception();
        expect(num_exception_instances == 2);
        expect(p != nullptr);
        p_copy = std::current_exception();
        expect(p == p_copy);
    }
    expect(num_exception_instances == 1);
    p_copy = nullptr;
    expect(num_exception_instances == 0);
}

TEST(inside_try_clause_nested_in_rethrow_catch_clause) {
    try {
        throw CountedException();
    } catch (...) {
        try {
            std::exception_ptr p = std::current_exception();
            expect(num_exception_instances == 1);
            expect(p != nullptr);
            throw;
        } catch (...) { expect(num_exception_instances == 1); }
        expect(num_exception_instances == 1);
    }
    expect(num_exception_instances == 0);
}

TEST(inside_catch_clause_nested_in_rethrow_catch_clause) {
    try {
        throw CountedException();
    } catch (...) {
        try {
            throw;
        } catch (...) {
            std::exception_ptr p = std::current_exception();
            expect(num_exception_instances == 1);
            expect(p != nullptr);
        }
        expect(num_exception_instances == 1);
    }
    expect(num_exception_instances == 0);
}

TEST(inside_catch_clause_nested_in_rethrow_catch_clause_stored_in_top_level_exception_ptr) {
    std::exception_ptr p;
    try {
        throw CountedException();
    } catch (...) {
        try {
            throw;
        } catch (...) {
            p = std::current_exception();
            expect(num_exception_instances == 1);
            expect(p != nullptr);
        }
        expect(num_exception_instances == 1);
    }
    expect(num_exception_instances == 1);
    p = nullptr;
    expect(num_exception_instances == 0);
}

TEST(inside_catch_clause_after_nested_rethrow) {
    try {
        throw CountedException();
    } catch (...) {
        try {
            throw;
        } catch (...) { expect(num_exception_instances == 1); }
        std::exception_ptr p = std::current_exception();
        expect(num_exception_instances == 1);
        expect(p != nullptr);
    }
    expect(num_exception_instances == 0);
}

TEST(after_eh_clauses) {
    try {
        throw CountedException();
    } catch (...) {
        try {
            throw;
        } catch (...) {}
    }
    expect(num_exception_instances == 0);
    std::exception_ptr p = std::current_exception();
    expect(num_exception_instances == 0);
    expect(p == nullptr);
}
