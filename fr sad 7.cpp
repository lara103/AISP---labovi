#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct QCvor;
typedef struct QCvor* QPosition;

typedef struct QCvor {
    int El;
    int Priority;
    QPosition Next;
} QCvor;

struct Cvor;
typedef struct Cvor* Position;

typedef struct Cvor {
    int El;
    Position Next;
} Cvor;


int Stack(Position);
int Queue(QPosition);

int Push(Position, int);
int Pop(Position);

int Count(Position);
int PrintList(Position);
int CloseStack(Position);

int Enqueue(QPosition);
int Dequeue(QPosition);
int PrintListQ(QPosition);

int main()
{
    Cvor head;
    QCvor qhead;

    head.Next = NULL;
    qhead.Next = NULL;

    srand((unsigned)time(NULL));

    int choice = 0;

    while (choice != 3)
    {
        printf("\n1. Circular stack\n2. Priority queue\n3. Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            Stack(&head);
            break;
        case 2:
            Queue(&qhead);
            break;
        case 3:
            break;
        default:
            printf("Error\n");
        }
    }

    return 0;
}

int Stack(Position head)
{
    int max = 0;

    while (max < 1 || max > 50)
    {
        printf("Enter max stack size (1-50): ");
        scanf("%d", &max);
    }

    int choice = 0;

    while (choice != 3)
    {
        printf("\n1. Push\n2. Pop\n3. Back\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            Push(head, max);
            PrintList(head->Next);
            break;
        case 2:
            Pop(head);
            PrintList(head->Next);
            break;
        case 3:
            CloseStack(head);
            break;
        default:
            printf("Error\n");
        }
    }

    return 0;
}

int Push(Position head, int max)
{
    if (Count(head) >= max)
    {
        printf("Stack is full\n");
        return -1;
    }

    Position q = (Position)malloc(sizeof(Cvor));
    if (!q)
        return -1;

    q->El = rand() % 91 + 10;

    if (head->Next == NULL)
    {
        head->Next = q;
        q->Next = q;
    }
    else
    {
        Position last = head->Next;
        while (last->Next != head->Next)
            last = last->Next;

        q->Next = head->Next;
        head->Next = q;
        last->Next = q;
    }

    printf("Push: %d\n", q->El);
    return 0;
}

int Pop(Position head)
{
    if (head->Next == NULL)
    {
        printf("Stack is empty\n");
        return -1;
    }

    Position first = head->Next;

    if (first->Next == first)
    {
        printf("Pop: %d\n", first->El);
        free(first);
        head->Next = NULL;
        return 0;
    }

    Position last = first;
    while (last->Next != first)
        last = last->Next;

    head->Next = first->Next;
    last->Next = head->Next;

    printf("Pop: %d\n", first->El);
    free(first);

    return 0;
}

int Count(Position head)
{
    if (head->Next == NULL)
        return 0;

    int count = 1;
    Position p = head->Next;

    while (p->Next != head->Next)
    {
        count++;
        p = p->Next;
    }

    return count;
}

int PrintList(Position first)
{
    if (!first)
        return 0;

    Position p = first;
    printf("Stack:");

    do
    {
        printf(" %d", p->El);
        p = p->Next;
    } while (p != first);

    printf("\n");
    return 0;
}

int CloseStack(Position head)
{
    while (head->Next != NULL)
        Pop(head);
    return 0;
}

int Queue(QPosition head)
{
    int choice = 0;

    while (choice != 3)
    {
        printf("\n1. Enqueue\n2. Dequeue\n3. Back\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            Enqueue(head);
            PrintListQ(head->Next);
            break;
        case 2:
            Dequeue(head);
            PrintListQ(head->Next);
            break;
        case 3:
            break;
        default:
            printf("Error\n");
        }
    }

    return 0;
}

int Enqueue(QPosition head)
{
    QPosition q = (QPosition)malloc(sizeof(QCvor));
    if (!q)
        return -1;

    q->Priority = rand() % 5 + 1;
    q->El = rand() % 91 + 10;

    while (head->Next && head->Next->Priority >= q->Priority)
        head = head->Next;

    q->Next = head->Next;
    head->Next = q;

    printf("Enqueue: %d (priority %d)\n", q->El, q->Priority);
    return 0;
}

int Dequeue(QPosition head)
{
    if (!head->Next)
    {
        printf("Queue is empty\n");
        return -1;
    }

    QPosition q = head->Next;
    head->Next = q->Next;

    printf("Dequeue: %d\n", q->El);
    free(q);
    return 0;
}

int PrintListQ(QPosition p)
{
    printf("Queue:");
    while (p)
    {
        printf(" %d", p->El);
        p = p->Next;
    }
    printf("\n");
    return 0;
}


