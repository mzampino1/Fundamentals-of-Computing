/* 
 * Matthew Zampino
 * Fundamentals of Computing - Lab 8
 * Purpose: This program, given a list of up to 20 words with up to 15 
 * letters each, creates a 15-by-15 crossword puzzle. This list can be
 * provided by the user at runtime, or it can be located in a text file
 * whose name is passed as a command line argument. After the list is
 * provided, the program first prints the completed crossword puzzle.
 * Then, it prints the puzzle itself, which replaces the words with
 * blanks. Finally, the clues are printed, which are randomly shuffled
 * anagrams of the given words. These results can be printed to standard
 * output or to a file.
 */

#include "crossfunc.h"

int main(int argc, char *argv[]) {

	// ensures that number of command line arguments is valid
	if(argc <= 3) {
		FILE* output = stdout;
		if(argc == 3)
			output = fopen(argv[2], "w");

		// create 15x15 board
		char board[BOARD_DIM][BOARD_DIM];
		// populate board with all '.' characters
		initializeBoard(board);

		Word words[20];
		Word placedWords[20];
		// words not placed on first pass
		Word unplacedWords[20];
		
		welcomeUser(output);
	
		int numWords = readStrings(output, words, argc, argv);

		// only continues if file name is valid (readWords returns
		// -1 if file name does not exist)
		if(numWords > 0) {
			
			sortByLength(words, numWords);

			int passNum = 0;

			placeFirstWord(words, placedWords);
			int unplacedCnt = 0;
			int placedCnt = 1;
			placeOtherWords(output, words, numWords, placedWords, unplacedWords, &unplacedCnt, &placedCnt, &passNum);
			
			// extra passes attempting to put unplaced words on board
			if(unplacedCnt > 0) {
				while(1) {
					// stops if all words are placed
					if(unplacedCnt == 0)
						break;
					
					int tempPlacedCnt = placedCnt;

					// words still not placed, acts as buffer to be assigned
					// into unplacedWords for the next pass
					Word stillUnplacedWords[20];

					int stillUnplacedCnt = 0;

					placeOtherWords(output, unplacedWords, unplacedCnt, placedWords, stillUnplacedWords, &stillUnplacedCnt, &placedCnt, &passNum);

					// updating unplaced count for the next iteration
					unplacedCnt = stillUnplacedCnt;
					copyWords(unplacedWords, stillUnplacedWords, unplacedCnt);
					
					// stops if words still remain but cannot
					// be placed
					if(tempPlacedCnt == placedCnt) {
						fprintf(output, "Unable to place any more words.\n");
						break;
					}
				}
			}

			populateBoard(placedWords, board, placedCnt);

			displayBoards(output, board);
			
			// make separate array for anagrams (scrambled words)
			Word anagrams[20];
			copyWords(anagrams, placedWords, placedCnt);
			scrambleStrings(anagrams, placedCnt);

			displayClues(output, anagrams, placedCnt);
			
			fclose(output);
			
		} else if(numWords == 0)
		fprintf(output, "Error: no words entered.\n");

	} else
		printf("Error: invalid number of command line arguments.\n");

	return 0;
}
