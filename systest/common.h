// Ugly hack to allow usage of typeid(). This has the same
// ABI as the lightcxx version. If (unlikely) that struct ever changes,
// this must be updated as well.
// I don't want to #include anything extra in these tests.
namespace std {
class type_info {
  public:
    virtual ~type_info();

    const char* name() const noexcept {
        return __name;
    }

  private:
    const char* __name;
};
}  // namespace std

extern "C" __attribute__((format(printf, 2, 3))) int sprintf(char*, const char*, ...);

template<class T>
const char* describe_type_alias(char* buf, const char* name) {
    sprintf(buf,
            "type=%s size=%zu alignment=%zu rtti='%s' (%p)",
            name, sizeof(T), alignof(T),
            typeid(T).name(), static_cast<const void*>(typeid(T).name()));
    return buf;
}

template<class T>
const char* describe_constant(char* buf, const char* name, T value) {
    constexpr const char* hex_digits = "0123456789ABCDEF";

    auto offset = sprintf(buf,
                          "const=%s size=%zu alignment=%zu rtti='%s' (%p) value=0x",
                          name, sizeof(decltype(value)), alignof(decltype(value)),
                          typeid(value).name(), static_cast<const void*>(typeid(value).name()));
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&value);
    for (int i = 0; i < static_cast<int>(sizeof(value)); i++) {
        buf[offset++] = hex_digits[bytes[i] >> 4];
        buf[offset++] = hex_digits[bytes[i] & 15];
    }
    buf[offset] = '\0';
    return buf;
}
