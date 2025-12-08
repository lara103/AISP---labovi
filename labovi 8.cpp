//8. Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa rezultat.Stog
//je potrebno realizirati preko vezane liste.
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

void Push(Position, int);
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
        printf("Error\n", filename);
        return 1;
    }

    printf("\nExpression: ");
    char token[32] = { 0 };
    int x;
    while (fscanf(file, "%s", token) == 1) {
        printf(" %s", token);

        x = atoi(token);
        if (x == 0 && token[0] != '0') {
            int a, b, result;
            b = Pop(&Stack);
            a = Pop(&Stack);
            result = Calculate(a, token[0], b);
            Push(&Stack, result);
        }
        else {
            Push(&Stack, x);
        }
    }
    fclose(file);

    printf("\nResult: %d\n", Stack.Next->Element);
 

    FreeStack(&Stack);
}

void Push(Position P, int n)
{
    Position q = (Position)malloc(sizeof(struct Node));
    if (q) {
        q->Element = n;
        q->Next = P->Next;
        P->Next = q;
    }
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
            printf("\nError \n");
        break;
    case '%':
        result = x % y;
        break;
    default:
        break;
    }
    return result;
}
void FreeStack(Position P) {

    Position tmp;
    while (P->Next != NULL) {
        tmp = P->Next;
        P->Next = tmp->Next;
        free(tmp);
    }
}



