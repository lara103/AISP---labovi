//Definirati strukturu osoba(ime, prezime, godina rođenja) i napisati program koji :
//a) dinamički dodaje novi element na početak liste,
//b) ispisuje listu,
//c) dinamički dodaje novi element na kraj liste,
//d) pronalazi element u listi(po prezimenu),
//e) briše određeni element iz liste.
//U zadatku se ne smiju koristiti globalne varijable

//3. Prethodnom zadatku dodati funkcije :
//a) dinamički dodaje novi element iza određenog elementa,
//b) dinamički dodaje novi element ispred određenog elementa,
//c) sortira listu po prezimenima osoba,
//d) upisuje listu u datoteku,
//e) čita listu iz datoteke
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

void pushFront(nodeptr, person);
void print(nodeptr);
void pushBack(nodeptr, person);
nodeptr findByLastname(nodeptr,const char*);
nodeptr findPrev(nodeptr, person);
void deleteEl(nodeptr, person);

//3.vjezba
void pushAfter(person, person, nodeptr);
void pushBefore(person, person, nodeptr);
void sortByLastName(nodeptr);
int saveToFile(nodeptr head, const char* filename);
int loadFromFile(nodeptr head, const char* filename);

int main()
{
	struct node head;
	head.next = NULL;

	person p1 = { "Marko", "Markovic", 1990 };
	person p2 = { "Ana", "Anic", 2005 };
	person p3 = { "Ivan", "Ivic", 2000 };
	person p4 = { "Lana", "Lanic", 2007 };
	person p5 = { "Maja", "Maric", 1999 };

	pushFront(&head, p1);
	pushFront(&head, p2);
	printf("\nList after pushFront:\n");
	print(head.next);

	pushBack(&head, p3);
	printf("\nList after pushBack:\n");
	print(head.next);

	nodeptr src = findByLastname(head.next, "Markovic");
	if (src != NULL)
		printf("\nFound: %s %s %d\n",
			src->el.name, src->el.lastname, src->el.birthYear);
	else
		printf("Person not found\n");

	deleteEl(&head, p2);
	printf("\nList after deleting:\n");
	print(head.next);
	
	//3.vjezba
	printf("\nList after push after(%s %s %d):\n", p1.name,p1.lastname,p1.birthYear);
	pushAfter(p1, p4, &head);
	print(head.next);

	printf("\nList after push before(%s %s %d):\n", p1.name, p1.lastname, p1.birthYear);
	pushBefore(p1, p5, &head);
	print(head.next);

	printf("\nList before sorting:\n");
	print(head.next);

	printf("\nList after sorting\n");
	sortByLastName(head.next);
	print(head.next);

	const char* filename = "people";
	if (saveToFile(&head, filename))
		printf("\nSaved list to file\n");
	else
		printf("\tError saving to file\n");

	//******
	while (head.next != NULL) {
		nodeptr tmp = head.next;
		head.next = tmp->next;
		free(tmp);
	} 

	if (loadFromFile(&head, filename))
		printf("\nLoaded list from file\n");
	else
		printf("\tError loading from file\n");

	printf("\nList after loading from file\n");
	print(head.next);

	while (head.next != NULL) {
		nodeptr tmp = head.next;
		head.next = tmp->next;
		free(tmp);
	}
 
	
}
void pushFront(nodeptr p, person x){
	nodeptr q;
	q = (nodeptr)malloc(sizeof(node));

	q->el = x;
	q->next = p->next;
	p->next = q;
}
void print(nodeptr p) {
	if (p == NULL) {
		printf("The list is empty");
	}

	while (p != NULL) {
		printf("%s %s %d\n", p->el.name, p->el.lastname, p->el.birthYear);
		p = p->next;
	}

}
void pushBack(nodeptr p, person x) { 
	while (p->next != NULL)
		p = p->next;

	nodeptr q;
	q = (nodeptr)malloc(sizeof(node));
	q->el = x;
	q->next = p->next;
	p->next = q;
	

}
nodeptr findByLastname(nodeptr p, const char* x) {
	while (p != NULL) {
		if(strcmp(p->el.lastname, x) == 0 ) 
			return p;
	p = p->next;
	}
	return NULL;

}

nodeptr findPrev(nodeptr p, person x) {
	while (p->next!=NULL &&
		!(strcmp(p->next->el.name, x.name) == 0 &&
		strcmp(p->next->el.lastname, x.lastname) == 0 &&
		p->next->el.birthYear == x.birthYear))
		p = p->next;

	if (p->next == NULL) {
		printf("Element dosent exist");
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
void pushAfter(person x, person y, nodeptr p) {
	nodeptr q = p->next;
	while (q != NULL &&
		!(strcmp(q->el.name, x.name) == 0 &&
			strcmp(q->el.lastname, x.lastname) == 0 &&
			q->el.birthYear == x.birthYear))
	{
		q = q->next;
	}

	if (q == NULL) return;

	nodeptr n = (nodeptr)malloc(sizeof(node));
	n->el = y;
	n->next = q->next;
	q->next = n;

}
void pushBefore(person x, person y, nodeptr p) {
	p = findPrev(p, x);
	if (p == NULL)
		return;

	nodeptr q = (nodeptr)malloc(sizeof(node));
	q->el = y;
	q->next = p->next;
	p->next = q;

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
	return 1;
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

	fclose(f);
	return 1;
}


