/*Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
A. dinamièki dodaje novi element na poèetak liste,
B. ispisuje listu,
C. dinamièki dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME    20
#define MAX_SURNAME 30
#define ERR_ALLOC   -1


typedef struct Person* Position;
typedef struct Person {

	char name[MAX_NAME];
	char surname[MAX_SURNAME];
	int birthYear;
	Position next;

}Person;

Position initializeHead();
int insertAtStart(Position head, char name[MAX_NAME], char surname[MAX_SURNAME], int birthYear);
int printList(Position head);

int main() {

	Position head = initializeHead();
	insertAtStart(head, "Ante", "Lisica", 2005);
	insertAtStart(head, "Branko", "Bulj", 1956);
	insertAtStart(head, "Grgo", "Hrabar", 1977);
	insertAtStart(head, "Miro", "Matas", 2010);
	printList(head);


	return 0;
}

Position initializeHead() {

	Position P = (Position)malloc(sizeof(Person));
	if (P == NULL) {
		printf("Greska pri alokaciji memorije!");
		return ERR_ALLOC;
	}
	else {

		P->name[0] = '\0';
		P->surname[0] = '\0';
		P->birthYear = 0;
		P->next = NULL;
	}
	return P;
}

int insertAtStart(Position head, char name[MAX_NAME], char surname[MAX_SURNAME], int birthYear) {

	Position new = (Position)malloc(sizeof(Person));
	if (new == NULL) {
		printf("Greska pri alokaciji memorije!");
		return ERR_ALLOC;
	}
	else {

		strcpy(new->name, name);
		strcpy(new->surname, surname);
		new->birthYear = birthYear;
		new->next = head->next;
		head->next = new;

	}
	return 0;
}

int printList(Position head) {

	Position q = head;
	while (q != NULL) {
		printf("[%s , %s , %d] -> ", q->name, q->surname, q->birthYear);
		q = q->next;
	}
	if (!q)
		printf("[prazna lista]");

	return 0;
}
