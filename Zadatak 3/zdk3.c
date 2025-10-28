/* Prethodnom zadatku dodati funkcije:
A. dinamièki dodaje novi element iza odreðenog elementa,
B. dinamièki dodaje novi element ispred odreðenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. èita listu iz datoteke.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME     20
#define MAX_SURNAME  30
#define MAX_FILENAME 15
#define ERR_ALLOC	 -1


typedef struct Person* Position;		//pokazivac na strukturu Person
typedef struct Person {					//struktura Person

	char name[MAX_NAME];
	char surname[MAX_SURNAME];
	int birthYear;
	Position next;

}Person;

Position initializeHead();			//kreira "dummy" element kao pocetak liste
int insertAtStart(Position head, char name[MAX_NAME], char surname[MAX_SURNAME], int birthYear);	//dodaje element na pocetak liste
int insertAtEnd(Position head, char name[MAX_NAME], char surname[MAX_SURNAME], int birthYear);		//dodaje element na kraj liste
int printList(Position head);																		//ispisuje listu
Position searchBySurname(Position head, char surname[MAX_SURNAME]);									//po prezimenu trazi element liste
int deleteFromList(Position head, char surname[MAX_SURNAME]);										//brise element liste po prezimenu
int freeAll(Position head);														//prolazi kroz cijelu listu i redom oslobada memoriju

int insertAfter(Position head, char targetSurname[MAX_SURNAME], char name[MAX_NAME], char surname[MAX_SURNAME], int birthYear);  //dodaje element iza odredenog elementa
int insertBefore(Position head, char targetSurname[MAX_SURNAME], char name[MAX_NAME], char surname[MAX_SURNAME], int birthYear); //dodaje element ispred odredenog elementa
int insertToFile(Position head, char fileName[MAX_FILENAME]);					//ispisuje listu u datoteku
int readFromFile(Position head, char fileName[MAX_FILENAME]);					//cita listu iz datoteke
int sortList(Position head);													//sortira listu

int main() {

	Position head = initializeHead();							  //kreira glavu
	if (!head)
		return ERR_ALLOC;										  //vraca error ako se ne moze alocirati
	insertAtStart(head, "Ante", "Lisica", 2005);                  //unosimo vrijednosti prvog elementa u nizu
	insertAtStart(head, "Branko", "Bulj", 1956);
	insertAtStart(head, "Grgo", "Hrabar", 1977);
	insertAtEnd(head, "Domagoj", "Duvnjak", 1985);                //unosimo vrijednosti zadnjeg elementa u nizu
	printList(head);

	deleteFromList(head, "Lisica");                               //brisemo element kojeg ima u listu i gledamo ispis
	printf("\n");
	printList(head);

	insertAfter(head, "Hrabar", "Zeljko", "Kerum", 1965);		  //unosimo element iza odredenog elementa
	insertBefore(head, "Bulj", "Tomislav", "Tolj", 1999);		  //unosimo element ispred odredenog elementa
	printf("\n");
	printList(head);

	insertToFile(head, "lista.txt");							  //zapisuje listu u datoteku
	freeAll(head);												  //oslobada memoriju liste
	readFromFile(head, "lista.txt");                              //cita listu iz datoteke natrag u program
	sortList(head);												  //sortira listu po prezimenima
	printf("\n");
	printList(head);
	freeAll(head);

	return 0;
}

Position initializeHead() {

	Position P = (Position)malloc(sizeof(Person));              //dinamicki alocira memoriju za glavu liste
	if (P == NULL) {
		printf("Greska pri alokaciji memorije!");
		return NULL;
	}

	P->name[0] = '\0';										//unosimo "prazne" vrijednosti na head
	P->surname[0] = '\0';
	P->birthYear = 0;
	P->next = NULL;

	return P;
}

int insertAtStart(Position head, char name[MAX_NAME], char surname[MAX_SURNAME], int birthYear) {

	Position new = (Position)malloc(sizeof(Person));           //alocira memoriju za novu osobu
	if (new == NULL) {
		printf("Greska pri alokaciji memorije!");
		return ERR_ALLOC;
	}

	strcpy(new->name, name);                               //kopira ime u novi cvor
	strcpy(new->surname, surname);						   //kopira prezime u novi cvor
	new->birthYear = birthYear;							   //postavlja godinu rodenja
	new->next = head->next;                                //novi pokazuje na trenutni prvi element
	head->next = new;                                      //glava pokazuje na novi element

	return 0;
}

int insertAtEnd(Position head, char name[MAX_NAME], char surname[MAX_SURNAME], int birthYear) {

	Position new = (Position)malloc(sizeof(Person));
	if (new == NULL) {
		printf("Greska pri alokaciji memorije!");
		return ERR_ALLOC;
	}

	strcpy(new->name, name);
	strcpy(new->surname, surname);
	new->birthYear = birthYear;
	new->next = NULL;                                         //novi pokazuje na kraj (NULL)
	Position q = head;
	while (q->next != NULL)                                   //vrti petlju dok ne dode do zadnjeg elementa koji pokazuje na kraj
		q = q->next;
	q->next = new;                                            //zadnji element sad pokazuje na novi

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
	Position q = head;                                              //pomocni pokazivac krece od heada
	while (q->next != deleteP)                                      //petlja se vrti dok ne dode do prethodnika cvora koji se brise
		q = q->next;
	q->next = deleteP->next;                                        //preskace obrisan cvor
	deleteP->next = NULL;                                           //odvezuje obrisani cvor iz liste
	free(deleteP);	                                              //oslobada memoriju obrisanog cvora
	
	return 0;

}

int freeAll(Position head) {

	Position q = head->next;                                    //pomocni pokazivac koji pokazuje na prvi stvarni element
	while (q != NULL) {                                         //prolazi kroz listu dok ne doðe do kraja 
		Position new = q->next;									//sprema adresu sljedeceg cvora prije nego sto oslobodi trenutni
		free(q);                                                //oslobada trenutni cvor
		q = new;												//prelazi na slijedeci cvor
	}
	head->next = NULL;
	return 0;
}

int insertAfter(Position head, char targetSurname[MAX_SURNAME], char name[MAX_NAME], char surname[MAX_SURNAME], int birthYear) {

	Position new = (Position)malloc(sizeof(Person));				//alocira novi element
	if (new == NULL) {
		printf("Greska pri alokaciji memorije!");
		return ERR_ALLOC;
	}

	Position q = searchBySurname(head, targetSurname);				//q je element iza kojeg umecemo
	strcpy(new->name, name);
	strcpy(new->surname, surname);
	new->birthYear = birthYear;						
	new->next = q->next;									//novi pokazuje na sljedeci cvor
	q->next = new;											//ciljani element pokazuje na novi cvor
	return 0;
}

int insertBefore(Position head, char targetSurname[MAX_SURNAME], char name[MAX_NAME], char surname[MAX_SURNAME], int birthYear) {

	Position new = (Position)malloc(sizeof(Person));			
	if (new == NULL) {
		printf("Greska pri alokaciji memorije!");
		return ERR_ALLOC;
	}

	Position q = searchBySurname(head, targetSurname);					//q je element ispred kojeg umecemo
	Position p = head;													//p je pomocni pokazivac koji krece od heada
	strcpy(new->name, name);
	strcpy(new->surname, surname);
	new->birthYear = birthYear;
	while (p->next != q)											 //petlja se vrti dok ne dode do prethodnog elementa od q
		p = p->next;
	new->next = p->next;											//novi sad pokazuje na ciljani
	p->next = new;													//prethodni pokazuje na novi

	return 0;
}

int insertToFile(Position head, char fileName[MAX_FILENAME]) {

	FILE* f = fopen(fileName, "w");											//otvara datoteku za pisanje
	if (!f) {
		printf("Greska pri otvaranju!");
		return -1;
	}
	Position q = head->next;
	while (q != NULL) {															//prolazi cijelu listu i upisuje u datoteku
		fprintf(f, "%s %s %d\n", q->name, q->surname, q->birthYear);
		q = q->next;
	}
	fclose(f);															//zatvara datoteku
	return 0;
}

int readFromFile(Position head, char fileName[MAX_FILENAME]) {

	FILE* f = fopen(fileName, "r");
	if (!f) {
		printf("Greska pri otvaranju!");
		return -1;
	}
	char fname[MAX_NAME] = { 0 };
	char lname[MAX_SURNAME] = { 0 };
	int year = 0;

	while (!feof(f))
	{
		if (fscanf(f, "%s %s %d", fname, lname, &year) != 3)					//cita dok ima valjanih linija
			break;                  

		int err = insertAtEnd(head, fname, lname, year);						//dodaje osobe na kraj liste
		if (err == ERR_ALLOC) {
			fclose(f);
			return ERR_ALLOC;       
		}
	}
	fclose(f);
	return 0;
}

int sortList(Position head) {

	int swapped = 1;										//pokazuje je li bilo zamjena
	Position end = NULL;									//granica do koje vise ne treba prolaziti

	while (swapped) {
		swapped = 0;
		Position prev = head;
		Position cur = head->next;
			
		while (cur->next != end) {									//prolazi do zadnjeg nesortiranog
			Position nxt = cur->next;

			if (strcmp(cur->surname, nxt->surname) > 0) {			//usporeduje prezimena
				prev->next = nxt;
				cur->next = nxt->next;
				nxt->next = cur;
				prev = nxt;
				swapped = 1;										//oznacava je li bila zamjena
			}	
			else {
				prev = cur;
				cur = nxt;
			}
		}
		end = cur;												//zadnji element se vise ne dira
	}
	return 0;
}