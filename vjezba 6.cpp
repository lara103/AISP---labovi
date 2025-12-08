//6. Napisati program koji pomoću vezanih listi simulira rad :
//a) stoga,
//b) reda.
//Napomena: Funkcija "push" sprema cijeli broj, slučajno generirani u opsegu od 10 - 100.
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MIN 10
#define MAX 100

struct node;
typedef struct node* position;

struct node {
    int element;
    position next;
};

int GetValueFromRange(int, int);
void PushQueue(position, int);
void PushStack(position, int);
void Pop(position);
void PrintList(position);
void FreeList(position);

int main()
{
    srand((unsigned int)time(NULL));

    struct node stack, queue;
    stack.next = NULL;
    queue.next = NULL;

    int selection = 1;

    while (selection != 0)
    {
        printf("\n\t\t Menu \n");
        printf("0 - End program\n");
        printf("1 - Push on stack\n");
        printf("2 - Pop from stack\n");
        printf("3 - Push on queue\n");
        printf("4 - Pop from queue\n");
        printf("\n\nChoice:\t");
        scanf_s(" %d", &selection);

        switch (selection)
        {
        case 1:
            PushStack(&stack, GetValueFromRange(MIN, MAX));
            PrintList(stack.next);
            break;
        case 2:
            Pop(&stack);
            PrintList(stack.next);
            break;
        case 3:
            PushQueue(&queue, GetValueFromRange(MIN, MAX));
            PrintList(queue.next);
            break;
        case 4:
            Pop(&queue);
            PrintList(queue.next);
            break;
        case 0:
            selection = 0;
            break;
        default:
            printf("\nError!\n");
        }
    }

    FreeList(stack.next);
    FreeList(queue.next);

}

int GetValueFromRange(int minValue, int maxValue)
{
    return rand() % (maxValue - minValue + 1) + minValue;
}

void PrintList(position p) {
    printf("\nList: \n");
    while (p)
    {
        printf("%d ", p->element);
        p = p->next;
    }
    printf("\n");
}

void PushStack(position p, int value) {
    position temp = (position)malloc(sizeof(struct node));
    if (temp) {
        temp->element = value;
        temp->next = p->next;
        p->next = temp;
    }
}

void PushQueue(position p, int value) {
    position temp = (position)malloc(sizeof(struct node));
    if (temp) {
        temp->element = value;
        temp->next = NULL;
        position last = p;
        while (last->next != NULL) last = last->next;
        last->next = temp;
    }
}

void Pop(position p) {
    if (p->next != NULL) {
        position temp = p->next;
        p->next = temp->next;
        free(temp);
    }
}
void FreeList(position head) {
    position temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

