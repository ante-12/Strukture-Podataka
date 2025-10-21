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
#define ERR_ALLOC -1


typedef struct Person* Position;		//pokazivac na strukturu Person
typedef struct Person {					//struktura Person

	char name[MAX_NAME];
	char surname[MAX_SURNAME];
	int birthYear;
	Position next;

}Person;

Position initializeHead();			//kreira "dummy" element kao pocetak liste
int insertAtStart(Position head, char name[MAX_NAME], char surname[MAX_SURNAME], int birthYear);	//dodaje element na pocetak liste
int insertAtEnd(Position head,char name[MAX_NAME], char surname[MAX_SURNAME], int birthYear);		//dodaje element na kraj liste
int printList(Position head);																		//ispisuje listu
Position searchBySurname(Position head, char surname[MAX_SURNAME]);									//po prezimenu trazi element liste
int deleteFromList(Position head, char surname[MAX_SURNAME]);										//brise element liste po prezimenu
int freeAll(Position head);														//prolazi kroz cijelu listu i redom oslobada memoriju

int main() {

	Position head = initializeHead();							  //kreira glavu
	if (!head)
		return ERR_ALLOC;										  //vraca error ako se ne moze alocirati
	insertAtStart(head, "Ante", "Lisica", 2005);                  //unosimo vrijednosti prvog elementa u nizu
	insertAtStart(head, "Branko", "Bulj", 1956);
	insertAtStart(head, "Grgo", "Hrabar", 1977);
	insertAtStart(head, "Miro", "Matas", 2010);
	insertAtEnd(head, "Domagoj", "Duvnjak", 1985);                //unosimo vrijednosti zadnjeg elementa u nizu
	printList(head);
	deleteFromList(head, "Lisica");                               //brisemo element kojeg ima u listu i gledamo ispis
	printf("\n");
	printList(head);
	printf("\n");
	deleteFromList(head, "Mamic");                                //brisemo element kojeg nema u listu i gledamo ispis
	freeAll(head);													

	return 0;
}

Position initializeHead() {

	Position P = (Position)malloc(sizeof(Person));              //dinamicki alocira memoriju za glavu liste
	if (P == NULL) {
		printf("Greska pri alokaciji memorije!");
		return NULL;
	}
	else {

		P->name[0] = '\0';										//unosimo "prazne" vrijednosti na head
		P->surname[0] = '\0';
		P->birthYear = 0;
		P->next = NULL;
	}
	return P;
}

int insertAtStart(Position head, char name[MAX_NAME], char surname[MAX_SURNAME], int birthYear) {

	Position new = (Position)malloc(sizeof(Person));           //alocira memoriju za novu osobu
	if (new == NULL) {
		printf("Greska pri alokaciji memorije!");
		return ERR_ALLOC;
	}
	else {

		strcpy(new->name, name);                               //kopira ime u novi cvor
		strcpy(new->surname, surname);						   //kopira prezime u novi cvor
		new->birthYear = birthYear;							   //postavlja godinu rodenja
		new->next = head->next;                                //novi pokazuje na trenutni prvi element
		head->next = new;                                      //glava pokazuje na novi element

	}
	return 0;
}

int insertAtEnd(Position head, char name[MAX_NAME], char surname[MAX_SURNAME], int birthYear) {

	Position new = (Position)malloc(sizeof(Person));
	if (new == NULL) {
		printf("Greska pri alokaciji memorije!");
		return ERR_ALLOC;
	}
	else {

		strcpy(new->name, name);
		strcpy(new->surname, surname);
		new->birthYear = birthYear;
		new->next = NULL;                                         //novi pokazuje na kraj (NULL)
		Position q = head;                                      
		while (q->next != NULL)                                   //vrti petlju dok ne dode do zadnjeg elementa koji pokazuje na kraj
			q = q->next;                                          
		q->next = new;                                            //zadnji element sad pokazuje na novi

	}

	return 0;
}

int printList(Position head) {

	Position q = head->next;                                                  //pocinje od prvog stvarnog elementa(nakon head)
	while (q != NULL) {                                                       //vrti petlju dok ne dode do kraja
		printf("[%s , %s , %d] -> ", q->name, q->surname, q->birthYear);      
		q = q->next;
	}
	if (!q)
		printf("NULL");													      //kad prode svaki element, printa NULL

	return 0;
}

Position searchBySurname(Position head, char surname[MAX_SURNAME]) {

	Position foundP = head->next;                                        //pocinje od prvog stvarnog elementa
	while (foundP != NULL && strcmp(foundP->surname, surname))			 //ide dok ne nade podudaranje prezimena ili dok ne dode do kraja
		foundP = foundP->next;
	if (foundP == NULL)												     //ako nije pronaden, vraca NULL
		return NULL;
	else
		return foundP;                                                   //inace vraca adresu pronadenog cvora 
	
}

int deleteFromList(Position head, char surname[MAX_SURNAME]) {

	Position deleteP = searchBySurname(head, surname);                   //preko searchBySurname trazimo cvor koji zelimo obrisati
	if (deleteP == NULL) {												 //ako ne postoji osoba, ispisuje ...
		printf("Ne postoji ta osoba!");
		return 1;
	}
	else {

		Position q = head;                                              //pomocni pokazivac krece od heada
		while (q->next != deleteP)                                      //petlja se vrti dok ne dode do prethodnika cvora koji se brise
			q = q->next;
		q->next = deleteP->next;                                        //preskace obrisan cvor
		deleteP->next = NULL;                                           //odvezuje obrisani cvor iz liste
		free(deleteP);	                                                //oslobada memoriju obrisanog cvora
		return 0;
	}
}

int freeAll(Position head) {                                     
	
	Position q = head->next;                                    //pomocni pokazivac koji pokazuje na prvi stvarni element
	while (q != NULL) {                                         //prolazi kroz listu dok ne doðe do kraja 
		Position new = q->next;									//sprema adresu sljedeceg cvora prije nego sto oslobodi trenutni
		free(q);                                                //oslobada trenutni cvor
		q = new;												//prelazi na slijedeci cvor
	}
	return 0;
}



