#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define PAUSE getchar()
#define CLS system ("cls")
#define FLUSH myFlush()

typedef struct {
	char brand[55];  // like iPhone, or Motorola, or Samsung
	char model[55];  // like S10 or i10, or Moto6+
	char os[55];     // Android, ios
	float memory;    // in GB
	float storage;   // in GB
	int year;
} PHONE;

// Prototype Functions Here
void addNewPhone(PHONE **cellphones, int *eSize, int size);
void displayMenu();
void displayPhones(PHONE **cellphones, int eSize);
void displayPhoneMenu(PHONE **cellphones, int eSize);
void displayThePhones(PHONE **cellphones, int eSize, char order);
char getChoice();
int getSize();
PHONE *loadStuff(int *size, int *eSize, char *opened);
PHONE *makeAnElement(); // returns a pointer to an element node
void myFlush();
void savePhones(PHONE **phones, int size, int eSize);

main() {
	char choice;
	int eSize = 0;
	int size = 0;
	PHONE **cellphones = NULL;
	char opened = 'N'; // if able to open or not

	cellphones = loadStuff(&size, &eSize, &opened);
	if(opened == 'N'){
		size = getSize();
		cellphones = calloc(size, sizeof(PHONE*));
		if (cellphones == NULL) {
			printf("Not able to create the array of indexes...program ending!\n\n");
			PAUSE;
			exit(-1);
		} 
	} // end if
	do {
		choice = getChoice();
		switch (choice) {
		case 'A': // add a new phone record
			addNewPhone(cellphones, &eSize, size);
			break;
		case 'D': // display phone records
			displayPhoneMenu(cellphones, eSize);
			break;
		case 'Q': // quit the program
			printf("\n\n\t\tThanks for using the program.  Have a good day.\n\n");
			PAUSE;
			savePhones(cellphones, size, eSize);
			break;
		default:
			printf("\n\n\t\tInvalid selection, try again!\n\n");
			PAUSE;
			break;
		} // end switch
	} while (choice != 'Q');
} // end of main
/////////////////////////////////////////////////////////

void addNewPhone(PHONE **cellphones, int *eSize, int size) {
	if (*eSize == size) {
		printf("Sorry not room to store another phone, call tech support!\n");
		PAUSE;
		return;
	} // end if
	cellphones[*eSize] = makeAnElement();
	printf("Enter the brand of the phone....................: ");
	scanf("%s", &cellphones[*eSize]->brand); FLUSH;
	printf("Enter the model of the phone....................: ");
	scanf("%s", &cellphones[*eSize]->model); FLUSH;
	printf("Enter the operating system for the phone........: ");
	scanf("%s", &cellphones[*eSize]->os); FLUSH;
	printf("Enter the amount of ram/memory in the phone (GB): ");
	scanf("%f", &cellphones[*eSize]->memory); FLUSH;
	printf("Enter the amount of storage in the phone (GB)...: ");
	scanf("%f", &cellphones[*eSize]->storage); FLUSH;
	printf("Enter the year the phone was made...............: ");
	scanf("%i", &cellphones[*eSize]->year); FLUSH;
	*eSize = *eSize + 1;
} // end addNewPhone



void displayPhones(PHONE **cellphones, int eSize) {
	int i;
	CLS;
	for (i = 0; i < eSize; i++) {
		printf("Phone Record %i of %i\n\n", i + 1, eSize);
		printf("Brand...........: %s\n", cellphones[i]->brand);
		printf("Model...........: %s\n", cellphones[i]->model);
		printf("Operating System: %s\n", cellphones[i]->os);
		printf("Memory..........: %.1f MB\n", cellphones[i]->memory);
		printf("Storage.........: %.1f GB\n", cellphones[i]->storage);
		printf("Year made.......: %i\n", cellphones[i]->year);
		printf("\n------------------------------------------------------\n");
	} // end for loop
	PAUSE;
} // end displayPhones

void displayMenu() {
	CLS;
	printf("\n\n");
	printf("\t\t================================================================\n");
	printf("\t\t==                PHONE DATABASE PROGRAM                      ==\n");
	printf("\t\t================================================================\n");
	printf("\t\t== [A]DD A NEW PHONE RECORD                                   ==\n");
	printf("\t\t----------------------------------------------------------------\n");
	printf("\t\t== [D]ISPLAY ALL PHONE RECORDS                                ==\n");
	printf("\t\t----------------------------------------------------------------\n");
	printf("\t\t== NEXT MENU CHOICE GOES HERE                                 ==\n");
	printf("\t\t----------------------------------------------------------------\n");
	printf("\t\t== [Q]UIT THE PROGRAM                                         ==\n");
	printf("\t\t----------------------------------------------------------------\n");
	printf("\n\n\t\tENTER YOUR SELECTION: ");
	return;
} // end displayMenu

