
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG 100

int main()
{
    char line[MAXLINE];
    char *args[MAXARG];
    char *token, *saveptr;
    int argc, background, status;
    pid_t pid;

    while (1) {
        while (waitpid(-1, NULL, WNOHANG) > 0);

        printf("Pls input cmd : ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        argc = 0;
        background = 0;

        token = strtok_r(line, " \t\n", &saveptr);

        while (token != NULL && argc < MAXARG - 1) {
            args[argc++] = token;
            token = strtok_r(NULL, " \t\n", &saveptr);
        }

        if (argc == 0)
            continue;

        args[argc] = NULL;

        if (strcmp(args[0], "exit") == 0)
            break;

        if (strcmp(args[argc - 1], "&") == 0) {
            background = 1;
            args[--argc] = NULL;
        }

        if (argc == 0)
            continue;

        pid = fork();

        if (pid < 0) {
            perror("fork");
            continue;
        }

        if (pid == 0) {
            printf("[%d] child process start\n", getpid());
            fflush(stdout);

            execvp(args[0], args);
            perror("execvp");
            exit(1);
        }
        else {
            printf("[%d] Parent process start\n", getpid());

            if (background == 0) {
                waitpid(pid, &status, 0);
                printf("[%d] child process end %d\n",
                       getpid(), pid);
            }
            else {
                printf("[%d] Background process %d\n",
                       getpid(), pid);
            }

            printf("SUCCESS\n");
        }
    }

    printf("Exit\n");

    return 0;
}

