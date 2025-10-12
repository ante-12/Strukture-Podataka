/*Napisati program koji prvo proèita koliko redakaima datoteka, tj. koliko ima studena
zapisanih u datoteci. Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 50
#include <stdio.h>
#include <stdlib.h>

typedef struct _student {                                                   //struktura studenta sa imenom, prezimenom i brojem bodova

	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int score;

}Student;

int studentCounter(FILE*);                                                //funkcija za procitati broj redaka u tekstualnoj datoteci

Student* loadStudents(FILE*, int);										   //funkcija za dinamicku alokaciju prostora za niz struktura studenata

int userInterface(Student*, int);										   //funckija za isprintati na ekranu podatke studenata 

int main() {

	FILE* txtFile = fopen("students.txt", "r");                            //otvara txt datoteku i cita iz nje
	int i = studentCounter(txtFile);									   //vrijednosti i se dodijeljuje broj redaka
	Student* s = loadStudents(txtFile, i);								   //dohvacam podatke o studentima
	userInterface(s, i);                                                    //poziva se navedena funkcija
	fclose(txtFile);                                                       //zatvaramo datoteku

	return 0;
}

int studentCounter(FILE* txtF) {

	txtF = fopen("students.txt", "r");
	if (txtF == NULL) {

		printf("Greška pri otvaranju!");                                    //salje grešku ako se ne moze otvoriti txt datoteka
		return -1;
	}

	int counter = 0;
	char buffer[MAX_LENGTH];

	while (fgets(buffer, sizeof(buffer), txtF) != NULL) {                //funkcija fgets broji retke u txt datoteci, time i broj studenata

		counter++;
	}

	rewind(txtF);                                                         //vraca se na pocetak datoteke    
	fclose(txtF);
	return counter;
}

Student* loadStudents(FILE* txtFile, int numberOfStudents) {

	Student* students = (Student*)malloc(sizeof(Student) * numberOfStudents);            //dinamicka alokacija memorije u koje su pohranjuju podatci o studentima

	if (students == NULL) {

		printf("Greška pri alokaciji memorije!");                                          //salje gresku ako se ne uspije alocirati memorija
		return NULL;
	}

	for (int i = 0; i < numberOfStudents; i++) {

		fscanf(txtFile, "%s %s %d", students[i].name, students[i].surname, &students[i].score);            //cita podatke studenata iz txt datoteke
	}

	return students;                                                 //vraca podatke o studentima
}

int userInterface(Student* s, int size) {

	int max = s[0].score;
	for (int i = 0; i < size; i++) {                                       //for petlja za izracunati maksimalan broj bodova izmeðu studenata
		if (s[i].score > max) {
			max = s[i].score;
		}
	}

	for (int i = 0; i < size; i++) {
		double relativeScore = (s[i].score / (double)max) * 100.0;                                       //relativan broj bodova u usporedbi sa najvecim POSTIGNUTIM brojem bodova izmedu studenata
		printf("%10s %10s %3d %3.2lf\n", s[i].name, s[i].surname, s[i].score, relativeScore);
	}

	return 0;
}
