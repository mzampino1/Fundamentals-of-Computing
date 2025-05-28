/* 
 * Matthew Zampino
 * Fundamentals of Computing - Lab 5 Part 2
 * Purpose: This program uses a text menu to store and manage
 * a list of sayings. After entering a startup data file to
 * be stored in the database, the user can then display the sayings,
 * enter a new saying, list sayings containing a given substring, 
 * save the sayings in the database to a new text file. The user
 * is reprompted with this text menu until the quit option is selected.
 */

#include <stdio.h>
#include <string.h>

// maximum length of saying, accounts for null character
#define MAX_LENGTH 257
// maximum number of sayings
#define MAX_SAYINGS 50

// function prototypes
void welcomeUser();
int startupAssign(char sayings[][MAX_LENGTH]);
void printMenu();
void displaySayings(char sayings[][MAX_LENGTH], int numSayings);
void newSaying(char sayings[][MAX_LENGTH], int numSayings);
void substringSearch(char sayings[][MAX_LENGTH], int numSayings);
void newFile(char sayings[][MAX_LENGTH], int numSayings);

int main() {
	
	welcomeUser();

	char sayings[MAX_SAYINGS][MAX_LENGTH];
	int numSayings = 0;

	// assigns startup file to sayings database, returns new number
	// of sayings or -1 if startup file does not exist
	numSayings = startupAssign(sayings);
	printf("\n");
	
	// if statement only runs the rest of the program if startup file
	// exists
	if(numSayings >= 0) {
		// flag used with while loop to reprompt user
		int stop = 0;
		while(!stop) {
			printMenu();
			int selection;
			scanf("%d", &selection);
			// removes newline from input buffer
			getchar();

			switch(selection) {
				case 1:
					displaySayings(sayings, numSayings);
					printf("\n");
					break;
				case 2:
					newSaying(sayings, numSayings);	
					// increases numSayings by 1 because of new saying added
					numSayings++;
					printf("\n");
					break;
				case 3:
					substringSearch(sayings, numSayings);
					printf("\n");
					break;
				case 4:
					newFile(sayings, numSayings);
					printf("\n");
					break;
				case 5:
					printf("Goodbye!\n");
					stop = 1;
					break;
				default:
					printf("Error: invalid selection.\n\n");
			}
		}
	}

	return 0;
}

// displays welcome message to user
void welcomeUser() {
	printf("Welcome to Sayings Manager!\n\n");
}

// prompts user for startup file name, returning -1 if the startup
// file does not exist. assigns sayings from this file into the array,
// and returns number of sayings added
int startupAssign(char sayings[][MAX_LENGTH]) {
	printf("Please enter your startup file name (30 characters max):\n");
	
	// size of 31 to account for null character
	char fileName[31];
	fgets(fileName, 31, stdin);

	// removes newline from fileName if necessary
	if(fileName[strlen(fileName) - 1] == '\n')
		fileName[strlen(fileName) - 1] = '\0';
	
	FILE *fp = fopen(fileName, "r");
	if(fp == NULL) {
		printf("Error: the file \"%s\" does not exist.\n", fileName);
		return -1;
	}

	int count = 0;

	// assigns strings to sayings array
	while(1) {
		fgets(sayings[count], MAX_LENGTH, fp);
		// removes newline from strings
		if(sayings[count][strlen(sayings[count])-1] == '\n')
			sayings[count][strlen(sayings[count])-1] = '\0';
		if(feof(fp)) {
			fclose(fp);
			break;
		}
		count++;
	}
	return count;
}

// displays text menu to user
void printMenu() {
	printf("Please enter the number corresponding to your desired action.\n");

	printf("1. display all sayings currently in the database\n");
	printf("2. enter a new saying into the database\n");
	printf("3. list sayings that contain a given substring\n");
	printf("4. save all sayings in a new text file\n");
	printf("5. quit\n");
}

// prints current list of sayings in database
void displaySayings(char sayings[][MAX_LENGTH], int numSayings) {
	// prints each saying
	for(int i = 0; i < numSayings; i++)
		puts(sayings[i]);
}

// adds a new saying string to the sayings array
void newSaying(char sayings[][MAX_LENGTH], int numSayings) {
	char str[257];
	printf("Please enter your new saying (256 characters max):\n");
	fgets(str, 257, stdin);

	// removes newline if necessary
	if(str[strlen(str) - 1] == '\n')
		str[strlen(str) - 1] = '\0';
	
	strcpy(sayings[numSayings], str);
}

// displays all sayings containing a substring entered by the user
void substringSearch(char sayings[][MAX_LENGTH], int numSayings) {
	printf("Please enter the substring you would like to search for:\n");
	char str[MAX_LENGTH];
	fgets(str, MAX_LENGTH, stdin);
	// removes newline from substring if necessary
	if(str[strlen(str) - 1] == '\n')
		str[strlen(str) - 1] = '\0';
	
	printf("Sayings that include the substring \"%s\":\n", str);
	for(int i = 0; i < numSayings; i++) {
		// only prints saying if str occurs in that saying
		if(strstr(sayings[i], str) != NULL)
			puts(sayings[i]);
	}
}

// saves all of the sayings currently in the array into a new text file with
// name specified by the user
void newFile(char sayings[][MAX_LENGTH], int numSayings) {
	printf("Please enter the new file's name (30 characters max):\n");
	char fileName[30];
	fgets(fileName, 30, stdin);
	// removes newline from file name if necessary
	if(fileName[strlen(fileName) - 1] == '\n')
		fileName[strlen(fileName) - 1] = '\0';

	FILE *fp = fopen(fileName, "w");
	for(int i = 0; i < numSayings; i++) {
		fputs(sayings[i], fp);
		// ensures that each saying ends in a newline
		fprintf(fp, "\n");
	}
	fclose(fp);
	printf("Successfully saved!\n");
}
