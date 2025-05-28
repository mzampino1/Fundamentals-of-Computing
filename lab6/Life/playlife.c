/* 
 * Matthew Zampino
 * Fundamentals of Computing - Lab 6
 * Purpose: This program simulates the animation of Conway's Game of Life
 * on a 40-by-40 board, where live cells are displayed as Xs. It can be
 * used in interactive mode, which asks for user input, or in batch mode,
 * which receives commands from a data file which has its name specified
 * in a command line argument.
 */

#include <stdio.h>
#include "lifefunc.h"

int main(int argc, char *argv[]) {

	char currentBoard[BOARD_SIZE][BOARD_SIZE];
	makeBlankBoard(currentBoard);
	
	// if/else if/else structure used to run interactive or batch mode
	// based on command line arguments

	// interactive mode
	if(argc == 1) {
		printBoard(currentBoard);
		
		char operation;

		// flag used to reprompt user
		int stop = 0;
		while(!stop) {
			printf("COMMAND: ");
			scanf(" %c", &operation);
			getchar(); // clears newline from input buffer
			stop = interactiveOperation(currentBoard, operation);
		}
	}
	
	// batch mode
	else if(argc == 2) {
		FILE *fp = fopen(argv[1], "r");
		// prints error message and returns error code if file does not exist
		if(fp == NULL) {
			printf("Error: the file \"%s\" does not exist.\n", argv[1]);
			return 2;
		}

		// iterates through file, executing appropriate commands
		// will never end if file is properly formatted, since the
		// file will end with an infinite loop as the animation plays
		char operation;
		while(!feof(fp)) {
			fscanf(fp, "%c", &operation);
			batchOperation(currentBoard, operation, fp);
		}
		fclose(fp);
	} 

	// invalid command line input
	else {
		printf("Error: invalid number of command line arguments.\n");
		return 1;
	}

	return 0;
}
