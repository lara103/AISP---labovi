// labovi 2 v2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>


typedef struct _person {
	char name[16];
	char lastname[16];
	int birthYear;
}person;

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

//3.vjezba
int pushAfter(person, person, nodeptr);
int pushBefore(person, person, nodeptr);
void sortByLastName(nodeptr);
int saveToFile(nodeptr head, const char* filename);
int loadFromFile(nodeptr head, const char* filename);

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
	printf("9 - load from file\n");
	printf("\n");

	char choice = 0;
	person p, q;
	nodeptr n;
	char name[20];

	while (choice != 'x') {
		scanf_s(" %c", &choice);
		switch (choice) {
		case 'x':
			choice = 'x';
			break;
		case '0':
			printf("Insert name, last name and birth year\n");
			scanf_s("%s %s %d", p.name,20, p.lastname,20, &p.birthYear);
			pushFront(&head, p);
			printf("\tList after changes\n");
			print(head.next);
			break;

		case '1':
			printf("Insert name, lastname and birth year\n");
			scanf_s("%s %s %d", p.name,20, p.lastname,20, &p.birthYear);
			pushBack(&head, p);
			printf("\tList after changes\n");
			print(head.next);
			break;

		case '2':
			printf("Insert last name\n");
			scanf_s("%s", p.lastname,20);
			n = findByLastname(head.next, p.lastname);
			if (n != NULL) {
				printf("\tPerson found\n");
				printf("%s %s %d", n->el.name, n->el.lastname, n->el.birthYear);
			}
			else
				printf("Person not found\n");
			break;
		case '3':
			printf("Insert name, lastname and birth year\n");
			scanf_s("%s %s %d", p.name,20, p.lastname,20, &p.birthYear);
			n = findPrev(&head, p);
			if (n != NULL) {
				printf("\tPrevious person;\n");
				printf("%s %s %d", n->el.name, n->el.lastname, n->el.birthYear);
			}
			else
				printf("No previous person found\n");
			break;
		case '4':
			printf("Insert name, lastname and birth year of the person you want to delete\n");
			scanf_s("%s %s %d", p.name,20, p.lastname,20, &p.birthYear);
			deleteEl(&head, p);
			printf("\tList after changes\n");
			print(head.next);
			break;
		case '5':
			printf("Insert name, lastname and birth year of the person you want to push\n");
			scanf_s("%s %s %d", p.name,20, p.lastname,20, &p.birthYear);
			printf("Insert name, lastname and birth year of the person you want to push (%s %s %d) after\n", p.name, p.lastname, p.birthYear);
			scanf_s("%s %s %d", q.name,20, q.lastname,20, &q.birthYear);
			pushAfter(q, p, &head);
			printf("\tList after changes\n");
			print(head.next);
			break;
		case '6':
			printf("Insert name, lastname and birth year of the person you want to push\n");
			scanf_s("%s %s %d", p.name,20, p.lastname,20, &p.birthYear);
			printf("Insert name, lastname and birth year of the person you want to push (%s %s %d) before\n", p.name, p.lastname, p.birthYear);
			scanf_s("%s %s %d", q.name,20, q.lastname,20, &q.birthYear);
			pushBefore(q, p, &head);
			printf("\tList after changes\n");
			print(head.next);
			break;
		case '7':
			sortByLastName(head.next);
			printf("The list is sorted\n");
			printf("\tList after changes\n");
			print(head.next);
			break;
		case '8':
			printf("Insert filename\n");
			scanf_s("%s", name,20);
			saveToFile(&head, name);
			printf("\tSaved\n");
			break;
		case '9':
			printf("Insert filename\n");
			scanf_s("%s", name,20);
			loadFromFile(&head, name);
			break;
		default:
			printf("Error!\n");
		}

	}


	while (head.next != NULL) {
		nodeptr tmp = head.next;
		head.next = tmp->next;
		free(tmp);
	}


}
int pushFront(nodeptr p, person x) {
	nodeptr q;
	q = (nodeptr)malloc(sizeof(node));
	if (q == NULL) {
		printf("Error\n");
		return -1;
	}

	q->el = x;
	q->next = p->next;
	p->next = q;

	return 0;
}
int print(nodeptr p) {
	if (p == NULL) {
		printf("The list is empty\n");
		return -1;
	}

	while (p != NULL) {
		printf("%s %s %d\n", p->el.name, p->el.lastname, p->el.birthYear);
		p = p->next;
	}

}
int pushBack(nodeptr p, person x) {
	while (p->next != NULL)
		p = p->next;

	nodeptr q;
	q = (nodeptr)malloc(sizeof(node));
	if (q == NULL) {
		printf("Error\n");
		return -1;
	}
	q->el = x;
	q->next = p->next;
	p->next = q;

	return 0;
}
nodeptr findByLastname(nodeptr p, const char* x) {
	while (p != NULL) {
		if (strcmp(p->el.lastname, x) == 0)
			return p;
		p = p->next;
	}
	return NULL;

}

