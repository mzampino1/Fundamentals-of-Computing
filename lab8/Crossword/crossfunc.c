// Matthew Zampino
// Fundamentals of Computing - Lab 8

#include "crossfunc.h"

// prints welcome message for user
void welcomeUser(FILE* output) {
	fprintf(output, "Welcome to Anagram Crossword Puzzle Generator!\n");
}

// initializes board to all periods (empty board)
void initializeBoard(char board[][BOARD_DIM]) {
	for(int i = 0; i < BOARD_DIM; i++) {
		for(int j = 0; j < BOARD_DIM; j++) {
			board[i][j] = '.';
		}
	}
}

// prints line that goes on top and bottom of board when displaying
void printLine(FILE* output) {
	for(int i = 0; i < BOARD_DIM + 2; i++)
		fprintf(output, "-");
	fprintf(output, "\n");
}

// displays solution board with box surrounding it
void displaySolnBoard(FILE* output, char board[][BOARD_DIM]) {
	printLine(output);
	for(int i = 0; i < BOARD_DIM; i++) {
		// prints left wall
		fprintf(output, "|");
		for(int j = 0; j < BOARD_DIM; j++) {
			// prints each character in board
			fprintf(output, "%c", board[i][j]);
		}
		// prints right wall
		fprintf(output, "|\n");
	}
	printLine(output);
}

// displays puzzle (unsolved) board with box around it
void displayPuzzleBoard(FILE* output, char board[][BOARD_DIM]) {
	printLine(output);
	for(int i = 0; i < BOARD_DIM; i++) {
		// prints left wall
		fprintf(output, "|");
		for(int j = 0; j < BOARD_DIM; j++) {
			// prints either a hashtag or space depending on value in 
			// board at that point (hashtag if period, space otherwise)
			if(board[i][j] == '.')
				fprintf(output, "#");
			else
				fprintf(output, " ");
		}
		// prints right wall
		fprintf(output, "|\n");
	}
	printLine(output);
}

// displays both boards
void displayBoards(FILE* output, char board[][BOARD_DIM]) {
	fprintf(output, "\nSolution:\n");
	displaySolnBoard(output, board);
	fprintf(output, "\n\nCrossword Puzzle:\n");
	displayPuzzleBoard(output, board);
}

// converts string to all uppercase
void strToUpper(char str[]) {
	for(int i = 0; i < strlen(str); i++)
		str[i] = toupper(str[i]);
}

// returns 1 if every character except last (newline) is in alphabet
int strIsAlpha(FILE* output, char str[], int totalWordsCnt) {
	for(int i = 0; i < strlen(str) - 1; i++)
		if(!isalpha(str[i])) {
			fprintf(output, "Error: word #%d ignored (non-alphabetical character)\n", totalWordsCnt + 1);
			return 0;
		}
	return 1;
}


// check if word entered is only 1 or 0 characters, returns 1 if it is too
// short and 0 otherwise
int isTooShort(FILE* output, char str[], int totalWordsCnt) {
	if(strlen(str) <= 2) {
		fprintf(output, "Error: word #%d ignored (too short)\n", totalWordsCnt + 1);
		return 1;
	}
	return 0;
}

// check if word is too long, skip entire line if it is (returns 1 if it
// is too long, 0 otherwise)
int isTooLong(FILE* output, char str[], FILE* fp, int totalWordsCnt) {
	// if there is no newline at end of string, that means the word 
	// is too long
	if(str[strlen(str) - 1] != '\n') {
		while(1) {
			if(fgetc(fp) == '\n') {
				break;
			}
		}

		fprintf(output, "Error: word #%d ignored (too long)\n", totalWordsCnt + 1);
		return 1;
	}
	return 0;
}

// removes newline from end of string
void removeNewline(char str[]) {
	if(str[strlen(str) - 1] == '\n')
		str[strlen(str) - 1] = '\0';
}

