#ifndef TESTING_COUNTED_TYPE_H
#define TESTING_COUNTED_TYPE_H

namespace Testing {

struct cnttype {
    static inline int default_ctor_count = 0;
    static inline int value_ctor_count = 0;
    static inline int copy_ctor_count = 0;
    static inline int move_ctor_count = 0;
    static inline int copy_assign_count = 0;
    static inline int move_assign_count = 0;
    static inline int dtor_count = 0;

    static void reset() {
        default_ctor_count = 0;
        value_ctor_count = 0;
        copy_ctor_count = 0;
        move_ctor_count = 0;
        copy_assign_count = 0;
        move_assign_count = 0;
        dtor_count = 0;
    }

    int val = 0;

    cnttype() noexcept {
        default_ctor_count++;
    }
    explicit cnttype(int v) noexcept
            : val(v) {
        value_ctor_count++;
    }
    cnttype(const cnttype& other) noexcept
            : val(other.val) {
        copy_ctor_count++;
    }
    cnttype(cnttype&& other) noexcept
            : val(other.val) {
        move_ctor_count++;
    }
    cnttype& operator=(const cnttype& other) noexcept {
        val = other.val;
        copy_assign_count++;
        return *this;
    }
    cnttype& operator=(cnttype&& other) noexcept {
        val = other.val;
        move_assign_count++;
        return *this;
    }
    ~cnttype() {
        dtor_count++;
    }
};

struct cnttype_copy {
    static inline int default_ctor_count = 0;
    static inline int value_ctor_count = 0;
    static inline int copy_ctor_count = 0;
    static inline int copy_assign_count = 0;
    static inline int dtor_count = 0;

    static void reset() {
        default_ctor_count = 0;
        value_ctor_count = 0;
        copy_ctor_count = 0;
        copy_assign_count = 0;
        dtor_count = 0;
    }

    int val = 0;

    cnttype_copy() noexcept {
        default_ctor_count++;
    }
    explicit cnttype_copy(int v) noexcept
            : val(v) {
        value_ctor_count++;
    }
    cnttype_copy(const cnttype_copy& other) noexcept
            : val(other.val) {
        copy_ctor_count++;
    }
    cnttype_copy(cnttype_copy&& other) = delete;
    cnttype_copy& operator=(const cnttype_copy& other) noexcept {
        val = other.val;
        copy_assign_count++;
        return *this;
    }
    cnttype_copy& operator=(cnttype_copy&& other) = delete;
    ~cnttype_copy() {
        dtor_count++;
    }
};

struct cnttype_move {
    static inline int default_ctor_count = 0;
    static inline int value_ctor_count = 0;
    static inline int move_ctor_count = 0;
    static inline int move_assign_count = 0;
    static inline int dtor_count = 0;

    static void reset() {
        default_ctor_count = 0;
        value_ctor_count = 0;
        move_ctor_count = 0;
        move_assign_count = 0;
        dtor_count = 0;
    }

    int val = 0;

    cnttype_move() noexcept {
        default_ctor_count++;
    }
    explicit cnttype_move(int v) noexcept
            : val(v) {
        value_ctor_count++;
    }
    cnttype_move(const cnttype_move& other) = delete;
    cnttype_move(cnttype_move&& other) noexcept
            : val(other.val) {
        move_ctor_count++;
    }
    cnttype_move& operator=(const cnttype_move& other) = delete;
    cnttype_move& operator=(cnttype_move&& other) noexcept {
        val = other.val;
        move_assign_count++;
        return *this;
    }
    ~cnttype_move() {
        dtor_count++;
    }
};

}  // namespace Testing

#endif
