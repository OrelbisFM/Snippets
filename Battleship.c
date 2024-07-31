#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define PAUSE system("pause")
#define CLS system("cls")
#define FLUSH myFlush()
#define ROWS 10
#define COLS 10
#define POINTS 100
#define SRAND srand((unsigned)time(NULL))

typedef struct {
	char name[100];
	char letter;
	int holes;
	int hits;
	char sunk[15];
	int x;
	int y;
	int dir;
	char sunkTest;
}SHIPS;// tells me what each ships need

typedef struct {
	int misslesShots;
	int misses;
	int hits;
	char inputgrid[ROWS][COLS];
	char grid[ROWS][COLS];
	SHIPS shps[5];
}GAME;// tells me that each board needs this

void createSave(GAME game, FILE *sGB, int pS[], int *eSize, FILE *sCT);
void displayGrid(char grid[ROWS][COLS]);
void displayMenu();
void insertValue(int a[], int eSize, int location, int value);
void getChoice(int *choice);
void intgrid(char grid[ROWS][COLS], char input[ROWS][COLS], SHIPS shps[5], char loaded, FILE *sGB, GAME *games);
void loadSave(FILE *sGB, int pS, GAME *games, FILE *sCT);
void myFlush();
void placeDirection(SHIPS shp, char place[][COLS], int direction);
void placeships(char place[ROWS][COLS], SHIPS shps[5], char loaded, FILE *sGB, GAME *games);
void scoreDisplay(GAME game);
void shpsMaking(SHIPS shps[]);
void topTenScores(GAME games, FILE *tST, int ps[]);
void writeScore(GAME *games, int pS[], int *eSize);

int main() {
	int choice;
	int pointSystem[POINTS];
	int random = 309;
	int eSize = 0;
	char loaded = 'N';
	GAME games;
	FILE *saveGameTxt = NULL;// TEXT
	FILE *topScorestxt = NULL;//TEXT
	FILE *scoresTxt = NULL;// TEXT

	games.hits = 0;
	games.misses = 0;
	games.misslesShots = 0;

	for (int i = 0; i < 5; i++)
		games.shps[i].sunkTest = 'N';

	SRAND;
	shpsMaking(games.shps);
	intgrid(games.grid, games.inputgrid, games.shps, loaded, saveGameTxt, &games);
	getChoice(&choice);

	do {
		switch (choice) {
		case 1:
			displayGrid(games.grid);
			createSave(games, saveGameTxt, pointSystem, &eSize, scoresTxt);
			writeScore(&games, pointSystem, &eSize);
			PAUSE; CLS;
			break;
		case 2:
			loadSave(saveGameTxt, pointSystem, &games, scoresTxt);
			choice = 1;
			break;
		case 3:
			topTenScores(games, topScorestxt, pointSystem);
			PAUSE;
			exit(-1);
		case 4:
			printf("Exiting the game (enter)\nYour game has been saved.\n");
			PAUSE;
			exit(-1);
			break;

		default:
			printf("THAT'S AN INVALID CHOICE\n");
			PAUSE;
			break;
		}// end switch
	} while (choice <= 4);

}// end of main

void createSave(GAME game, FILE *sGB, int pS[], int *eSize, FILE *sCT) {
	sGB = fopen("Save Game.txt", "w");
	sCT = fopen("Save Score.txt", "w");

	char x, y;
	for (x = 0; x < ROWS; x++) {
		for (y = 0; y < COLS; y++) {
			fprintf(sGB, "%c", game.grid[x][y]);
		}// end of inner for loop
		fprintf(sGB, "\n");
	}// end of outter for loop

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			fprintf(sGB, "%c", game.inputgrid[i][j]);
		}//End inner loop
		fprintf(sGB, "\n");
	}//End outer for
	fprintf(sCT, "%i\n", game.misslesShots);
	fprintf(sCT, "%i\n", game.hits);
	fprintf(sCT, "%i\n", game.misses);
	for (int i = 0; i < 5; i++)
	{
		fprintf(sGB, "%i\n", game.shps[i].dir);
		fprintf(sGB, "%i\n", game.shps[i].hits);
		fprintf(sGB, "%i\n", game.shps[i].holes);
		fprintf(sGB, "%c\n", game.shps[i].letter);
		fprintf(sGB, "%i\n", game.shps[i].x);
		fprintf(sGB, "%i\n", game.shps[i].y);
		fprintf(sCT, "%c\n", game.shps[i].sunkTest);
	}
	fclose(sGB);
	fclose(sCT);
}//End createSave