// assigns words in file or standard input to words array, returns number
// of words assigned
int assignStrings(FILE* output, Word words[], FILE* fp) {
	// iterate if tempWord is valid
	int assignedWordsCnt = 0;
	// iterate for every word
	int totalWordsCnt = 0;

	while(assignedWordsCnt < 20) {
		// creates temporary string to check if word is valid before 
		// putting it in the words array
		char tempStr[BOARD_DIM + 2];

		fgets(tempStr, BOARD_DIM + 2, fp);

		// other checks aren't needed if only period has been entered
		if(!(tempStr[0] == '.' && tempStr[1] == '\n')) {
			// ensures that word is valid before removing newline and copying
			// into words array
			if( !isTooLong(output, tempStr, fp, totalWordsCnt) && 
				!isTooShort(output, tempStr, totalWordsCnt) && 
				strIsAlpha(output, tempStr, totalWordsCnt)) {

				removeNewline(tempStr);
				strToUpper(tempStr);

				// copies characters from tempWord to word in words array 
				// (safe because program has already checked that tempWord 
				// is not too long)
				strcpy(words[assignedWordsCnt].str, tempStr);

				// iterates assigned words count
				assignedWordsCnt++;
			}
		} else {
			// breaks out of loop if period has been reached
			break;
		}

		totalWordsCnt++;
	}
	return assignedWordsCnt;
}

// determines if words should be read from user input or from file,
// prints appropriate message if words are being read from user input,
// creates file pointer to file name indicated in command line
// argument, and returns number of words assigned
int readStrings(FILE* output, Word words[], int argc, char *argv[]) {
	
	if(argc == 1) {
		fprintf(output, "Please enter a list of words, then a period:\n");
		assignStrings(output,words, stdin);
	} else {
		// removes newline from file name given in command line argument
		char fileName[strlen(argv[1]) + 1];
		strcpy(fileName, argv[1]);
		removeNewline(fileName);

		FILE* fp = fopen(fileName, "r");
		if(fp != NULL) {
			int cnt = assignStrings(output, words, fp);
			fclose(fp);
			return cnt;
		} else {
			fprintf(output, "Error: invalid file name entered.\n");
			return -1;
		}
	}
}

// swaps the strings in two indices of words array
void swapStrings(Word words[], int i, int j) {
	char temp[BOARD_DIM + 1];
	strcpy(temp, words[i].str);
	strcpy(words[i].str, words[j].str);
	strcpy(words[j].str, temp);
}

// uses bubble sort algorithm to sort words by length
// (iterates through array, comparing adjacent elements and
// swapping if necessary, then repeats this process)
void sortByLength(Word words[], int numWords) {
	for(int i = 0; i < numWords - 1; i++) {

		// last "i" elements are in correct location,
		// so the loop does not need to check those elements
		for(int j = 0; j < numWords - i - 1; j++) {
			if(strlen(words[j].str) < strlen(words[j + 1].str))
				swapStrings(words, j, j + 1);
		}
	}
}

// copies each member of the Word struct from source to destination
void copyWord(Word *dest, Word *source) {
		strcpy(dest->str, source->str);
		dest->row = source->row;
		dest->col = source->col;
		dest->dir = source->dir;
		dest->interIndex = source->interIndex;
}

// copies words from source array to destination array
void copyWords(Word destWords[], Word sourceWords[], int numWords) {
	for(int i = 0; i < numWords; i++)
		copyWord(&destWords[i], &sourceWords[i]);
}

// scrambles each word in an array using strfry, ensuring that no
// scrambled word is equal to the original word
void scrambleStrings(Word words[], int numPlacedWords) {
	for(int i = 0; i < numPlacedWords; i++) {
		// creates temporary string to store original word
		char tempStr[BOARD_DIM + 1];
		strcpy(tempStr, words[i].str);

		// check that word does not contain all same characters
		int allSame = 1;
		for(int i = 0; i < strlen(tempStr) - 1; i++) {
			if(tempStr[i] != tempStr[i + 1])
				allSame = 0;
		}

		// ensures that anagram is different from the original word
		// by scrambling until they are not equal
		if(!allSame) {
			while(strcmp(tempStr, words[i].str) == 0)
				strfry(words[i].str);
		}
	}
}

