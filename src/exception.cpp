#include <exception>

#include <cstdlib>

#include "handler.h"

namespace std {

namespace {
_Light::Handler<terminate_handler> global_terminate_handler;
}

terminate_handler set_terminate(terminate_handler f) noexcept {
    return global_terminate_handler.set(f);
}

terminate_handler get_terminate() noexcept { return global_terminate_handler.get(); }

[[noreturn]] void terminate() noexcept {
    const auto handler = get_terminate();
    if (handler) { handler(); }
    std::abort();
}

const char* exception::what() const noexcept { return "exception"; }

}  // namespace std
