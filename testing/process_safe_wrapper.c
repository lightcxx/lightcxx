#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    pid_t pid = fork();

    if (pid == -1) {
        return 1;
    }

    if (pid == 0) {
        execvp(argv[1], argv + 1);
        return 1;
    }

    int status = 0;
    int wait_ret = wait(&status);
    if (wait_ret != pid) {
        printf("EXPECTATION FAILED: WAIT FAILED. return=%d, errno=%d, message=%s",
               wait_ret,
               errno,
               strerror(errno));
        return 1;
    }
    printf("\n----\n");
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGABRT) {
            printf("PROCESS EXIT KILLED BY SIGNAL SIGABRT\n");
        } else {
            printf("PROCESS EXIT KILLED BY SIGNAL %d\n", WTERMSIG(status));
        }
    } else if (WIFEXITED(status)) {
        printf("PROCESS EXIT CODE = %d\n", WEXITSTATUS(status));
    } else {
        printf("EXPECTATION FAILED: PROCESS EXITED BY UNKNOWN MEANS. status=%d\n", status);
    }
    return 0;
}
