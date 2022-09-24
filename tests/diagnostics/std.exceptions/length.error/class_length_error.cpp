#include <stdexcept>

#include "testing.h"
#include <type_traits>

TEST() {
    static_assert(std::is_base_of_v<std::logic_error, std::length_error>);

    const char* msg = "message";
    {
        const std::length_error exc(msg);
        expect(std::strcmp(exc.what(), msg) == 0);
    }
    {
        char data[128];
        std::strcpy(data, "this is a message");
        const std::length_error exc(data);
        std::strcpy(data, "this is NOT the message");
        expect(std::strcmp(exc.what(), "this is a message") == 0);
    }
    {
        char* data = static_cast<char*>(std::malloc(128));
        std::strcpy(data, "this is a message");
        const std::length_error exc(data);
        std::strcpy(data, "this is NOT the message");
        std::free(data);
        expect(std::strcmp(exc.what(), "this is a message") == 0);
    }
    {
        try {
            throw std::length_error(msg);
            fail();
        } catch (const std::exception& exc) {
            expect(std::strcmp(exc.what(), msg) == 0);
        }
    }
}
