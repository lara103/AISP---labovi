#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _person {
    char name[16];
    char lastname[16];
    int birthYear;
} person;

typedef struct node* nodeptr;
struct node {
    person el;
    nodeptr next;
};

int pushFront(nodeptr, person);
int print(nodeptr);
int pushBack(nodeptr, person);
nodeptr findByLastname(nodeptr, const char*);
nodeptr findPrev(nodeptr, person);
void deleteEl(nodeptr, person);

int pushAfter(person, person, nodeptr);
int pushBefore(person, person, nodeptr);
void sortByLastName(nodeptr);
int saveToFile(nodeptr head, const char* filename);
int loadFromFile(nodeptr head, const char* filename);

void clearList(nodeptr head);

int main()
{
    struct node head;
    head.next = NULL;

    printf("\n\t ~Menu~ \t\n");
    printf("x - end program\n");
    printf("0 - push front\n");
    printf("1 - push back\n");
    printf("2 - find by last name\n");
    printf("3 - find previous\n");
    printf("4 - delete element\n");
    printf("5 - push after\n");
    printf("6 - push before\n");
    printf("7 - sort by last name\n");
    printf("8 - save to file\n");
    printf("9 - load from file\n\n");

    char choice = 0;
    person p, q;
    nodeptr n;
    char name[20];

    while (choice != 'x') {
        scanf_s(" %c", &choice, 1);

        switch (choice) {

        case 'x':
            clearList(&head);
            return 0;

        case '0':
            scanf_s("%s %s %d", p.name, 16, p.lastname, 16, &p.birthYear);
            if (pushFront(&head, p) == -1)
                printf("Error\n");
            print(head.next);
            break;

        case '1':
            scanf_s("%s %s %d", p.name, 16, p.lastname, 16, &p.birthYear);
            if (pushBack(&head, p) == -1)
                printf("Error\n");
            print(head.next);
            break;

        case '2':
            scanf_s("%s", p.lastname, 16);
            n = findByLastname(head.next, p.lastname);
            if (n)
                printf("%s %s %d\n", n->el.name, n->el.lastname, n->el.birthYear);
            else
                printf("Person not found\n");
            break;

        case '3':
            scanf_s("%s %s %d", p.name, 16, p.lastname, 16, &p.birthYear);
            n = findPrev(&head, p);
            if (n)
                printf("%s %s %d\n", n->el.name, n->el.lastname, n->el.birthYear);
            else
                printf("No previous person found\n");
            break;

        case '4':
            scanf_s("%s %s %d", p.name, 16, p.lastname, 16, &p.birthYear);
            deleteEl(&head, p);
            print(head.next);
            break;

        case '5':
            scanf_s("%s %s %d", p.name, 16, p.lastname, 16, &p.birthYear);
            scanf_s("%s %s %d", q.name, 16, q.lastname, 16, &q.birthYear);
            if (pushAfter(q, p, &head) == -1)
                printf("Error\n");
            print(head.next);
            break;

        case '6':
            scanf_s("%s %s %d", p.name, 16, p.lastname, 16, &p.birthYear);
            scanf_s("%s %s %d", q.name, 16, q.lastname, 16, &q.birthYear);
            if (pushBefore(q, p, &head) == -1)
                printf("Error\n");
            print(head.next);
            break;

        case '7':
            sortByLastName(head.next);
            print(head.next);
            break;

        case '8':
            scanf_s("%s", name, 20);
            if (saveToFile(&head, name) == -1)
                printf("File error\n");
            break;

        case '9':
            scanf_s("%s", name, 20);
            if (loadFromFile(&head, name) == -1)
                printf("File error\n");
            break;

        default:
            printf("Error!\n");
        }
    }

    clearList(&head);
    return 0;
}

void clearList(nodeptr head) {
    nodeptr tmp;
    while (head->next) {
        tmp = head->next;
        head->next = tmp->next;
        free(tmp);
    }
}

int pushFront(nodeptr p, person x) {
    nodeptr q = malloc(sizeof(struct node));
    if (!q) return -1;
    q->el = x;
    q->next = p->next;
    p->next = q;
    return 0;
}

int print(nodeptr p) {
    if (!p) {
        printf("The list is empty\n");
        return -1;
    }
    while (p) {
        printf("%s %s %d\n", p->el.name, p->el.lastname, p->el.birthYear);
        p = p->next;
    }
    return 0;
}

int pushBack(nodeptr p, person x) {
    while (p->next) p = p->next;
    nodeptr q = malloc(sizeof(struct node));
    if (!q) return -1;
    q->el = x;
    q->next = NULL;
    p->next = q;
    return 0;
}

nodeptr findByLastname(nodeptr p, const char* x) {
    while (p) {
        if (!strcmp(p->el.lastname, x))
            return p;
        p = p->next;
    }
    return NULL;
}

nodeptr findPrev(nodeptr p, person x) {
    while (p->next &&
        !(strcmp(p->next->el.name, x.name) == 0 &&
            strcmp(p->next->el.lastname, x.lastname) == 0 &&
            p->next->el.birthYear == x.birthYear))
        p = p->next;

    return p->next ? p : NULL;
}

void deleteEl(nodeptr p, person x) {
    nodeptr prev = findPrev(p, x);
    if (prev) {
        nodeptr tmp = prev->next;
        prev->next = tmp->next;
        free(tmp);
    }
}

int loadFromFile(nodeptr head, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return -1;

    clearList(head);

    person x;
    while (fscanf(f, "%s %s %d", x.name, x.lastname, &x.birthYear) == 3) {
        if (pushBack(head, x) == -1) {
            fclose(f);
            clearList(head);
            return -1;
        }
    }

    fclose(f);
    print(head->next);
    return 0;
}
