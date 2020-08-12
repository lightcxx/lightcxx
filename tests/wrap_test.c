#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    pid_t pid = fork();

    if (pid == -1) {
        return 1;
    }

    if (pid == 0) {
        execvp(argv[1], argv + 1);
        exit(1);
    }

    int status = 0;
    wait(&status);
    printf("\n----\n");
    if (WIFSIGNALED(status)) {
        printf("TEST EXITED BY SIGNAL: %d\n", WTERMSIG(status));
    } else if (WIFEXITED(status)) {
        printf("TEST EXITED WITH CODE: %d\n", WEXITSTATUS(status));
    } else {
        printf("TEST EXITED BY UNKNOWN MEANS.\n");
    }
    return 0;
}
