#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    char savedText[10][100] = {{0}};
    char buf;

    int fd;
    int row = 0;
    int col = 0;
    int total;
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

    for (i = total - 1; i >= 0; i--) {
        printf("%s\n", savedText[i]);
    }

    printf("\n");

    return 0;
}
