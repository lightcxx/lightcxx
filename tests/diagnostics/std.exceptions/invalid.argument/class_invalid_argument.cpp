#include <stdexcept>

#include "testing.h"
#include <type_traits>

TEST() {
    static_assert(std::is_base_of_v<std::logic_error, std::invalid_argument>);

    const char* msg = "message";
    {
        const std::invalid_argument exc(msg);
        ASSERT(std::strcmp(exc.what(), msg) == 0);
    }
    {
        char data[128];
        std::strcpy(data, "this is a message");
        const std::invalid_argument exc(data);
        std::strcpy(data, "this is NOT the message");
        ASSERT(std::strcmp(exc.what(), "this is a message") == 0);
    }
    {
        char* data = static_cast<char*>(std::malloc(128));
        std::strcpy(data, "this is a message");
        const std::invalid_argument exc(data);
        std::strcpy(data, "this is NOT the message");
        std::free(data);
        ASSERT(std::strcmp(exc.what(), "this is a message") == 0);
    }
    {
        try {
            throw std::invalid_argument(msg);
            FAIL();
        } catch (const std::exception& exc) {
            ASSERT(std::strcmp(exc.what(), msg) == 0);
        }
    }
}
