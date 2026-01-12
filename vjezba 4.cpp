#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct term* termPtr;
struct term {
    int coef;
    int exp;
    termPtr next;
};

int insertSorted(termPtr, int, int);
int printPolynomial(termPtr);
int readPolynomial(char[], termPtr);
termPtr addPolynomials(termPtr, termPtr);
termPtr multiplyPolynomials(termPtr, termPtr);
void freePolynomial(termPtr);
void freeAll(termPtr, termPtr, termPtr, termPtr);

int main()
{
    char f1[20], f2[20];

    printf("Insert file name\n");
    scanf("%s", f1);
    printf("Insert file name\n");
    scanf("%s", f2);

    struct term head1 = { 0, 0, NULL };
    struct term head2 = { 0, 0, NULL };

    if (readPolynomial(f1, &head1) == -1) {
        printf("Error\n");
        freeAll(head1.next, head2.next, NULL, NULL);
        return -1;
    }

    if (readPolynomial(f2, &head2) == -1) {
        printf("Error\n");
        freeAll(head1.next, head2.next, NULL, NULL);
        return -1;
    }

    printf("Polynomial 1:\n");
    if (printPolynomial(head1.next) == -1) {
        freeAll(head1.next, head2.next, NULL, NULL);
        return -1;
    }

    printf("Polynomial 2:\n");
    if (printPolynomial(head2.next) == -1) {
        freeAll(head1.next, head2.next, NULL, NULL);
        return -1;
    }

    termPtr sum = addPolynomials(head1.next, head2.next);
    if (!sum) {
        freeAll(head1.next, head2.next, NULL, NULL);
        return -1;
    }

    printf("Sum:\n");
    if (printPolynomial(sum) == -1) {
        freeAll(head1.next, head2.next, sum, NULL);
        return -1;
    }

    termPtr product = multiplyPolynomials(head1.next, head2.next);
    if (!product) {
        freeAll(head1.next, head2.next, sum, NULL);
        return -1;
    }

    printf("Product:\n");
    if (printPolynomial(product) == -1) {
        freeAll(head1.next, head2.next, sum, product);
        return -1;
    }

    freeAll(head1.next, head2.next, sum, product);
    return 0;
}


void freeAll(termPtr p1, termPtr p2, termPtr p3, termPtr p4) {
    freePolynomial(p1);
    freePolynomial(p2);
    freePolynomial(p3);
    freePolynomial(p4);
}



int insertSorted(termPtr head, int coef, int exp) {
    if (coef == 0)
        return 0;

    termPtr p = head;
    while (p->next && p->next->exp > exp)
        p = p->next;

    if (p->next && p->next->exp == exp) {
        p->next->coef += coef;
        if (p->next->coef == 0) {
            termPtr del = p->next;
            p->next = del->next;
            free(del);
        }
        return 0;
    }

    termPtr newTerm = malloc(sizeof(term));
    if (!newTerm)
        return -1;

    newTerm->coef = coef;
    newTerm->exp = exp;
    newTerm->next = p->next;
    p->next = newTerm;

    return 0;
}

int printPolynomial(termPtr head) {
    if (!head) {
        printf("empty\n");
        return -1;
    }

    while (head) {
        printf("%d", head->coef);
        if (head->exp != 0)
            printf("x^%d", head->exp);
        if (head->next)
            printf(" + ");
        head = head->next;
    }
    printf("\n");
    return 0;
}

int readPolynomial(char f[], termPtr head) {
    FILE* fp = fopen(f, "r");
    if (!fp)
        return -1;

    int coef, exp;
    while (fscanf(fp, "%d %d", &coef, &exp) == 2) {
        if (insertSorted(head, coef, exp) == -1) {
            fclose(fp);
            printf("Memory error\n");
            return -1;
        }
    }

    fclose(fp);
    return 0;
}

termPtr addPolynomials(termPtr head1, termPtr head2) {
    struct term resultHead = { 0, 0, NULL };
    termPtr res = &resultHead;

    for (termPtr p = head1; p; p = p->next)
        if (insertSorted(res, p->coef, p->exp) == -1)
            return NULL;

    for (termPtr p = head2; p; p = p->next)
        if (insertSorted(res, p->coef, p->exp) == -1) {
            freePolynomial(resultHead.next);
            return NULL;
        }

    return resultHead.next;
}

termPtr multiplyPolynomials(termPtr head1, termPtr head2) {
    struct term resultHead = { 0, 0, NULL };
    termPtr res = &resultHead;

    for (termPtr p1 = head1; p1; p1 = p1->next)
        for (termPtr p2 = head2; p2; p2 = p2->next)
            if (insertSorted(res,
                p1->coef * p2->coef,
                p1->exp + p2->exp) == -1) {
                freePolynomial(resultHead.next);
                return NULL;
            }

    return resultHead.next;
}

void freePolynomial(termPtr head) {
    while (head) {
        termPtr tmp = head;
        head = head->next;
        free(tmp);
    }
}
