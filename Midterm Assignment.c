#define _CRT_SECURE_NO_WARNINGS
#define PAUSE system("pause")
#define FLUSH myFlush()
#define CLS system("cls")

#define SIZE 51
#define EMPTY -1
#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/////* Stack & Stack Functions */////
typedef struct stack
{
	char items[SIZE];
	int top;
}STACK;

void initialize(STACK* stackPtr);
int push(STACK* stackPtr, int value);
int pop(STACK* stackPtr);
int full(STACK* stackPtr);
int empty(STACK* stackPtr);
int top(STACK* stackPtr);

///////////* Functions *////////////
int is_balanced_parenthesis(char* string);
int is_operator(char c);
int get_operator_priority(char c);
int convert_to_int(char c);

char* convert_to_post_fix(char string[]);
void menu();
void evaluate(char string[]);
void myFlush();

////////////////////////////////////

char cUsrInput[SIZE];
STACK operators;
STACK postFix;


void main()
{
	while (strcmp(cUsrInput, "X") != 0)
	{
		menu();
		if (is_balanced_parenthesis(cUsrInput))
		{
			convert_to_post_fix(cUsrInput);
			evaluate(postFix.items);
		}
		else
		{
			printf("Parenthesis imbalanced");
		}
	}
	return;
}


int is_balanced_parenthesis(char* string)
{
	int iLeftParenthesis = 0, iRightParenthesis = 0;

	for (int i = 0; i < (int)strlen(string); i++)
	{
		if (string[i] == '(')
			iLeftParenthesis++;
		if (string[i] == ')')
			iRightParenthesis++;
	}
	return (iLeftParenthesis == iRightParenthesis);
}

int is_operator(char c)
{
	switch (c)
	{
	case '+':
	case '-':
	case '/':
	case '*':
	case '^':
	case '%':
		return TRUE;
	default:
		return FALSE;
	}
}

int get_operator_priority(char c)
{
	switch (c)
	{
	case '+':
	case '-':
		return 1;
	case '/':
	case '*':
	case '%':
		return 2;
	case '^':
		return 3;
	default:
		printf("Incorrect use of get_operator_priority()"); PAUSE;
		exit(1);
	}
}

int convert_to_int(char c)
{
	if ((c - '0') >= 0 && (c - '0') <= 9)
	{
		return (c - '0');
	}
	else
	{
		return -1;
	}
}

char* convert_to_post_fix(char string[])
{
	int iCount = 0;
	char cTempPostfix[SIZE];

	for (int i = 0; i < (int)strlen(string); i++)
	{
		
		if (convert_to_int(string[i]) != -1)
		{
			if (string[i+1])
			{

			}
		}
	}
}

void evaluate(char string[])
{

}

void menu()
{
	char usrChoice;
	char infix[SIZE] = { '\0' };
	
	do
	{
		CLS;
		printf("**************************\n");
		printf("**         Menu         **\n");
		printf("**************************\n");
		printf("E. Enter infix.\n");
		printf("X. Exit.\n\n");

		printf("Input choice: "); (void)scanf("%c", &usrChoice); FLUSH;
		usrChoice = toupper(usrChoice);
		
		switch (usrChoice)
		{
		case 'E':
			printf("\n\nInput infix expression: "); (void)scanf("%s", infix); FLUSH;
			strcpy(cUsrInput, infix);
			return;
		case 'X':
			exit(1);
			break;
		default:
			printf("\n\nPlease enter a valid choice."); PAUSE;
			break;
		}
	} while (1);
}

void myFlush() {
	while (getchar() != '\n');
}

///////////*  Stack usage functions  *///////////
void initialize(STACK* stackPtr)
{
	stackPtr->top = -1;
}

int push(STACK* stackPtr, int value)
{
	if (full(stackPtr))
		return 0;
	stackPtr->items[stackPtr->top + 1] = value;
	(stackPtr->top)++;
	return 1;
}

int pop(STACK* stackPtr)
{
	int retval;

	if (empty(stackPtr))
		return EMPTY;

	retval = stackPtr->items[stackPtr->top];
	(stackPtr->top)--;
	return retval;
}

int full(STACK* stackPtr)
{
	return (stackPtr->top == SIZE - 1);
}

int empty(STACK* stackPtr)
{
	return (stackPtr->top == -1);
}

int top(STACK* stackPtr)
{
	if (empty(stackPtr))
		return EMPTY;

	return stackPtr->items[stackPtr->top];
}