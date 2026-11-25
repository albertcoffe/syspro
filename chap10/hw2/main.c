#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node *head, struct node *tail, int data)
{
    struct node *p;

    p = malloc(sizeof(struct node));

    if (p == NULL)
        exit(1);

    p->data = data;
    p->next = NULL;

    if (head->next == NULL)
        head->next = p;
    else
        tail->next->next = p;

    tail->next = p;
}

int delete(struct node *head, struct node *tail)
{
    struct node *p;
    int data;

    p = head->next;
    data = p->data;
    head->next = p->next;

    if (head->next == NULL)
        tail->next = NULL;

    free(p);

    return data;
}

int main()
{
    struct node head, tail;
    int data;
    char input[100];
    char extra;

    head.next = NULL;
    tail.next = NULL;

    while (scanf("%99s", input) == 1) {
        if (sscanf(input, "%d%c", &data, &extra) != 1
            || data <= 0)
            break;

        addq(&head, &tail, data);
    }

    printf("Print queue\n");

    while (head.next != NULL) {
        printf("%d\n", delete(&head, &tail));
    }

    return 0;
}
