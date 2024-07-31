
#include "myTemplate.h"



typedef struct
{
	int day;
	int month;
	int year;
}DATE;

void displayDates(DATE date, int *eSize);
void getDates(DATE *dates, int *eSize);

int main()
{
	int size = 1000;
	int eSize = 0;

	DATE *dates = calloc(size, sizeof(DATE));
	if (dates == NULL)
	{
		printf("No space!");
		PAUSE;
		exit(-1);
	}


	for (int i = 0; i < 5; i++)
	{
		getDates(&dates[i], &eSize);
	}
	for (int i = 0; i < 5; i++)
	{
		displayDates(dates[i], &eSize);
	}
}

void displayDates(DATE date, int *eSize)
{
	printf("The date at %x is %i/%i/%i.", date, date.month, date.month, date.year);
}

void getDates(DATE *dates, int *eSize)
{
	printf("Enter month: ");
	scanf("%i", dates->month);

	printf("Enter day: ");
	scanf("%i", dates->day);

	printf("Enter year: ");
	scanf("%i", dates->year);
}

/*
int main()
{
	int *number; //Pointer to interger
	int size = 99;

	//number = calloc(1, sizeof(int));
	number = calloc(size, sizeof(int)); //Assigns 

	if (number == NULL)
	{
		printf("No memory available!\n");
		PAUSE;
		exit(-1);
	}

	*number = 666;
	//number[0] = 666; Equivalent 
	//number++; This increments the adress by the amount of bytes of the datatype wich lets you use pointer math

	printf("The value is located at %x is %i.\n", number, *number); // Initializes to 0 by default

	PAUSE;

	free(number);
}
*/
