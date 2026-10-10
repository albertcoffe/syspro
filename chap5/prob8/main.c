#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char savedText[10][100] = {{0}};
    char buf;
    char input[100];
    char *token;

    int fd;
    int row = 0;
    int col = 0;
    int total;
    int start, end;
    int number;
    int i;
    ssize_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: ./main test.txt\n");
        return 1;
    }

    fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    while ((result = read(fd, &buf, 1)) > 0) {
        if (row >= 10) {
            fprintf(stderr, "Too many lines\n");
            close(fd);
            return 1;
        }

        if (buf == '\n') {
            savedText[row][col] = '\0';
            row++;
            col = 0;
        } else {
            if (col >= 99) {
                fprintf(stderr, "Line too long\n");
                close(fd);
                return 1;
            }

            savedText[row][col] = buf;
            col++;
        }
    }

    if (result == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    close(fd);

    total = row;

    if (col > 0) {
        savedText[row][col] = '\0';
        total++;
    }
    printf("File read success\n");
    printf("Total Line : %d\n", total);
    printf("You can choose 1 ~ %d Line\n", total);
    printf("Pls 'Enter' the line to select : ");
    fflush(stdout);
    if (scanf("%99s", input) != 1) {
        return 1;
    }
    if (strcmp(input, "*") == 0) {
        for (i = 0; i < total; i++) {
            printf("%s\n", savedText[i]);
        }
    } else if (strchr(input, ',') != NULL) {
        token = strtok(input, ",");
        while (token != NULL) {
            number = atoi(token);
            if (number >= 1 && number <= total) {
                printf("%s\n", savedText[number - 1]);
            }
            token = strtok(NULL, ",");
        }
    } else if (strchr(input, '-') != NULL) {
        if (sscanf(input, "%d-%d", &start, &end) == 2) {
            if (start >= 1 && end <= total && start <= end) {
                for (i = start; i <= end; i++) {
                    printf("%s\n", savedText[i - 1]);
                }
            }
        }
    } else {
        number = atoi(input);

        if (number >= 1 && number <= total) {
            printf("%s\n", savedText[number - 1]);
        }
    }
    return 0;
}
