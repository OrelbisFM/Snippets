void validate_input(char dataType, char cValidate[], char iValidate[], char *cInput, int *iInput)
{
	int valid = FALSE;
	switch (tolower(dataType))
	{
	case 'i':	//Interger
		while (valid == FALSE)
		{
			for (unsigned int i = 0; i < strlen(iValidate); i++)
			{
				if (*iInput == (iValidate[i] - '0'))
					valid = TRUE;
			}
			if (valid == FALSE)
			{
				printf("Invalid input, please try again: ");
				scanf("%i", iInput); FLUSH;
			}
		}
		return;
	case 'c':	//Character
		while (valid == FALSE)
		{
			for (unsigned int i = 0; i < strlen(cValidate); i++)
			{
				if (*cInput == cValidate[i])
					valid = TRUE;
			}
			if (valid == FALSE)
			{
				printf("Invalid input, please try again: ");
				scanf("%c", cInput); FLUSH;
			}
		}
		return;
	default:
		printf("Invalid dataType specified for validate_input()!");
		PAUSE;
		exit(0);
		return;
	}
}
