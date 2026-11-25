#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node *top, int data)
{
    struct node *p;

    p = malloc(sizeof(struct node));

    if (p == NULL)
        exit(1);

    p->data = data;
    p->next = top->next;
    top->next = p;
}

int pop(struct node *top)
{
    struct node *p;
    int data;

    p = top->next;
    data = p->data;
    top->next = p->next;

    free(p);

    return data;
}

int main()
{
    struct node top;
    int data;
    char input[100];
    char extra;

    top.next = NULL;

    while (scanf("%99s", input) == 1) {
        if (sscanf(input, "%d%c", &data, &extra) != 1
            || data <= 0)
            break;

        push(&top, data);
    }

    printf("Print stack\n");

    while (top.next != NULL) {
        printf("%d\n", pop(&top));
    }

    return 0;
}
