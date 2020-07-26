#ifndef _LIGHTCXX_GUARD_TESTING_LIGHTCXX_TEST_H
#define _LIGHTCXX_GUARD_TESTING_LIGHTCXX_TEST_H

class LightCXXTest {
  public:
    void run() noexcept;

    void expect(bool condition, const char* message = "") noexcept;

    template<class T, class U>
    consteval void expectType(U&& val) noexcept {
        static_assert(SameType<T, decltype(val)>::value, "Invalid type.");
    }

    template<class T, class U, class V>
    void expectTypeAndValue(U&& val, V&& expected, const char* message = "") noexcept {
        static_assert(SameType<T, decltype(val)>::value, "Invalid type.");
        expect(val == expected, message);
    }

    int main() noexcept;

  private:
    int status_code = 0;

    template<class T, class U>
    struct SameType {
        static constexpr auto value = false;
    };

    template<class T>
    struct SameType<T, T> {
        static constexpr auto value = true;
    };
};

#define STATIC_EXPECT(...)                                                                         \
    expect(__VA_ARGS__);                                                                           \
    static_assert(__VA_ARGS__)

#endif
