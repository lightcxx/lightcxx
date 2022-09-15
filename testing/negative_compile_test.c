#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char* const* environ;

#define MAX_NUM_RUNS 999
#define MAX_NUM_RUNS_STR "999"

static const char* usage = "Usage: %s <num-runs> <msg-pattern> <source-file> <compiler> [<compiler-flags>...]\n";
#define PRINT_ERROR_USAGE_AND_EXIT(...) \
    do {                                \
        printf(__VA_ARGS__);            \
        printf(usage, argv[0]);         \
        return EXIT_FAILURE;            \
    } while (0)

int main(int argc, char** argv) {
    if (argc < 5) {
        PRINT_ERROR_USAGE_AND_EXIT("Incorrect number of arguments.\n");
    }

    char* const arg_num_runs = argv[1];
    char* const arg_msg_pattern = argv[2];
    char* const arg_source_file = argv[3];
    char* const arg_compiler = argv[4];
    char** const arg_compiler_flags = argv + 5;
    const int arg_compiler_flags_size = argc - 5;

    int num_runs = atoi(arg_num_runs);
    if (num_runs <= 0) {
        PRINT_ERROR_USAGE_AND_EXIT("Invalid num runs '%s' (expected positive number)\n", arg_num_runs);
    }
    if (num_runs > MAX_NUM_RUNS) {
        PRINT_ERROR_USAGE_AND_EXIT("Invalid num runs '%s' (way too many runs, clearly a bug)\n", arg_num_runs);
    }

    int has_msg_pattern = (arg_msg_pattern[0] != '\0') && (arg_msg_pattern[0] != '.' || arg_msg_pattern[1] != '*' || arg_msg_pattern[2] != '\0');
    regex_t msg_pattern;
    if (has_msg_pattern) {
        int regcomp_status = regcomp(&msg_pattern, arg_msg_pattern, REG_EXTENDED | REG_NOSUB);
        if (regcomp_status != 0) {
            char regerror_msg[256];
            regerror(regcomp_status, &msg_pattern, regerror_msg, 256);
            PRINT_ERROR_USAGE_AND_EXIT("Invalid message pattern '%s': %s\n", arg_msg_pattern, regerror_msg);
        }
    }

    for (int test_id = 0; test_id < num_runs; test_id++) {
        size_t cmd_capacity = 16;
        char** cmd = malloc(cmd_capacity * sizeof(char*));
        size_t cmd_size = 0;
#define ADD_CMD_ARG(arg)                      \
    do {                                      \
        if (cmd_size + 1 == cmd_capacity) {   \
            cmd_capacity *= 2;                \
            cmd = realloc(cmd, cmd_capacity); \
        }                                     \
        cmd[cmd_size++] = arg;                \
        cmd[cmd_size] = NULL;                 \
    } while (0)

        ADD_CMD_ARG(arg_compiler);
        for (int arg_cmd_index = 0; arg_cmd_index < arg_compiler_flags_size; arg_cmd_index++) {
            ADD_CMD_ARG(arg_compiler_flags[arg_cmd_index]);
        }
        ADD_CMD_ARG(strdup("-c"));
        ADD_CMD_ARG(arg_source_file);
        ADD_CMD_ARG(strdup("-o"));
        ADD_CMD_ARG(strdup("/dev/null"));
        ADD_CMD_ARG(strdup("-DNEGATIVE_COMPILE_ITERATION=" MAX_NUM_RUNS_STR));
        sprintf(cmd[cmd_size - 1], "-DNEGATIVE_COMPILE_ITERATION=%d", test_id);

        const char* test_filename = arg_source_file;
        const char* cursor = strstr(test_filename, "/tests/");
        if (cursor != NULL) {
            test_filename = cursor + 7;
        }
        printf("Running test %s (negative compile iteration #%d)\n", test_filename, test_id);

        int pipe_fd[2];
        if (pipe(pipe_fd) < 0) {
            printf("pipe failed: errno=%d message=%s\n", errno, strerror(errno));
            return 1;
        }

        pid_t pid = fork();
        if (pid == -1) {
            printf("fork failed: return=%d, errno=%d, message=%s\n", pid, errno, strerror(errno));
            return 1;
        }
        if (pid == 0) {
            close(pipe_fd[0]);                          // close pipe read end in child
            if (dup2(pipe_fd[1], STDOUT_FILENO) < 0) {  // pipe stdout to parent
                printf("dup2 failed: errno=%d message=%s\n", errno, strerror(errno));
                // Still inform the parent we failed.
                const char* msg = "ERROR: dup2 didn't work, check stdout for details.\n";
                write(pipe_fd[1], msg, strlen(msg));  // If this fails, tough luck, nothing to do.
                // Since this is a compiler failure test, returning 0 from the
                // subprocess will ensure the test fails.
                return 0;
            }
            if (dup2(pipe_fd[1], STDERR_FILENO) < 0) {  // pipe stderr to parent
                printf("dup2 failed: errno=%d message=%s\n", errno, strerror(errno));
                // Still inform the parent we failed.
                const char* msg = "ERROR: dup2 didn't work, check stdout for details.\n";
                write(pipe_fd[1], msg, strlen(msg));  // If this fails, tough luck, nothing to do.
                // Since this is a compiler failure test, returning 0 from the
                // subprocess will ensure the test fails.
                return 0;
            }
            close(pipe_fd[1]);  // close pipe write end after dup
            execve(cmd[0], cmd, environ);
            printf("execve failed: errno=%d message=%s\n", errno, strerror(errno));
            printf("Command line:\n ");
            for (int cmd_index = 0; cmd_index < cmd_size; cmd_index++) {
                printf(" %s", cmd[cmd_index]);
            }
            printf("\n");
            return 0;
        }

        close(pipe_fd[1]);  // close write end in parent.
        // Allocate buffer for compiler output.
        size_t compiler_output_size = 0;
        size_t compiler_output_capacity = 1 << 16;
        char* compiler_output = malloc(compiler_output_capacity);
#define ADD_COMPILER_OUTPUT(buffer, size)                                         \
    do {                                                                          \
        while (compiler_output_size + size >= compiler_output_capacity) {         \
            compiler_output_capacity *= 2;                                        \
            compiler_output = realloc(compiler_output, compiler_output_capacity); \
        }                                                                         \
        memcpy(compiler_output + compiler_output_size, buffer, size);             \
        compiler_output_size += size;                                             \
    } while (0)
        char pipe_buffer[256];
        while (1) {
            ssize_t num_bytes = read(pipe_fd[0], pipe_buffer, 255);
            if (num_bytes < 0) {
                printf("read failed: errno=%d message=%s\n", errno, strerror(errno));
                return 1;
            }
            if (num_bytes == 0) {
                break;
            }
            ADD_COMPILER_OUTPUT(pipe_buffer, num_bytes);
        }
        close(pipe_fd[0]);  // close read end in parent after the run.
        char eos[1] = "";
        ADD_COMPILER_OUTPUT(eos, 1);  // null terminator
#define PRINT_COMPILER_CMD_AND_OUTPUT()                              \
    do {                                                             \
        printf("command:");                                          \
        for (int cmd_index = 0; cmd_index < cmd_size; cmd_index++) { \
            printf(" %s", cmd[cmd_index]);                           \
        }                                                            \
        printf("\n"                                                  \
               "------ BEGIN COMPILER OUTPUT ------\n"               \
               "%s\n"                                                \
               "------  END  COMPILER OUTPUT ------\n",              \
               compiler_output);                                     \
    } while (0)
        int compiler_status;
        int child_pid = wait(&compiler_status);
        if (child_pid != pid) {
            printf("wait failed: returned=%d child_pid=%d errno=%d message=%s\n", child_pid, pid, errno, strerror(errno));
            return 1;
        }
        if (WIFSIGNALED(compiler_status)) {
            PRINT_COMPILER_CMD_AND_OUTPUT();
            printf("Compiler killed by signal %d.\n", (int)(WTERMSIG(compiler_status)));
            return 1;
        }
        if (WEXITSTATUS(compiler_status) == 0) {
            PRINT_COMPILER_CMD_AND_OUTPUT();
            printf("Compiler exited with code 0.\n");
            return 1;
        }

        if (has_msg_pattern) {
            int regexec_status = regexec(&msg_pattern, compiler_output, 0, NULL, 0);
            if (regexec_status == REG_NOMATCH) {
                PRINT_COMPILER_CMD_AND_OUTPUT();
                printf("Pattern '%s' not found in compiler output.\n", arg_msg_pattern);
                return 1;
            }
        }

        free(compiler_output);  // Free compiler output buffer.
    }
    return 0;
}