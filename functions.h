//This project was created cooperatively by:
//Fatema Moharam, Department : CCE, ID: 6655, Group: 3, Section: 2
//Nourhan Waleed, Department : CCE, ID: 6609, Group: 3, Section: 1

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    int day,month,year;
}DATE ;
typedef struct {
    char lastname[20], firstname[20], address[150], email[150],phonenumber[15];
    DATE birthdate;
} contact ;
contact pcontacts[100];
char filename[20];

void save (int count);
void delete(int *count);
void load (int *count);
void printall(int count);
int searchlastname(const int count, int *a, int* b);
void Add(int *count);
void printcontact(const int i);
void modify(const int count);
int isnum(char checked[12]);
int checkalpha(char checked[150]);
int ismail(char mail[150]);
int nocomma(char address[150]);
void sort(const int count);
int searchfirstname(int *a, int* b);