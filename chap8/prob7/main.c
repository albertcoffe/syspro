
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char *argv[])
{
    int i;

    if (argc < 2) {
        printf("Enter an option.\n");
        return 1;
    }

    if (strcmp(argv[1], "-e") == 0) {
        if (argc == 2) {
            for (i = 0; environ[i] != NULL; i++) {
                printf("%s\n", environ[i]);
            }
        }
        else {
            char *value = getenv(argv[2]);

            if (value != NULL)
                printf("%s\n", value);
            else
                printf("not found\n");
        }
    }
    else if (strcmp(argv[1], "-u") == 0) {
        printf("User ID: %d\n", (int)getuid());
        printf("E User ID: %d\n", (int)geteuid());
    }
    else if (strcmp(argv[1], "-g") == 0) {
        printf(" Group ID: %d\n", (int)getgid());
        printf("E Group ID: %d\n", (int)getegid());
    }
    else if (strcmp(argv[1], "-i") == 0) {
        printf("Process ID: %d\n", (int)getpid());
    }
    else if (strcmp(argv[1], "-p") == 0) {
        printf("Process ID: %d\n", (int)getppid());
    }
    else {
        printf(" option.\n");
    }

    return 0;
}

