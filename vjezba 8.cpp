#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Node;
typedef struct Node* Position;

struct Node {
    int Element;
    Position Next;
};

int Push(Position, int);
int Pop(Position);
int Calculate(int, char, int);
void FreeStack(Position);

int main(void)
{
    struct Node Stack;
    FILE* file;
    char filename[1024] = { 0 };

    Stack.Next = NULL;

    printf("Enter filename: (Text.txt)\n ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error\n");
        return -1;
    }

    printf("\nExpression: ");
    char token[32] = { 0 };
    int x;

    while (fscanf(file, "%s", token) == 1) {
        printf(" %s", token);

        x = atoi(token);
        if (x == 0 && token[0] != '0') {
            int a, b, result;

            if (Stack.Next == NULL) {
                printf("Error not enough numbers on stack\n");
                fclose(file);
                FreeStack(&Stack);
                return -1;
            }
            b = Pop(&Stack);

            if (Stack.Next == NULL) {
                printf("Error not enough numbers on stack\n");
                fclose(file);
                FreeStack(&Stack);
                return -1;
            }
            a = Pop(&Stack);

            result = Calculate(a, token[0], b);
            if (Push(&Stack, result) == -1) {
                printf("Error\n");
                fclose(file);
                FreeStack(&Stack);
                return -1;
            }
        }
        else {
            if (Push(&Stack, x) == -1) {
                printf("Error\n");
                fclose(file);
                FreeStack(&Stack);
                return -1;
            }
        }
    }

    fclose(file);

    if (Stack.Next == NULL) {
        printf("Error\n");
        FreeStack(&Stack);
        return -1;
    }
    else {
        int final = Pop(&Stack);

        if (Stack.Next != NULL) {
            printf("Error too much numbers\n");
            FreeStack(&Stack);
            return -1;
        }
        else {
            printf("\nResult: %d\n", final);
        }
    }

    FreeStack(&Stack);
    return 0;
}



int Push(Position P, int n)
{
    Position q = (Position)malloc(sizeof(struct Node));
    if (q == NULL)
        return -1;

    q->Element = n;
    q->Next = P->Next;
    P->Next = q;

    return 0;
}

int Pop(Position P)
{
    Position tmp;
    int n = 0;

    if (P->Next != NULL) {
        tmp = P->Next;
        P->Next = tmp->Next;
        n = tmp->Element;
        free(tmp);
    }
    return n;
}

int Calculate(int x, char op, int y)
{
    int result = 0;

    switch (op) {
    case '+':
        result = x + y;
        break;
    case '-':
        result = x - y;
        break;
    case '*':
        result = x * y;
        break;
    case '/':
        if (y != 0)
            result = x / y;
        else
            printf("Error division by zero\n");
        break;
    case '%':
        result = x % y;
        break;
    default:
        printf("Unknown operator\n");
    }
    return result;
}

void FreeStack(Position P)
{
    Position tmp;
    while (P->Next != NULL) {
        tmp = P->Next;
        P->Next = tmp->Next;
        free(tmp);
    }
}
