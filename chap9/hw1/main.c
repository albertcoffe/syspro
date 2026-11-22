
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("=== Assignment 1 ===\n");

    printf("\n1. sleep 100 &\n");
    system("sleep 100 &");

    printf("\n2. sleep 100 &\n");
    system("sleep 100 &");

    printf("\n3. jobs\n");
    system("jobs");

    printf("\n4. ps -f\n");
    system("ps -f");

    printf("\n5. kill %%1\n");
    system("kill %1");

    printf("\n6. ps -f\n");
    system("ps -f");

    return 0;
}