nodeptr findPrev(nodeptr p, person x) {
	while (p->next != NULL &&
		!(strcmp(p->next->el.name, x.name) == 0 &&
			strcmp(p->next->el.lastname, x.lastname) == 0 &&
			p->next->el.birthYear == x.birthYear))
		p = p->next;

	if (p->next == NULL) {
		printf("Element dosent exist\n");
		return NULL;
	}
	return p;
}

void deleteEl(nodeptr p, person x) {
	p = findPrev(p, x);
	nodeptr temp;

	if (p != NULL) {
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
}

//3.vjezba
int pushAfter(person x, person y, nodeptr p) {
	nodeptr q = p->next;
	while (q != NULL &&
		!(strcmp(q->el.name, x.name) == 0 &&
			strcmp(q->el.lastname, x.lastname) == 0 &&
			q->el.birthYear == x.birthYear))
	{
		q = q->next;
	}

	if (q == NULL) return -1;

	nodeptr n = (nodeptr)malloc(sizeof(node));
	if (n == NULL) {
		printf("Error\n");
		return -1;
	}
	n->el = y;
	n->next = q->next;
	q->next = n;
	return 0;
}
int pushBefore(person x, person y, nodeptr p) {
	p = findPrev(p, x);
	if (p == NULL)
		return -1;

	nodeptr q = (nodeptr)malloc(sizeof(node));
	if (q == NULL) {
		printf("Error\n");
		return -1;
	}
	q->el = y;
	q->next = p->next;
	p->next = q;
	return 0;
}
void sortByLastName(nodeptr p) {
	if (p == NULL) return;

	int swapped;
	nodeptr a;

	do {
		swapped = 0;
		a = p;

		while (a->next != NULL) {
			if (strcmp(a->el.lastname, a->next->el.lastname) > 0) {
				person temp = a->el;
				a->el = a->next->el;
				a->next->el = temp;
				swapped = 1;
			}
			a = a->next;
		}

	} while (swapped);
}
int saveToFile(nodeptr head, const char* filename) {
	FILE* f = fopen(filename, "w");
	if (!f)
		return 0;

	nodeptr p = head->next;
	while (p != NULL) {
		fprintf(f, "%s %s %d\n",
			p->el.name,
			p->el.lastname,
			p->el.birthYear);
		p = p->next;
	}

	fclose(f);
	return 0;
}
int loadFromFile(nodeptr head, const char* filename) {
	FILE* f = fopen(filename, "r");
	if (!f) return 0;

	nodeptr temp;
	while (head->next != NULL) {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}

	person x;
	while (fscanf(f, "%s %s %d", x.name, x.lastname, &x.birthYear) == 3) {
		pushBack(head, x);
	}
	printf("File data:\n");
	print(head->next);
	fclose(f);
	return 0;
}

