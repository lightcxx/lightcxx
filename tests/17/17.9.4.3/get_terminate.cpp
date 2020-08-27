#include <exception>

#include "testing/test.h"

TEST() {
    std::terminate_handler g = []() { ::abort(); };
    std::terminate_handler h = []() { _Exit(1); };
    expect(std::get_terminate() == nullptr, "first std::get_terminate");
    std::set_terminate(g);
    expect(std::get_terminate() == g, "second std::get_terminate");
    std::set_terminate(h);
    expect(std::get_terminate() == h, "third std::get_terminate");
    std::set_terminate(nullptr);
    expect(std::get_terminate() == nullptr, "fourth std::get_terminate");
    std::set_terminate(g);
    expect(std::get_terminate() == g, "fifth std::get_terminate");
}