void displayGrid(char grid[ROWS][COLS]) {
	char x, y;
	printf("    a  b  c  d  e  f  g  h  i  j\n");
	printf("    == == == == == == == == == ==\n");
	for (x = 0; x < ROWS; x++) {
		printf("[%i]", (x + 1) - 1);
		for (y = 0; y < COLS; y++) {
			printf(" %c ", grid[x][y]);
		}// end of inner for loop
		printf("\n");
	}// end of outter for loop
}// end displayGrid

void displayMenu() {
	printf("1. Start New Game\n");// done
	printf("2. Resume an Existing Game\n");// have to be done with a text/bin file
	printf("3. View Best Scores\n");// have to be done with a text/bin file
	printf("4. Quit\n");// done
}// menu for choices

void getChoice(int *choice) {
	displayMenu();
	printf("Enter a Choice:  ");
	scanf_s("%i", choice); FLUSH;
}// end getCHoice

void intgrid(char grid[ROWS][COLS], char input[ROWS][COLS], SHIPS shps[5], char loaded, FILE *sGB, GAME *games) {
	char x, y;
	for (x = 0; x < ROWS; x++) {
		for (y = 0; y < COLS; y++) {
			grid[x][y] = '.';
			input[x][y] = ' ';
		}// end of inner loop
	}// end of outter loop
	placeships(input, shps, loaded, sGB, games);// puts the ships that are in the grid.
}// end of intgrid

void loadSave(FILE *sGB, int pS, GAME *games, FILE *sCT) {
	char x, y;
	char trash;
	sGB = fopen("Save Game.txt", "r");
	sCT = fopen("Save Score.txt", "r");
	for (x = 0; x < ROWS; x++) {
		for (y = 0; y < COLS; y++) {
			fscanf(sGB, "%c", &games->grid[x][y]);
		}// end of inner for loop
		fscanf(sGB, "%c", &trash);
	}// end of outter for loop
	for (x = 0; x < ROWS; x++) {
		for (y = 0; y < COLS; y++) {
			fscanf(sGB, "%c", &games->inputgrid[x][y]);
		}// end of inner for loop
		fscanf(sGB, "%c", &trash);
	}// end of outter for loop
	fscanf(sCT, "%i", &games->misslesShots);
	fscanf(sCT, "%c", &trash);
	fscanf(sCT, "%i", &games->hits);
	fscanf(sCT, "%c", &trash);
	fscanf(sCT, "%i", &games->misses);
	fscanf(sCT, "%c", &trash);
	for (int i = 0; i < 5; i++)
	{
		fscanf(sGB, "%i", &games->shps[i].dir);
		fscanf(sGB, "%i", &games->shps[i].hits);
		fscanf(sGB, "%i", &games->shps[i].holes);
		fscanf(sGB, "%c", &trash);
		fscanf(sGB, "%c", &games->shps[i].letter);
		fscanf(sGB, "%i", &games->shps[i].x);
		fscanf(sGB, "%i", &games->shps[i].y);
		fscanf(sGB, "%c", &trash);
		fscanf(sCT, "%c", &games->shps[i].sunkTest);
		if (games->shps[i].sunkTest == 'Y')
			strcpy(games->shps[i].sunk, "Sunk");
	}
	fclose(sGB);
	fclose(sCT);
}//End loadSave