void displayPhoneMenu(PHONE **cellphones, int eSize) {
	char choice;
	do {
		CLS;
		printf("\n\n");
		printf("\t\t================================================================\n");
		printf("\t\t==                DISPLAY PHONES SUBMENU                      ==\n");
		printf("\t\t================================================================\n");
		printf("\t\t== [A]SCENDING ORDER....(DISPLAY ALL PHONE RECORDS)           ==\n");
		printf("\t\t----------------------------------------------------------------\n");
		printf("\t\t== [D]ESCENDING ORDER...(DISPLAY ALL PHONE RECORDS)           ==\n");
		printf("\t\t----------------------------------------------------------------\n");
		printf("\t\t== [E]NTRY ORDER........(DISPLAY ALL PHONE RECORDS)           ==\n");
		printf("\t\t----------------------------------------------------------------\n");
		printf("\t\t== [R]ETURN TO THE MAIN MENU                                  ==\n");
		printf("\t\t----------------------------------------------------------------\n");
		printf("\n\n\t\tENTER YOUR SELECTION: ");
		scanf("%c", &choice); FLUSH;
		switch (toupper(choice)) {
		case 'A':  // display in ASCENDING ORDER
			displayThePhones(cellphones, eSize, 'A');
			break;
		case 'D':  // display in DESCENDING ORDER 
			displayThePhones(cellphones, eSize, 'D');
			break;
		case 'E':  // display in ENTRY ORDER
			displayThePhones(cellphones, eSize, 'E');
			break;
		case 'R':
			printf("Going back to main menu, press enter.\n");
			PAUSE;
			break;
		default:
			printf("INVALID...try again...\n");
			PAUSE;
		} // end switch
	} while (toupper(choice) != 'R');
	return;
} // end displayPhoneMenu

void displayThePhones(PHONE **a, int eSize, char order) {
	char swapped;
	int bottom = eSize - 1;

	if (order == 'E') {
		displayPhones(a, eSize);
		return;
	} // end if

	// Save the array
	PHONE **temp = calloc(eSize, sizeof(PHONE*));
	if (temp == NULL) {
		printf("NO ROOM TO SORT\n");
		exit(-1);
	}// end if

	PHONE **tempLoc = calloc(1, sizeof(PHONE*));
	if (tempLoc == NULL) {
		printf("NO ROOM TO SORT\n");
		exit(-1);
	}// end if

	
	// Copy the cellphone array
	for (int i = 0; i < eSize; i++)
		temp[i] = a[i];

	// Sort the array
	do {
		swapped = 'N';
		for (int i = 0; i < bottom; i++) {
			if (order == 'A') {
				if (strcmp(temp[i]->model, temp[i + 1]->model) > 0) {
					tempLoc = temp[i];
					temp[i] = temp[i + 1];
					temp[i + 1] = tempLoc;
					swapped = 'Y';
				} // end if
			}
			else {
				if (strcmp(temp[i]->model, temp[i + 1]->model) < 0) {
					tempLoc = temp[i];
					temp[i] = temp[i + 1];
					temp[i + 1] = tempLoc;
					swapped = 'Y';
				} // end if
			}
		} // end for loop
		bottom--;
	} while (swapped == 'Y');

	displayPhones(temp, eSize);

	//free(tempLoc);
} // end displayThePhones

char getChoice() {
	char result;
	displayMenu();
	scanf("%c", &result); FLUSH;
	return toupper(result);
} // end getChoice


int getSize() {
	int result;
	char valid = 'Y';
	do {
		printf("Enter the number of phones records you are planning on storing: ");
		if (scanf("%i", &result) == 0) { // invalid value when the scanf returns a zero value
			valid = 'N';
			printf("\n\nYou must enter a valid integer value greater than zero!! \n\n");
		}
		else
			valid = 'Y';
		FLUSH;
	} while (valid == 'N' || result <= 0);
	return result;
} // end getSize

PHONE *makeAnElement() {
	int *result;
	result = calloc(1, sizeof(PHONE));
	if (result == NULL) {
		printf("Sorry not more space for even on more node!\n");
		PAUSE;
		exit(-1);
	} // end if
	return result;
} // end makeAnElement   


void myFlush(){
  while (getchar() != '\n');
} // end myFlush

PHONE *loadStuff(int *size, int *eSize, char *opened) {
	PHONE **result = NULL;
	FILE *ptr = fopen("cellphones.bin", "rb");
	if (ptr == NULL) {
		*opened = 'N';
		printf("Not able to open a saved data file....\n");
		PAUSE;
		return result;
	} // 
	// Get the size
		fread(size, sizeof(int), 1, ptr);
	// Get the effective size
		fread(eSize, sizeof(int), 1, ptr);

	// Create the table of contents array or the ** array
		result = calloc(*size, sizeof(PHONE*));
		if (result == NULL) {
			printf("MEMORY ERROR...\n");
			PAUSE;
			exit(-1);
		} // end if

    // Create and populate the NODES
		for (int i = 0; i < *eSize; i++) {
			result[i] = makeAnElement(); 
			fread(result[i], sizeof(PHONE), 1, ptr);
		} // end for 
		printf("Hey the stuff is back....\n");
		*opened = 'Y'; // throw the flag
		PAUSE;
	return result;
} // end loadStuff



void savePhones(PHONE **phones, int size, int eSize) {
	FILE *ptr2 = fopen("cellphones.bin", "wb");
	if (ptr2 == NULL) {
		printf("Sorry I cannot save anything...error in file\n");
		PAUSE;
		return;
	} // end if

	// Save the Size
		fwrite(&size, sizeof(int), 1, ptr2);

	// Save the eSize
		fwrite(&eSize, sizeof(int), 1, ptr2);

	// Save the NODES
		for (int i = 0; i < eSize; i++) {
			fwrite(phones[i], sizeof(PHONE), 1, ptr2);
			free(phones[i]);
		} // end for

    // Close out the memory for the table of contents the ** array
	// and clear the binfile pointer
		free(phones);
		fclose(ptr2);

		printf("ALL THE STUFF HAS BEEN SAVED!\n");
		PAUSE;
			   		 	  	  	   	
		return;
} // end savePhones




