#include <bitset>

#include "testing.h"

TEST() {
    std::bitset<52> x;
    std::bitset<52> y(334);

    x &= y;
    y |= x;
    y ^= x;
    x = (x <<= 3);
    y = (y >>= 3);
    x.set();
    x.set(13);
    x.set(14, false);
    y.reset();
    y.reset(15);
    y = ~x;
    y.flip();
    y.flip(12);
    [[maybe_unused]] auto ref = y[3];
    ref.flip();
    ~ref;
    [[maybe_unused]] auto ref_cpy = ref;
    compiler_forget(ref_cpy);
    [[maybe_unused]] auto ref_cast = static_cast<bool>(ref);
    [[maybe_unused]] auto cref = static_cast<const std::bitset<52>>(y)[3];
    x.to_ulong();
    y.to_ullong();
    x.count();
    static_assert(std::bitset<52>{}.size() == 52);
    [[maybe_unused]] auto eq = x == y;
    x.test(3);
    x.all();
    x.any();
    x.none();
    x << 3;
    x >> 3;
    x& y;
    x | y;
    x ^ y;
}