void myFlush() {
	while (getchar() != '\n');
}// end myFlush

void placeDirection(SHIPS shp, char place[][COLS], int direction)
{
	int i = 0, j = 0;
	switch (direction)
	{
	case 0://north
		for (j = 0; j < shp.holes; j++) {
			place[shp.x - j][shp.y] = shp.letter;
		}
		break;
	case 1:// east
		for (j = 0; j < shp.holes; j++) {
			place[shp.x][shp.y + j] = shp.letter;
		}
		break;
	case 2:// south
		for (j = 0; j < shp.holes; j++) {
			place[shp.x + j][shp.y] = shp.letter;
		}
		break;
	case 3:// west
		for (j = 0; j < shp.holes; j++) {
			place[shp.x][shp.y - j] = shp.letter;
		}
		break;
	}
}
// end of placeDirection

void placeships(char place[ROWS][COLS], SHIPS shps[5], char loaded, FILE *sGB, GAME *games)
{
	int i = 0, j = 0;
	int distance;
	int invalidPosition;// this is my flag
	char x, y;

	if (loaded == 'N') {
		for (i = 0; i < 5; i++) {
			//Generate x-y position and direction
			shps[i].x = rand() % ROWS;
			shps[i].y = rand() % COLS;
			shps[i].dir = rand() % 4;
			//Test if that is a valid combination
			switch (shps[i].dir) {
			case 0:// North
				distance = shps[i].x + 1 - shps[i].holes;
				do {
					invalidPosition = 0;// flag
					if (distance < 0) {
						invalidPosition = 1;
					}
					for (j = 0; j < shps[i].holes; j++) {
						if (place[shps[i].x - j][shps[i].y] != ' ') {
							invalidPosition = 1;
						}// end of inner loop
					}// end of outter loop
					if (invalidPosition == 1) {
						shps[i].x = rand() % ROWS;
						shps[i].y = rand() % COLS;
						distance = shps[i].x + 1 - shps[i].holes;
					}
				} while (invalidPosition == 1);
				placeDirection(shps[i], place, shps[i].dir);

				break;
			case 1:// east
				distance = (COLS - shps[i].y) - shps[i].holes;
				do {
					invalidPosition = 0;
					if (distance < 0) {
						invalidPosition = 1;
					}
					for (j = 0; j < shps[i].holes; j++) {
						if (place[shps[i].x][shps[i].y + j] != ' ') {
							invalidPosition = 1;
						}// end of outter loop
					}// end of inner loop
					if (invalidPosition == 1) {
						shps[i].x = rand() % ROWS;
						shps[i].y = rand() % COLS;
						distance = (COLS - shps[i].y) - shps[i].holes;

					}
				} while (invalidPosition == 1);
				placeDirection(shps[i], place, shps[i].dir);
				break;
			case 2:// south
				distance = (ROWS - shps[i].x) - shps[i].holes;
				do {
					invalidPosition = 0;
					if (distance < 0) {
						invalidPosition = 1;
					}
					for (j = 0; j < shps[i].holes; j++) {
						if (place[shps[i].x + j][shps[i].y] != ' ') {
							invalidPosition = 1;
						}// end of inner loop
					}// end of outter loop
					if (invalidPosition == 1) {
						shps[i].x = rand() % ROWS;
						shps[i].y = rand() % COLS;
						distance = (ROWS - shps[i].x) - shps[i].holes;
					}
				} while (invalidPosition == 1);
				placeDirection(shps[i], place, shps[i].dir);
				break;
			case 3:// west
				distance = shps[i].y + 1 - shps[i].holes;
				do {
					invalidPosition = 0;
					if (distance < 0) {
						invalidPosition = 1;
					}
					for (j = 0; j < shps[i].holes; j++) {
						if (place[shps[i].x][shps[i].y - j] != ' ') {
							invalidPosition = 1;
						}//end of innner loop
					}// end of outter loop
					if (invalidPosition == 1) {
						shps[i].x = rand() % ROWS;
						shps[i].y = rand() % COLS;
						distance = shps[i].y + 1 - shps[i].holes;
					}// end if
				} while (invalidPosition == 1);
				placeDirection(shps[i], place, shps[i].dir);
				break;
			}
			//place ship

		}// end for
	}//End loaded flag for
	else if (loaded == 'Y') {
		for (x = 0; x < ROWS; x++) {
			for (y = 0; y < COLS; y++) {
				fscanf(sGB, "%c", games->grid[x][y]);
			}// end of inner for loop
		}// end of outter for loop
	}//End if

}
// end placeShips

