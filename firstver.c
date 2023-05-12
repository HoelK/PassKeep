
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void emptybuffer()
{
	int c = 0;
	while(c != '\n' && c != EOF)
	{
		c = getchar();
	}
}

int countline(FILE **descFILE) //Count the numbers of passwords
{
	int c = 0, lines = 0;

	*descFILE = fopen("desc.txt", "r");
	while(!feof(*descFILE))
	{
		c = fgetc(*descFILE);
		if(c == '\n')
			lines++;
	}
	return lines;
}

void masterpass() //Ask the password for acces the database
{

}

void choice() //Ask what the user want to do
{

}

void displaydata(const int totlines, FILE **descFILE, FILE **passFILE) //Show every passwords
{
	char outputdesc[25] = {0};
	char outputpass[25] = {0};

	*descFILE = fopen("desc.txt", "r");
	*passFILE = fopen("pass.txt", "r");
	
	printf("Description");
	printf("	Mot de passe\n\n");

	for (int i = 0; i < totlines; i++)
	{
		fgets(outputdesc, 25, *descFILE);
		outputdesc[strcspn(outputdesc, "\n")] = 0;
		printf("%s  	", outputdesc);

		fgets(outputpass, 25, *passFILE);
		printf("%s", outputpass);
	}

	fclose(*passFILE);
	fclose(*descFILE);
}


void newpass(FILE **descFILE, FILE **passFILE) //Add a password
{
	char inputdesc[25] = {0};
	char inputpass[25] = {0};

	//Adding the descrition in the file
	printf("Veuillez entrer une description site/email... : ");
	fgets(inputdesc, 25, stdin);

	*descFILE = fopen("desc.txt", "a");
	fprintf(*descFILE, "%s", inputdesc);
	fclose(*descFILE);

	//Adding the password in the file
	printf("Veuillez entrer un mot de passe : ");
	fgets(inputpass, 25, stdin);

	*passFILE = fopen("pass.txt", "a");
	fprintf(*passFILE, "%s", inputpass);
	fclose(*passFILE);
}

void deletepass(int totlines, FILE **descFILE, FILE **passFILE) //Delete a password
{
	int line = 1, deleteline= 0;
	char descLine[25] = {0}, passLine[25] = {0};
	FILE *tempDesc = NULL;
	FILE *tempPass = NULL;

	printf("Veuillez saisir le numéro de la ligne du mot de passe à supprimer : ");
	scanf("%d", &deleteline);

	*descFILE = fopen("desc.txt", "r");
	*passFILE = fopen("pass.txt", "r");

	tempDesc = fopen("tempdesc.txt", "a");
	tempPass = fopen("temppass.txt", "a");

	for(int i = 0; i < totlines; i++)
	{
		fgets(descLine, 25, *descFILE);
		fgets(passLine, 25, *passFILE);

		if(line != deleteline)
		{
			fputs(descLine, tempDesc);
			fputs(passLine, tempPass);
		}
		line++;
	}

	fclose(*descFILE);
	fclose(*passFILE);
	remove("desc.txt");
	remove("pass.txt");
	rename("tempdesc.txt", "desc.txt");
	rename("temppass.txt", "pass.txt");

	*descFILE = tempDesc;
	*passFILE = tempPass;

	fclose(*descFILE);
	fclose(*passFILE);
}

void randompass() //Generate a random secured password
{

}


void main()
{
	int totlines = 0;
	FILE *passFILE = NULL;
	FILE *descFILE = NULL;

	totlines = countline(&descFILE);
	displaydata(totlines, &descFILE, &passFILE);
}
