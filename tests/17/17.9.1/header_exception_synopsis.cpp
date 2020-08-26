#include <exception>

#include "testing/test.h"

void Testing::run() {
    [[maybe_unused]] std::exception exc;
    [[maybe_unused]] std::bad_exception b_exc;
    [[maybe_unused]] std::nested_exception n_exc;

    std::terminate_handler h = nullptr;
    expectType<void(*&)()>(h);
    expectType<std::terminate_handler&&>(std::get_terminate());
    expectType<std::terminate_handler&&>(std::set_terminate(h));
    [[maybe_unused]] const auto terminate_lambda = []() {
        std::terminate();
    };

    [[maybe_unused]] int n = std::uncaught_exceptions();
    std::exception_ptr exc_ptr;

    expectType<std::exception_ptr&&>(std::current_exception());
    [[maybe_unused]] const auto rethrow_exception_lambda = [&exc_ptr]() {
        std::rethrow_exception(exc_ptr);
    };
    expectType<std::exception_ptr&&>(std::make_exception_ptr(14));

    static_assert(std::is_same_v<std::add_pointer_t<int>, int*>);

    try {
        std::throw_with_nested(5);
    } catch(...) {}

    std::rethrow_if_nested(15);
}
