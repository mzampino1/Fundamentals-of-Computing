#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lifefunc.h"

// initializes board with all blank spaces
void makeBlankBoard(char board[][BOARD_SIZE]) {
	for(int i = 0; i < BOARD_SIZE; i++) {
		for(int j = 0; j < BOARD_SIZE; j++) {
			board[i][j] = ' ';
		}
	}
}

// prints board with box around it
void printBoard(char board[][BOARD_SIZE]) {
	// clears the screen
	system("clear");

	// top wall
	printf(" ");
	for(int i = 0; i < BOARD_SIZE; i++)
		printf("-");
	printf("\n");

	// prints content of board with left and right walls
	for(int i = 0; i < BOARD_SIZE; i++) {
		printf("|");
		for(int j = 0; j < BOARD_SIZE; j++)
			printf("%c", board[i][j]);
		printf("|");
		printf("\n");
	}
	
	// bottom wall
	printf(" ");
	for(int i = 0; i < BOARD_SIZE; i++) 
		printf("-");
	printf("\n");
}

// performs interactive mode operation based on character,
// returns 1 if quit is selected and 0 otherwise
int interactiveOperation(char board[][BOARD_SIZE], char operation) {
	// need to put declaration before switch because cannot have
	// declaration after label (e.g. after "case 'a':")
	int row, col;
	switch(operation) {
		case 'a':
			scanf("%d", &row);
			scanf("%d", &col);
			getchar(); // clears newline from input buffer
			
			// ensures valid coordinates have been entered
			if((row >= 0 && row <= BOARD_SIZE) && (col >= 0 && col <= BOARD_SIZE)) {
				addLiveCell(board, row, col);
				printBoard(board);
			} else
				printf("Error: invalid coordinates.\n");
			
			break;
		case 'r':
			scanf("%d", &row);
			scanf("%d", &col);
			getchar(); // clears newline from input buffer
			
			// ensures valid coordinates have been entered
			if(row >= 0 && row <= BOARD_SIZE && col >= 0 && col <= BOARD_SIZE) {
				removeLiveCell(board, row, col);
				printBoard(board);
			} else
				printf("Error: invalid coordinates.\n");
			
			printBoard(board);
			break;
		case 'n':
			nextIteration(board);
			printBoard(board);
			break;
		case 'q':
			printf("Goodbye!\n");
			return 1;
			break;
		case 'p':
			playInfinitely(board);
			break;
		default:
			printf("Error: invalid command, please try again.\n\n");
	}
	return 0;
}

// performs batch operation based on character, assuming file is
// properly formatted
int batchOperation(char board[][BOARD_SIZE], char operation, FILE *fp) {
	int row, col;
	switch(operation) {
		case 'a':
			fscanf(fp, "%d", &row);
			fscanf(fp, "%d", &col);
			addLiveCell(board, row, col);

			// skips newline in file
			fgetc(fp);
			break;
		case 'p':
			fclose(fp);
			// prints original board once before playing
			printBoard(board);
			playInfinitely(board); // this will start an infinite loop
	}
}

// updates oldBoard to newBoard's values
void copyBoard(char oldBoard[][BOARD_SIZE], char newBoard[][BOARD_SIZE]) {
	for(int i = 0; i < BOARD_SIZE; i++) {
		for(int j = 0; j < BOARD_SIZE; j++)
			oldBoard[i][j] = newBoard[i][j];
	}
}

// adds live cell at row, column coordinates (coordinates start at 0)
void addLiveCell(char board[][BOARD_SIZE], int row, int col) {
	// adds live cell if cell is empty
	if(board[row][col] == ' ')
		board[row][col] = 'X';
}

// removes live cell at row, column coordinates (coordinates start at 0)
void removeLiveCell(char board[][BOARD_SIZE], int row, int col) {
	// removes live cell if cell is live
	if(board[row][col] == 'X')
		board[row][col] = ' ';
}

// returns number of neighbors around cell
int countNeighbors(char board[][BOARD_SIZE], int givenRow, int givenCol) {
	int cnt = 0;
	int currentRow, currentCol;
	for(int relRow = -1; relRow <= 1; relRow++) {
		for(int relCol = -1; relCol <= 1; relCol++) {
			// coordinates of neighboring cell being checked
			currentRow = givenRow + relRow;
			currentCol = givenCol + relCol;
			// if statement prevents array out of bounds access
			if((currentRow >= 0 && currentRow < BOARD_SIZE) && (currentCol >= 0 && currentCol < BOARD_SIZE)) {
				// if statement prevents given cell itself from being counted as neighbor
				if(!(currentRow == givenRow && currentCol == givenCol)) {
					if(board[currentRow][currentCol] == 'X')
						cnt++;
				}
			}
		}
	}
	return cnt;
}

// advances currentBoard to next iteration based on rules of the game
void nextIteration(char currentBoard[][BOARD_SIZE]) {
	// temporary board will contain updated board, and needs to
	// start with same values as current board
	char tempBoard[BOARD_SIZE][BOARD_SIZE];
	copyBoard(tempBoard, currentBoard);

	int neighborCnt;

	for(int i = 0; i < BOARD_SIZE; i++) {
		for(int j = 0; j < BOARD_SIZE; j++) {
			neighborCnt = countNeighbors(currentBoard, i, j);

			// handles case where cell is dead
			if(currentBoard[i][j] == ' ') {
				if(neighborCnt == 3)
					tempBoard[i][j] = 'X';	
			}

			// handles case where cell is live
			if(currentBoard[i][j] == 'X') {
				if(!(neighborCnt == 2 || neighborCnt == 3))
					tempBoard[i][j] = ' ';
			}	
		}
	}
	copyBoard(currentBoard, tempBoard);
}

// runs the simulation endlessly
void playInfinitely(char currentBoard[][BOARD_SIZE]) {
	while(1) {
		nextIteration(currentBoard);
		printBoard(currentBoard);
		usleep(100000); // 0.1 seconds per frame of simulation (10 frames per second)
	}
}
