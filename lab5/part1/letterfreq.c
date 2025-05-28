/*
 * Matthew Zampino
 * Fundamentals of Computing - Lab 5 Part 1
 * Purpose: This program counts the frequency of each letter
 * of the alphabet as they appear in a text file. It outputs
 * the number of characters, letters, frequency of each letter,
 * and the percentage for each letter.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// function prototypes
void initializeToZeros(int letterCounts[], int numLetters);
void welcomeUser();
void getFileName(char fileName[]);
int scanText(char fileName[], int letterCounts[]);
int getTotalLetters(int letterCounts[], int numLetters);
void displayTotals(char fileName[], int totalChars, int totalLetters);
void displayLetterInfo(int letterCounts[], int numLetters, int totalLetters);

int main() {

	// declare variables: 
	// number of letters in alphabet
	const int numLetters = 26;
	// file name from user (30 characters or less)
	char fileName[31];
	// array for letter counts
	int letterCounts[numLetters];

	// initialize letterCounts values to zero
	initializeToZeros(letterCounts, numLetters);

	welcomeUser();
	
	getFileName(fileName);

	// assign letter counts and declare + assign appropriate value to
	// variable for total characters
	int totalChars = scanText(fileName, letterCounts);
	// declare + assign appropriate value to variable for total letters
	int totalLetters = getTotalLetters(letterCounts, numLetters);

	// print stats
	displayTotals(fileName, totalChars, totalLetters);
	displayLetterInfo(letterCounts, numLetters, totalLetters);	

	return 0;
}

// intializes all values in array to zero
void initializeToZeros(int letterCounts[], int numLetters) {
	for(int i = 0; i < numLetters; i++)
		letterCounts[i] = 0;
}

// prints welcome message to user
void welcomeUser() {
	printf("Welcome to text file letter frequency counter!\n\n");
}

// retrieve file name from user input
void getFileName(char fileName[]) {
	// uses while loop to reprompt user until 
	while(1) {
		printf("Please enter your file's name: ");
		fgets(fileName, 31, stdin);

		// removes newline character if necessary
		if(fileName[strlen(fileName) - 1] == '\n')
			fileName[strlen(fileName) - 1] = '\0';

		// check if file name is valid
		FILE *test = fopen(fileName, "r");
		if(test == NULL) 
			printf("Error: invalid file name\n\n");
		else {
			fclose(test);
			break;
		}
	}
}

// counts total characters, assigns letterCount values, and 
// returns total character count
int scanText(char fileName[], int letterCounts[]) {
	// declare variables for total character and letter counts
	int totalChars = 0;
	int totalLetters = 0;
	
	// declare file pointer
	FILE *fp = fopen(fileName, "r");

	// iterate until end of file is reached (using break statement)
	while(1) {
		// get current character from file (makes lowercase to ensure counts
		// are case insensitive)
		char currentChar = tolower(fgetc(fp));

		// check if end of file is reached 
		// (before total character count is incremented)
		if(feof(fp))
			break;

		// increment total character count
		totalChars++;
		
		// increments total letter count and appropriate letterCounts[] element
		if(isalpha(currentChar)) {
			totalLetters++;
			// subtracts by 97 (ASCII value for 'a') to increment proper index
			letterCounts[currentChar - 'a']++;
		}
	}
	fclose(fp);

	return totalChars;
}

// returns total number of letters
int getTotalLetters(int letterCounts[], int numLetters) {
	int totalLetters = 0;
	for(int i = 0; i < numLetters; i++) {
		totalLetters += letterCounts[i];
	}
	return totalLetters;
}

// prints total characters and letters in the text file
void displayTotals(char fileName[], int totalChars, int totalLetters) {
	printf("\nGeneral summary for %s:\n", fileName);
	printf("  there were %d total characters\n", totalChars);
	printf("  there were %d letters\n\n", totalLetters);
}

// prints letter counts and letter percentages
void displayLetterInfo(int letterCounts[], int numLetters, int totalLetters) {
	printf("Letter counts:\n");
	// declares print count variable to print 6 letter counts per line
	int printCnt = 0;
	for(int i = 0; i < numLetters; i++) {
		printCnt++;

		// prints letter corresponding to index
		printf("   %c:", 'a' + i);
		// prints count for that letter
		printf("%6d", letterCounts[i]);

		// prints newline if 6 counts have been printed
		if(printCnt % 6 == 0)
			printf("\n");
	}

	printf("\n\nLetter percentages:\n");
	// resets print count variable to 0
	printCnt = 0;
	for(int i = 0; i < numLetters; i++) {
		printCnt++;

		// prints letter corresponding to index
		printf("   %c:", 'a' + i);
		
		// calculates percentage based on total letter count
		float percentage = ((float)(letterCounts[i]) / totalLetters) * 100;
		// print percentage (rounded to nearest tenth) for letter count
		printf("%5.1f%%", percentage);

		// prints newline if 6 counts have been printed
		if(printCnt % 6 == 0)
			printf("\n");
	}
	printf("\n");
}
