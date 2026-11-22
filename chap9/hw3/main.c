
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG 100

void execute(char *cmd)
{
    char *args[MAXARG];
    char *token, *saveptr;
    char *infile = NULL, *outfile = NULL;
    int argc = 0;
    int background = 0;
    int fd;
    pid_t pid;

    token = strtok_r(cmd, " \t\n", &saveptr);

    while (token != NULL && argc < MAXARG - 1) {
        if (strcmp(token, "&") == 0) {
            background = 1;
        }
        else if (strcmp(token, ">") == 0) {
            token = strtok_r(NULL, " \t\n", &saveptr);
            outfile = token;
        }
        else if (strcmp(token, "<") == 0) {
            token = strtok_r(NULL, " \t\n", &saveptr);
            infile = token;
        }
        else {
            args[argc++] = token;
        }

        token = strtok_r(NULL, " \t\n", &saveptr);
    }

    args[argc] = NULL;

    if (argc == 0)
        return;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        if (infile != NULL) {
            fd = open(infile, O_RDONLY);
            if (fd < 0) {
                perror("open");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        if (outfile != NULL) {
            fd = open(outfile,
                      O_WRONLY | O_CREAT | O_TRUNC,
                      0644);
            if (fd < 0) {
                perror("open");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        execvp(args[0], args);
        perror("execvp");
        exit(1);
    }
    else {
        if (!background) {
            waitpid(pid, NULL, 0);
        }
        else {
            printf("[Background PID: %d]\n", pid);
        }
    }
}

int main()
{
    char line[MAXLINE];
    char *cmd, *saveptr;

    while (1) {
        while (waitpid(-1, NULL, WNOHANG) > 0);

        printf("[shell] ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        if (strcmp(line, "exit\n") == 0 ||
            strcmp(line, "exit") == 0)
            break;

        cmd = strtok_r(line, ";", &saveptr);

        while (cmd != NULL) {
            char command[MAXLINE];

            strcpy(command, cmd);
            execute(command);

            cmd = strtok_r(NULL, ";", &saveptr);
        }
    }

    return 0;
}

