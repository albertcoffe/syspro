#include <stdio.h>

void print_file(FILE *fp, int numbered) {
    int c;
    int line = 1;
    int new_line = 1;

    c = getc(fp);
    while (c != EOF) {
        if (numbered && new_line) {
            printf("%3d ", line++);
            new_line = 0;
        }
        putc(c, stdout);
        if (c == '\n')
            new_line = 1;
        c = getc(fp);
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int i;
    int numbered = 0;
    int start = 1;

    if (argc < 2) {
        fp = stdin;
        print_file(fp, 0);
        return 0;
    }

    if (argv[1][0] == '-' && argv[1][1] == 'n') {
        numbered = 1;
        start = 2;
    }

    for (i = start; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stderr, "File %s Open Error\n", argv[i]);
            continue;
        }
        print_file(fp, numbered);
        fclose(fp);
    }

    return 0;
}

