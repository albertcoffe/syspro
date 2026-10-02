#include "copy.h"

void copy(char *s, char *t) {
    int i;
    i = 0;
    while ((t[i] = s[i]) != '\0') {
        ++i;
    }
}
