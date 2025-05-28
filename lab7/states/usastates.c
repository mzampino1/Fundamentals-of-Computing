/*
 * Matthew Zampino
 * Fundamentals of Computing - Lab 7 Part 2
 * Purpose: This program reads in data about U.S. states from a csv
 * file, and prompts the user to pick one of four options. These
 * options are: list all data, list a state's name, capital, and year based
 * on a given abbreviation, list all states that joined the union during 
 * or after a given year, or list all states whose names contain a 
 * given string. The user is reprompted until the quit option is
 * selected.
 */

#include "statesfunc.h"

int main() {

	const int ARRAY_SIZE = 100;
	
	// declare array of states
	State states[ARRAY_SIZE];
	
	// declare file pointer to file entered by user
	FILE* fp = openUserFile();

	// assign info to states array and assign number of states
	// to numStates
	int numStates = assignStateInfo(states, fp);
	fclose(fp);

	int stop = 0;
	while(!stop) {
		printTextMenu();
		// if quit is selected, stop will be 1
		stop = performUserSelection(states, numStates);
	}
	printf("Goodbye!\n");

	return 0;
}
