#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char *mode_name;

    if (argc != 2) {
        fprintf(stderr, "How to use: %s [stdin|stdout|stderr|FileName]\n", argv[0]);
        return 1;
    }

    if (!strcmp(argv[1], "stdin"))
        fp = stdin;
    else if (!strcmp(argv[1], "stdout"))
        fp = stdout;
    else if (!strcmp(argv[1], "stderr"))
        fp = stderr;
    else
        fp = fopen(argv[1], "r");

    if (fp == NULL) {
        fprintf(stderr, "Error Open File\n");
        return 2;
    }

    if (fp == stdin)
        mode_name = "stdin -> line buffered (줄 버퍼 방식)";
    else if (fp == stdout)
        mode_name = "stdout -> line buffered (줄 버퍼 방식)";
    else if (fp == stderr)
        mode_name = "stderr -> unbuffered (버퍼 미사용)";
    else
        mode_name = "general file -> fully buffered (완전 버퍼 방식)";

    printf("Stream = %s, %s\n", argv[1], mode_name);

    if (fp != stdin && fp != stdout && fp != stderr)
        fclose(fp);

    return 0;
}

