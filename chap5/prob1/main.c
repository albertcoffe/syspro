#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;

    if (argc != 2) {
        printf("usage:./main test.txt\n");
        return 1;
    }

    fd = open(argv[1], O_RDWR);

    if (fd == -1) {
        printf("File Open Error\n");
        perror(argv[1]);
        return 1;
    }

    printf("file %s Open Success : %d\n", argv[1], fd);

    close(fd);
    return 0;
}