void scoreDisplay(GAME game) {
	printf("\n");
	printf("%s\t", game.shps[0].name), printf("%-8s\t  ", game.shps[0].sunk), printf("Missiles fired: %i\n", game.misslesShots);
	printf("%s\t", game.shps[1].name), printf("%s  \n", game.shps[1].sunk);
	printf("%s\t", game.shps[2].name), printf("%-8s\t  ", game.shps[2].sunk), printf("Ships Hit: %i\n", game.hits);
	printf("%s\t", game.shps[3].name), printf("%s  \n", game.shps[3].sunk);
	printf("%s\t", game.shps[4].name), printf("%-8s\t  ", game.shps[4].sunk), printf("Ships missed: %i\n", game.misses);
	printf("\nEnter[Letter followed by Number or QQ to Quit]: ");
}
// end of bottom board menu

void shpsMaking(SHIPS shps[]) {
	strcpy_s(shps[0].name, 100, "Air Force Academy");// first ship made
	shps[0].letter = 'A';
	shps[0].holes = 5;
	shps[0].hits = 5;
	shps[0].x;
	shps[0].y;
	strcpy_s(shps[0].sunk, 15, "Floating");
	strcpy_s(shps[1].name, 100, "Deland High School");// second ship made
	shps[1].letter = 'D';
	shps[1].holes = 2;
	shps[1].hits = 2;
	shps[1].x;
	shps[1].y;
	strcpy_s(shps[1].sunk, 15, "Floating");
	strcpy_s(shps[2].name, 100, "Eskimo University");// third ship made
	shps[2].letter = 'E';
	shps[2].holes = 3;
	shps[2].hits = 3;
	shps[2].x;
	shps[2].y;
	strcpy_s(shps[2].sunk, 15, "Floating");
	strcpy_s(shps[3].name, 100, "Seminole State Ship");// fourth ship made
	shps[3].letter = 'S';
	shps[3].holes = 3;
	shps[3].hits = 3;
	shps[3].x;
	shps[3].y;
	strcpy_s(shps[3].sunk, 15, "Floating");
	strcpy_s(shps[4].name, 100, "Valencia Destroyer");// fifth ship made
	shps[4].letter = 'V';
	shps[4].holes = 4;
	shps[4].hits = 4;
	shps[4].x;
	shps[4].y;
	strcpy_s(shps[4].sunk, 15, "Floating");
}// end of shpsMaking


void topTenScores(GAME games, FILE *tST, int ps[]) {

	printf("== TOP TEN SCORES ==\n");
	for (int i = 0; i < 10; i++) {
		printf("%i. %i\n", i + 1, ps[i]);
	}//End for
}//End topTenScores

