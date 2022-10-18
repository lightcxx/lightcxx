// Tests are NOT allowed to expect to exit with code 7, so
// this will always be a test fail.
#define ALWAYS_ERROR_EXIT_CODE 7

typedef __SIZE_TYPE__ size_t;

extern __attribute__((__noreturn__)) void _Exit(int);
extern long write(int, const char*, size_t);

typedef void (*test_def_t)(void);

static void** tests_tail;
static void** tests_head;

static void write_str(const char* buf) {
    size_t len = 0;
    while (buf[len]) {
        len++;
    }
    size_t total_written = 0;
    while (1) {
        long written = write(1, buf + total_written, len - total_written);
        if (written <= 0) {
            // If writing fails, there's really no way to print a valuable error message.
            _Exit(ALWAYS_ERROR_EXIT_CODE);
        }
        total_written += (size_t)written;
        if (total_written == len) {
            break;
        }
    }
}

void testing_fail_impl(const char* func, const char* file, const char* line) {
    write_str("EXPECTATION FAILED: IN FUNCTION ");
    write_str(func);
    write_str(" (");
    write_str(file);
    write_str(":");
    write_str(line);
    write_str(")\n");
    _Exit(ALWAYS_ERROR_EXIT_CODE);
}

void step(const char* msg) {
    write_str("STEP: ");
    write_str(msg);
    write_str("\n");
}

void testing_register_test(test_def_t test, void* buffer[2]) {
    if (tests_head == 0) {
        tests_head = buffer;
    }
    buffer[0] = 0;
    buffer[1] = (void*)test;
    if (tests_tail != 0) {
        tests_tail[0] = buffer;
    }
    tests_tail = buffer;
}

int main(void) {
    for (void** ptr = tests_head; ptr != 0; ptr = (void**)ptr[0]) {
        ((test_def_t)ptr[1])();
    }
    return 0;
}
