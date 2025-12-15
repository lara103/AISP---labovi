//Za dvije sortirane liste L1 i L2(mogu se pročitati iz datoteke ili unijeti ručno, bitno je samo da su
//	sortirane), napisati program koji stvara novu vezanu listu tako da računa :
//a) L1∪L2,
//b) L1∩ L2.
//Liste osim pokazivača na slijedeću strukturu imaju i jedan cjelobrojni element, po kojem su
//sortirane
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _Node;
typedef struct _Node* Position;

struct _Node {
    int Element;
    Position Next;
};


int ReadListFromFile(Position);
void PrintList(Position);
int Intersection(Position, Position, Position);
int Union(Position, Position, Position);
void freeList(Position);

int main(void) {
    Position headL1, headL2, headP, headU;

    headL1 = (Position)malloc(sizeof(struct _Node));
    if (headL1 == NULL) {
        printf("Error\n");
        return -1;
    }
    headL1->Next = NULL;

    headL2 = (Position)malloc(sizeof(struct _Node));
    if (headL2 == NULL) {
        printf("Error\n");
        return -1;
    }
    headL2->Next = NULL;

    headP = (Position)malloc(sizeof(struct _Node));
    if (headP == NULL) {
        printf("Error\n");
        return -1;
    }
    headP->Next = NULL;

    headU = (Position)malloc(sizeof(struct _Node));
    if (headU == NULL) {
        printf("Error\n");
        return -1;
    }
    headU->Next = NULL;


    ReadListFromFile(headL1);
    ReadListFromFile(headL2);

    printf("\nList L1: ");
    PrintList(headL1->Next);

    printf("\nList L2: ");
    PrintList(headL2->Next);

    Intersection(headL1->Next, headL2->Next, headP);
    printf("\nIntersection of L1 and L2: ");
    PrintList(headP->Next);


    Union(headL1->Next, headL2->Next, headU);
    printf("\nUnion of L1 and L2: ");
    PrintList(headU->Next);

    freeList(headL1);
    freeList(headL2);
    freeList(headP);
    freeList(headU);

    return 0;
}

int ReadListFromFile(Position P) {
    FILE* f;
    char filename[1024];
    Position q, tmp;
    int value;

    printf("\nEnter file name: (list1.txt/list2.txt)\n");
    scanf("%s", filename);

    f = fopen(filename, "r");
    if (f == NULL) {
        printf("\nError\n", filename);
        return -1;
    }

    while (fscanf(f, "%d", &value) == 1) {
        q = (Position)malloc(sizeof(struct _Node));
        if (q == NULL) {
            printf("Error\n");
            return -1;
        }
        q->Element = value;

        tmp = P;
        while (tmp->Next != NULL && tmp->Next->Element > q->Element)
            tmp = tmp->Next;

        q->Next = tmp->Next;
        tmp->Next = q;
    }

    fclose(f);

    return 0;
}

void PrintList(Position P) {
    while (P != NULL) {
        printf(" %d", P->Element);
        P = P->Next;
    }
    printf("\n");
}

int Intersection(Position L1, Position L2, Position P) {
    Position q, tail = P;

    while (L1 != NULL && L2 != NULL) {
        if (L1->Element > L2->Element)
            L1 = L1->Next;
        else if (L1->Element < L2->Element)
            L2 = L2->Next;
        else {
            q = (Position)malloc(sizeof(struct _Node));
            if (q == NULL) {
                printf("Error\n");
                return -1;
            }
            q->Element = L1->Element;
            q->Next = NULL;
            tail->Next = q;
            tail = q;

            L1 = L1->Next;
            L2 = L2->Next;
        } 
    }
    return 0;
}


int Union(Position L1, Position L2, Position U) {
    Position q, tail = U;

    while (L1 != NULL && L2 != NULL) {
        int tmpEl;
        if (L1->Element > L2->Element) {
            tmpEl = L1->Element;
            L1 = L1->Next;
        }
        else if (L1->Element < L2->Element) {
            tmpEl = L2->Element;
            L2 = L2->Next;
        }
        else {
            tmpEl = L1->Element;
            L1 = L1->Next;
            L2 = L2->Next;
        }
        if (tail== U|| tail->Element != tmpEl) {
            q = (Position)malloc(sizeof(struct _Node));
            if (q == NULL) {
                printf("Error\n");
                return -1;
            }
            q->Element = tmpEl;
            q->Next = NULL;
            tail->Next = q;
            tail = q;
        }
    }

    Position tmp;
    if (L1 != NULL)
        tmp = L1;
    else
        tmp = L2;

    while (tmp != NULL) {
        if (tail->Element != tmp->Element) {
            q = (Position)malloc(sizeof(struct _Node));
            if (q == NULL) {
                printf("Error\n");
                return -1;
            }
            q->Element = tmp->Element;
            q->Next = NULL;
            tail->Next = q;
            tail = q;
        
        }
        tmp = tmp->Next;
    }
    return 0;
}
void freeList(Position head) {
    Position tmp;
    while (head != NULL) {
        tmp = head;
        head = head->Next;
        free(tmp);
    }
}