void writeScore(GAME *games, int pS[], int *eSize) {
	char x, y;
	char switched = 'N';
	int hasHit = -1;
	int hits = 0;
	int shots = 0;
	int misses = 0;
	int highest = 0, lowest;
	scoreDisplay(*games);

	scanf_s("%c", &y);//number
	scanf_s("%c", &x);//letter
	FLUSH;
	x = tolower(x);
	y = tolower(y);
	if (x == 'q' && y == 'q')
	{
		printf("THANKS FOR PLAYING \n");
		PAUSE;
		CLS;
		return main();
	}
	y = y - 'a';
	x = x - '0';

	if ((x < 'a' || x > 'j') && (y < 0 || y > 9)) {
		printf("THAT'S AN INVALID COORDINATE \n");
	}
	else {
		if (games->grid[x][y] == '.')
		{
			if (games->shps->sunkTest)
			{
				if (games->inputgrid[x][y] != ' ') {
					games->hits++;
					printf("hit\n");
					games->grid[x][y] = 'H';
					switch (games->inputgrid[x][y])
					{
					case 'A':
						games->shps[0].hits--;
						if (games->shps[0].hits == 0) {
							placeDirection(games->shps[0], games->grid, games->shps[0].dir);
							strcpy_s(games->shps[0].sunk, 15, "sunk");
							games->shps[0].sunkTest = 'Y';
							placeDirection(games->shps[0], games->grid, games->shps[0].dir);
						}
						break;
					case 'D':
						games->shps[1].hits--;
						if (games->shps[1].hits == 0) {
							placeDirection(games->shps[1], games->grid, games->shps[1].dir);
							strcpy_s(games->shps[1].sunk, 15, "sunk");
							games->shps[1].sunkTest = 'Y';
							placeDirection(games->shps[1], games->grid, games->shps[1].dir);
						}
						break;
					case 'E':
						games->shps[2].hits--;
						if (games->shps[2].hits == 0) {
							placeDirection(games->shps[2], games->grid, games->shps[2].dir);
							strcpy_s(games->shps[2].sunk, 15, "sunk");
							games->shps[2].sunkTest = 'Y';
							placeDirection(games->shps[2], games->grid, games->shps[2].dir);
						}
						break;
					case 'S':
						games->shps[3].hits--;
						if (games->shps[3].hits == 0) {
							placeDirection(games->shps[3], games->grid, games->shps[3].dir);
							strcpy_s(games->shps[3].sunk, 15, "sunk");
							games->shps[3].sunkTest = 'Y';
							placeDirection(games->shps[3], games->grid, games->shps[3].dir);
						}
						break;
					case 'V':
						games->shps[4].hits--;
						if (games->shps[4].hits == 0) {
							placeDirection(games->shps[4], games->grid, games->shps[4].dir);
							strcpy_s(games->shps[4].sunk, 15, "sunk");
							games->shps[4].sunkTest = 'Y';
							placeDirection(games->shps[4], games->grid, games->shps[4].dir);
						}
						break;
					default:
						break;
					}
					games->misslesShots++;
				}
				else
				{
					printf("miss\n");
					games->grid[x][y] = 'M';
					games->misses++;
					games->misslesShots++;
				}
			}
			if ((games->shps[0].sunkTest == 'Y') && (games->shps[1].sunkTest == 'Y') && (games->shps[2].sunkTest == 'Y') && (games->shps[3].sunkTest == 'Y') && (games->shps[4].sunkTest == 'Y'))
			{
				printf("GAME OVER!\n");
				printf("YOU WON!\n");
				PAUSE;
				CLS;
				return main();
				findLocation(pS, eSize, games->misslesShots);
				eSize = findLocation(pS, eSize, games->misslesShots);
			}//End if
		}
		else {
			printf("you fired here already!!!\n");
		}//End else
	}//End outer else


}
// end of writescores

void insertValue(int a[], int eSize, int location, int value) {
	for (int i = eSize; i > location; i--)
		a[i] = a[i - 1];
	a[location] = value;
}// end insertValue

int findLocation(int array[], int eSize, int value) {
	int result = eSize;
	int i = 0;
	char inserted = 'N';
	while (i < result && inserted == 'N' && result < ROWS) {
		if (value < array[i]) {
			insertValue(array, eSize, i, value);
			inserted = 'Y';
			result++;
		}//End if
		i++;
	}//end while
	if (inserted == 'N' && result < ROWS) {
		array[result] = value;//throws the value to the bottom of the array
		result++;
	}//End if
	return result;
}//End findLocation
