
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1, pid2;

    setbuf(stdout, NULL);

    pid1 = fork();

    if (pid1 == 0) {
        execl("/bin/sh", "sh", "-c",
              "echo START1; sleep 10; echo DONE1", NULL);
        exit(1);
    }

    pid2 = fork();

    if (pid2 == 0) {
        execl("/bin/sh", "sh", "-c",
              "echo START2; sleep 10; echo DONE2", NULL);
        exit(1);
    }

    printf("First PID: %d\n", pid1);
    printf("Second PID: %d\n", pid2);

    sleep(1);

    kill(pid1, SIGSTOP);
    printf("First process STOP\n");

    sleep(1);

    kill(pid1, SIGCONT);
    printf("First process CONT\n");

    sleep(1);

    kill(pid1, SIGKILL);
    printf("First process KILL\n");

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}

