// Tests are NOT allowed to expect to exit with code 7, so
// this will always be a test fail.
#define ALWAYS_ERROR_EXIT_CODE 7

typedef __SIZE_TYPE__ size_t;

extern __attribute__((__noreturn__)) void _Exit(int);
extern long write(int, const char*, size_t);

struct test_def {
    void (*test_func)(void);
    const char* name;
};
typedef struct test_def test_def_t;

enum {
    MAX_NUM_TESTS = 256,
    OUTPUT_LINE_CAP = 4096 - sizeof(size_t),
};

static test_def_t tests[MAX_NUM_TESTS];
static size_t num_tests = 0;
static char output_line[OUTPUT_LINE_CAP];

static void write_output_line(size_t sz);
static void push_char(size_t* current_sz, char ch);
static void push_string(size_t* current_sz, const char* buf);
static void push_int(size_t* current_sz, int i);

static void check_size(size_t* current_sz, size_t sz) {
    if (*current_sz + sz >= OUTPUT_LINE_CAP) {
        size_t err_sz = 0;
        push_string(&err_sz, "EXPECTATION FAILED: Output line too long! Check capacity in testing.c");
        write_output_line(err_sz);
        _Exit(ALWAYS_ERROR_EXIT_CODE);
    }
}

static void push_char(size_t* current_sz, char ch) {
    check_size(current_sz, (size_t)1);
    output_line[(*current_sz)++] = ch;
}

static void push_string(size_t* current_sz, const char* buf) {
    for (const char* ptr = buf; *ptr != '\0'; ptr++) {
        push_char(current_sz, *ptr);
    }
}

static void push_int(size_t* current_sz, int i) {
    size_t num_digits = 0;
    int j = i;
    do {
        i /= 10;
        num_digits++;
    } while (i > 0);
    check_size(current_sz, num_digits);
    size_t pos = *current_sz + num_digits - 1;
    do {
        output_line[pos--] = (char)('0' + j % 10);
        j /= 10;
    } while (j > 0);
    *current_sz += num_digits;
}

static void write_output_line(size_t sz) {
    push_char(&sz, '\n');
    size_t total_written = 0;
    while (1) {
        long written = write(1, output_line + total_written, sz - total_written);
        if (written <= 0) {
            // If writing fails, there's really no way to print a valuable error message.
            _Exit(ALWAYS_ERROR_EXIT_CODE);
        }
        total_written += (size_t)written;
        if (total_written == sz) {
            break;
        }
    }
}

void testing_fail_impl(const char* func, const char* file, int line) {
    size_t sz = 0;
    push_string(&sz, "EXPECTATION FAILED: IN FUNCTION ");
    push_string(&sz, func);
    push_string(&sz, " (");
    push_string(&sz, file);
    push_char(&sz, ':');
    push_int(&sz, line);
    push_char(&sz, ')');
    write_output_line(sz);
    _Exit(ALWAYS_ERROR_EXIT_CODE);
}

void testing_expect_impl(int cnd, const char* func, const char* file, int line) {
    if (!cnd) {
        testing_fail_impl(func, file, line);
    }
}

void step(const char* msg) {
    size_t sz = 0;
    push_string(&sz, "STEP: ");
    push_string(&sz, msg);
    write_output_line(sz);
}

void testing_register_test(void (*test)(void), const char* name) {
    if (num_tests >= MAX_NUM_TESTS) {
        size_t sz = 0;
        push_string(&sz, "EXPECTATION FAILED: Too many tests registered in one binary. Check limit in testing.c.");
        write_output_line(sz);
        _Exit(ALWAYS_ERROR_EXIT_CODE);
    }
    tests[num_tests].test_func = test;
    tests[num_tests].name = name;
    num_tests++;
}

int main(void) {
    for (size_t i = 0; i < num_tests; i++) {
        tests[i].test_func();
    }
    return 0;
}
