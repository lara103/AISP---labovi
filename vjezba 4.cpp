//Napisati program za zbrajanje i množenje polinoma.Koeficijenti i eksponenti se čitaju iz datoteke.
//Napomena: Eksponenti u datoteci nisu nužno sortirani

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>


typedef struct term* termPtr;
 struct term {
	int coef;
	int exp;
	termPtr next;
};

int insertSorted(termPtr, int, int);
int printPolynomial(termPtr );
int readPolynomial(char[], termPtr);
termPtr addPolynomials(termPtr, termPtr);
termPtr multiplyPolynomials(termPtr, termPtr);
void freePolynomial(termPtr);

int main()
{
	FILE* fp1 = fopen("poly1.txt", "r");
	FILE* fp2 = fopen("poly2.txt", "r");
	if (!fp1 || !fp2) {
		printf("Error opening files\n");
		return -1;
	}
	char[20] f1;
	char[20] f2;
	printf("Insert file name\n");
	scanf("%s", f1);
	printf("Insert file name\n");
	scanf("%s", f2);


	struct term head1 = { 0, 0, NULL };
	struct term head2 = { 0, 0, NULL };

	readPolynomial(f1, &head1);
	readPolynomial(f2, &head2);

	fclose(fp1);
	fclose(fp2);

	printf("Polynomial 1:\n");
	printPolynomial(head1.next);

	printf("Polynomial 2:\n");
	printPolynomial(head2.next);

	termPtr sum = addPolynomials(head1.next, head2.next);
	printf("Sum:\n");
	printPolynomial(sum);

	termPtr product = multiplyPolynomials(head1.next, head2.next);
	printf("Product:\n");
	printPolynomial(product);


	freePolynomial(head1.next);
	freePolynomial(head2.next);
	freePolynomial(sum);
	freePolynomial(product);

}
int insertSorted(termPtr head, int coef, int exp) {
	if (coef == 0)
		return -1;

	termPtr p = head;
	while (p->next != NULL && p->next->exp > exp)
		p = p->next;

	if (p->next != NULL && p->next->exp == exp) {
		p->next->coef += coef;

		if (p->next->coef == 0) {
			termPtr del = p->next;
			p->next = del->next;
			free(del);
		}
		return 1;
	}
	termPtr newTerm = (termPtr)malloc(sizeof(term));
	if (newTerm == NULL) {
		printf("Error\n");
		return -1;
	}
	newTerm->coef = coef;
	newTerm->exp = exp;
	newTerm->next = p->next;
	p->next = newTerm;

}
int printPolynomial(termPtr head) {
	termPtr p = head;

	if (p == NULL) {
		printf("empty\n");
		return -1;
	}

	while (p != NULL) {
		printf("%d", p->coef);
		if (p->exp != 0)
			printf("x^%d", p->exp);
		if (p->next != NULL)
			printf(" + ");
		p = p->next;
	}
	printf("\n");
}
int readPolynomial(char[] f, termPtr head) {
	
	int coef, exp;
	FILE* fp = fopen(f, "r");
	if (fp == NULL) {
		printf("Error\n");
		return -1;
	}
	while (fscanf(fp, "%d %d", &coef, &exp) == 2) {
		insertSorted(head, coef, exp);
	}
	return 0;
}
termPtr addPolynomials(termPtr head1, termPtr head2) {
	struct term resultHead = { 0, 0, NULL };
	termPtr res = &resultHead;

	termPtr p = head1;
	while (p != NULL) {
		insertSorted(res, p->coef, p->exp);
		p = p->next;
	}

	p = head2;
	while (p != NULL) {
		insertSorted(res, p->coef, p->exp);
		p = p->next;
	}

	return resultHead.next;
}
termPtr multiplyPolynomials(termPtr head1, termPtr head2) {
	struct term resultHead = { 0, 0, NULL };
	termPtr res = &resultHead;

	for (termPtr p1 = head1; p1 != NULL; p1 = p1->next) {
		for (termPtr p2 = head2; p2 != NULL; p2 = p2->next) {
			int coef = p1->coef * p2->coef;
			int exp = p1->exp + p2->exp;
			insertSorted(res, coef, exp);
		}
	}

	return resultHead.next;
}
void freePolynomial(termPtr head) {
	termPtr p = head;
	while (p != NULL) {
		termPtr tmp = p;
		p = p->next;
		free(tmp);
	}
}