// changes first word's coordinates to center of board, stores in 
// placedWords
void placeFirstWord(Word words[], Word placedWords[]) {
	// first word is always across
	words[0].dir = across;
	// row is in vertical center
	words[0].row = BOARD_DIM / 2;
	// col is in horizontal center
	words[0].col = (BOARD_DIM / 2) - (strlen(words[0].str)/2);
	copyWord(&placedWords[0], &words[0]);
}

// assigns appropriate direction and coordinates to word 2 based on 
// direction of word 1 and intersection indices
void setDirAndCoords(Word *w1, Word *w2, int w1Match, int w2Match) {
	if(w1->dir == across) {
		w2->dir = down;
		// col is determined by w1Match (shifts word2 right), 
		// row is determined by w2Match (shifts word2 upward)
		w2->col = w1->col + w1Match;
		w2->row = w1->row - w2Match;
		w2->interIndex = w2Match;
	} else {
		w2->dir	= across;
		// row is determined by w1Match (shifts word2 down)
		// col is determined by w2Match (shifts word2 left)
		w2->row = w1->row + w1Match;
		w2->col = w1->col - w2Match;
		w2->interIndex = w2Match;
	}
}

// places word 2 so that it intersects with the word 1,
// if it is a valid intersection;1
// returns 0 if there is no intersection and 1 if there
// is an intersection
int intersectWords(Word *w1, Word *w2, Word placedWords[], int numPlacedWords) {
	// variables to store indices of matching characters
	int w1Match;
	int w2Match;

	int interExists = 0;

	// outer loop iterates through first word
	for(int i = 0; i < strlen(w1->str); i++) {
		// inner loop iterates through second word, checking for
		// matching letters and checks if is valid
		for(int j = 0; j < strlen(w2->str); j++) {
			if(w1->str[i] == w2->str[j]) {
				w1Match = i;
				w2Match = j;

				Word tempWords[20];
				copyWords(tempWords, placedWords, numPlacedWords);
				copyWord(&tempWords[numPlacedWords], w2);
				setDirAndCoords(w1, &tempWords[numPlacedWords], w1Match, w2Match);

				// create temporary board to test populate with temporary
				// list of words
				char tempBoard[BOARD_DIM][BOARD_DIM];
				initializeBoard(tempBoard);
				if(!populateBoard(tempWords, tempBoard, numPlacedWords + 1)) {
					setDirAndCoords(w1, w2, w1Match, w2Match);
					interExists = 1;
				}
			}
		}
	}
	return interExists;
}

// changes other words' (all words after word #1) coordinates to 
// appropriate locations, stores these in placedWords and returns
// number of words placed, also updates pointer to unplaced count
void placeOtherWords(FILE* output, Word words[], int numWords, Word placedWords[], Word unplacedWords[],
					int *unplacedCnt, int *placedCnt, int *passNum) {
	(*passNum)++;
	// ignore first word for the first pass
	int i;
	if(*passNum == 1)
		i = 1;
	else
		i = 0;
		
	// iterates through array of words, checking if each word can successfully 
	// intersect with any previously placed words
	fprintf(output, "\nPass #%d:\n", *passNum);
	int wordSkipped = 0;
	for(i; i < numWords; i++) {
		int intersectionExists = 0;
		for(int j = 0; j < *placedCnt; j++) {
			if(intersectWords(&placedWords[j], &words[i], placedWords, *placedCnt)) {
				copyWord(&placedWords[*placedCnt], &words[i]);
				(*placedCnt)++;
				intersectionExists = 1;
				break;
			}
		}
		// only does this if the word has no intersections
		if(!intersectionExists) {
			fprintf(output, "Skipped word \"%s\"\n", words[i].str);
			copyWord(&unplacedWords[*unplacedCnt], &words[i]);
			(*unplacedCnt)++;
			wordSkipped = 1;
		}
	}
	if(!wordSkipped) {
		fprintf(output, "No words skipped.\n");
	}
}

