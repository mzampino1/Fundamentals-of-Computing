// Matthew Zampino
// Fundamentals of Computing - Lab 7 Part 2

// include in header file because the FILE* type is defined by
// stdio.h, so whenever this header file is used
// stdio.h must be included
#include <stdio.h>

// declaration for State struct
typedef struct {
	char abbreviation[3];
	// assumes name and capital are 24 characters or less
	char name[25]; 
	char capital[25];
	int year;
} State;

// function prototypes
void removeNewline(char str[]);
FILE* openUserFile();
int assignStateInfo(State states[], FILE* fp);
void printTextMenu();
int performUserSelection(State states[], int numStates);
void listAllData(State states[], int numStates);
void strToUpper(char str[]);
void infoGivenAbbrev(State states[], int numStates);
void statesAfterYear(State states[], int numStates);
void statesWithString(State states[], int numStates);
