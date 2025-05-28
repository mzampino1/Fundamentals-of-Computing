// Matthew Zampino
// Fundamentals of Computing - Lab 7 Part 2

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "statesfunc.h"

// removes newline from string if necessary
void removeNewline(char str[]) {
	if(str[strlen(str) - 1] == '\n')
		str[strlen(str) - 1] = '\0';
}

// returns file pointer to file specified by user
FILE* openUserFile() {
	// infinite while loop reprompts user until valid file name is entered
	while(1) {
		// gets file name string from user input, assuming name is
		// 19 characters or less
		char fileName[20];
		printf("Please enter name of data file: ");
		fgets(fileName, 20, stdin);
		removeNewline(fileName);

		FILE* fp = fopen(fileName, "r");
		if(fp == NULL)
			printf("Error: file does not exist.\n\n");
		else
			return fp;
	}
}

// assigns state info from csv file to states array, returns number
// of states assigned
int assignStateInfo(State states[], FILE* fp) {
	// counts number of states assigned
	int cnt = 0;

	while(1) {
		char line[50]; 
		fgets(line, 50, fp);
		// breaks out of while loop if end of file is reached
		// when attempting fgets
		if(feof(fp))
			break;
		removeNewline(line);
	
		// assigns values on each line to the State variable at the
		// corresponding index of states, using "," as delimiter
		strcpy(states[cnt].abbreviation, strtok(line, ","));
		strcpy(states[cnt].name, strtok(NULL, ","));
		strcpy(states[cnt].capital, strtok(NULL, ","));
		states[cnt].year = atoi(strtok(NULL, ","));
		
		// increments counting variable
		cnt++;
	}
	return cnt;
}

// prints text menu with options for user to select from
void printTextMenu() {
	printf("\n");
	printf("Please enter the number corresponding to your desired action.\n");
	printf("1: List data for all states\n");
	printf("2: List a state's name, capital, and year of joining union given its abbreviation (case insensitive)\n");
	printf("3: List names of all states that joined the union during or after a given year\n");
	printf("4: List names of all states whose names contain a given string (case insensitive)\n");
	printf("5: Quit\n");
}

// performs action selected by the user, returns 1 if user selects
// quit and 0 otherwise
int performUserSelection(State states[], int numStates) {
	int selection;
	scanf("%d", &selection);

	// calls appropriate function based on user's selection, returns
	// 0 if quit is selected
	switch(selection) {
		case 1:
			listAllData(states, numStates);
			break;
		case 2:
			infoGivenAbbrev(states, numStates);
			break;
		case 3:
			statesAfterYear(states, numStates);
			break;
		case 4:
			statesWithString(states, numStates);
			break;
		case 5:
			return 1;
		default:
			printf("Error: invalid selection\n");
	}
	return 0;
}

// prints all info for each state with one line per state, using the
// following format: abbreviation, name, capital, year of joining the union
void listAllData(State states[], int numStates) {
	printf("Format: abbreviation, name, capital, year of joining the union\n");
	for(int i = 0; i < numStates; i++) {
		printf("%s, ", states[i].abbreviation);
		printf("%s, ", states[i].name);
		printf("%s, ", states[i].capital);
		printf("%d\n", states[i].year);
	}
}

// converts string to all uppercase
void strToUpper(char str[]) {
	for(int i = 0; i < strlen(str); i++) {
		str[i] = toupper(str[i]);
	}
}

// prints name, capital, and year of joining the union for a state
// given a case-insensitive user-entered abbreviation; 
// prints an error message if there is no state with that abbrevation
// (assumes that abbreviations in file are capitalized)
void infoGivenAbbrev(State states[], int numStates) {
	// removes newline from input buffer
	getchar();

	char abbrev[3];
	// gets abbreviation from user input, no need
	// to remove newline since abbreviation is always 2 characters
	printf("Please enter abbreviation (2 characters): ");	
	fgets(abbrev, 3, stdin); 

	// converts abbreviation entered by user to uppercase before
	// comparing to data
	strToUpper(abbrev);

	// iterates through states array, prints info if abbreviation
	// is found
	for(int i = 0; i < numStates; i++) {
		if(strcmp(states[i].abbreviation, abbrev) == 0) {
			printf("Format: name, capital, year of joining the union\n");
			printf("%s, ", states[i].name);
			printf("%s, ", states[i].capital);
			printf("%d\n", states[i].year);
			// exits function if matching abbreviation is found
			return;
		}
	}
	// only prints if matching abbreviation is never found
	printf("Error: abbreviation not found.\n");
}

// prints names of states that joined the union during or after
// a given year
void statesAfterYear(State states[], int numStates) {
	int year;
	// gets year from user input
	printf("Please enter minimum year of joining the union: ");
	scanf("%d", &year);

	// iterates through states array, prints name if year is
	// greater than or equal to given year
	for(int i = 0; i < numStates; i++) {
		if(states[i].year >= year)
			printf("%s\n", states[i].name);
	}
}

// prints names of states whose names contain a given string, where
// the comparison is case insensitive
void statesWithString(State states[], int numStates) {
	// removes newline from input buffer
	getchar();

	char str[25];
	// gets abbreviation from user input
	printf("Please enter string: ");
	fgets(str, 25, stdin); 
	removeNewline(str);
	strToUpper(str);

	// iterates through states array, prints name if the name
	// contains the string str
	for(int i = 0; i < numStates; i++) {
		// makes new string to prevent strToUpper from changing
		// the original name
		char currentName[25];
		strcpy(currentName, states[i].name);

		// checks if str is in name, makes comparison case insensitive
		// by ensuring strings are all uppercase before comparing them
		strToUpper(currentName);
		if(strstr(currentName, str) != NULL)
			printf("%s\n", states[i].name);
	}
}