// puts words on board based on their coordinates and direction, 
// returns 1 if there is an error and 0 if it is successful
int populateBoard(Word placedWords[], char board[][BOARD_DIM], int numPlacedWords) {
	// iterates through array of words, placing words starting at their
	// coordinates either across or down on the board based on direction
	for(int i = 0; i < numPlacedWords; i++) {
		if(placedWords[i].dir == across) {
			for(int j = 0; j < strlen(placedWords[i].str); j++) {
				// ensures word does not go out of bounds
				if(placedWords[i].col + j > 14 || placedWords[i].row < 0) {
					return 1;
				}

				// ensures no overlapping occurs (besides intersecting letter)
				if(j != placedWords[i].interIndex && board[placedWords[i].row][placedWords[i].col + j] != '.') {
					return 1;	
				}

				// ensures there is gap between non-intersecting words
				
				// check down
				if(j != placedWords[i].interIndex 
					&& placedWords[i].row < 14 && board[placedWords[i].row + 1][placedWords[i].col + j] != '.') {
					return 1;
				}
				// check up
				if(j != placedWords[i].interIndex 
					&& placedWords[i].row > 0 && board[placedWords[i].row - 1][placedWords[i].col + j] != '.') {
					return 1;
				}
				// check left if at start
				if(j == 0 && placedWords[i].col > 0 && board[placedWords[i].row][placedWords[i].col - 1] != '.') {
					return 1;
				}
				// check right if at end
				if(j == strlen(placedWords[i].str) - 1 && placedWords[i].col < 14 && board[placedWords[i].row][placedWords[i].col + j + 1] != '.') {
					return 1;
				}

				board[placedWords[i].row][placedWords[i].col + j] = placedWords[i].str[j];
			}
		} else {
			for(int j = 0; j < strlen(placedWords[i].str); j++) {
				// ensures word does not go out of bounds
				if(placedWords[i].row + j > 14) {
					return 1;
				}

				// ensures no overlapping occurs (besides intersecting letter)
				if(j != placedWords[i].interIndex && board[placedWords[i].row + j][placedWords[i].col] != '.') {
					return 1;
				}

				// ensures there is gap between non-intersecting words
				
				// check right
				if(j != placedWords[i].interIndex 
					&& placedWords[i].col < 14 && board[placedWords[i].row + j][placedWords[i].col + 1] != '.') {
					return 1;
				}
				// check left
				if(j != placedWords[i].interIndex 
					&& placedWords[i].col > 0 && board[placedWords[i].row + j][placedWords[i].col - 1] != '.') {
					return 1;
				}
				// check up if at start
				if(j == 0 && placedWords[i].row > 0 && board[placedWords[i].row - 1][placedWords[i].col] != '.') {
					return 1;
				}
				// check down if at end
				if(j == strlen(placedWords[i].str) - 1 && placedWords[i].row < 14 && board[placedWords[i].row + j + 1][placedWords[i].col] != '.') {
					return 1;
				}

				board[placedWords[i].row + j][placedWords[i].col] = placedWords[i].str[j];
			}
		}
	}
	return 0;
}

// prints formatted clues
void displayClues(FILE* output, Word anagrams[], int numWords) {
	fprintf(output, "\nClues: coordinates, direction, anagram\n(coordinates of the start of a word are in row, column format starting at 0)\n\n");
	for(int i = 0; i < numWords; i++) {
		if(anagrams[i].dir == across)
			fprintf(output, "%2d,%2d Across %s\n", anagrams[i].row, anagrams[i].col, anagrams[i].str);
		else
			fprintf(output, "%2d,%2d Down   %s\n", anagrams[i].row, anagrams[i].col, anagrams[i].str);
	}
}
