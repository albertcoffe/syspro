#include <stdio.h>
#include "copy.h"
#include <string.h>

#define NLINES 5

char line[MAXLINE];
char lines[NLINES][MAXLINE];
char temp[MAXLINE];

int main() {
    int len;
    int i, j, count;

    count = 0;
    while (count < NLINES && fgets(line, MAXLINE, stdin) != NULL) {
        copy(line, lines[count]);
        count++;
    }

    i = 0;
    while (i < NLINES - 1) {
        j = 0;
        while (j < NLINES - 1 - i) {
            if (strlen(lines[j]) < strlen(lines[j + 1])) {
                copy(lines[j], temp);
                copy(lines[j + 1], lines[j]);
                copy(temp, lines[j + 1]);
            }
            j++;
        }
        i++;
    }

    i = 0;
    while (i < NLINES) {
        printf("%s", lines[i]);
        i++;
    }

    return 0;
}

