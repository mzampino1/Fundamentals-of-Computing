// Matthew Zampino
// Fundamentals of Computing - Lab 8

#define _GNU_SOURCE

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BOARD_DIM 15

typedef enum {across, down} Direction;

typedef struct {
	int row;
	int col;
	Direction dir;
	char str[BOARD_DIM + 1];
	int interIndex;
} Word;

// function prototypes
void welcomeUser(FILE* output);
void initializeBoard(char board[][BOARD_DIM]);
void printLine(FILE* output);
void displaySolnBoard(FILE* output, char board[][BOARD_DIM]);
void displayPuzzleBoard(FILE* output, char board[][BOARD_DIM]);
void displayBoards(FILE* output, char board[][BOARD_DIM]);
void strToUpper(char str[]);
int strIsAlpha(FILE* output, char str[], int totalWordsCnt);
int isTooShort(FILE* output, char str[], int totalWordsCnt);
int isTooLong(FILE* output, char str[], FILE* fp, int totalWordsCnt);
void removeNewline(char str[]);
int assignStrings(FILE* output, Word words[], FILE* fp);
int readStrings(FILE* output, Word words[], int argc, char *argv[]);
void swap(Word words[], int i, int j);
void sortByLength(Word words[], int numWords);
void copyWord(Word *dest, Word *source);
void copyWords(Word destWords[], Word sourceWords[], int numWords);
void scrambleStrings(Word words[], int numPlacedWords);
void setDirAndCoords(Word *w1, Word *w2, int w1Match, int w2Match);
int intersectWords(Word *w1, Word *w2, Word placedWords[], int numPlacedWords);
void placeFirstWord(Word words[], Word numPlacedWords[]);
void placeOtherWords(FILE* output, Word words[], int numWords, Word placedWords[], Word unplacedWords[], int *unplacedCnt, int *placedCnt, int *passNum);
int populateBoard(Word placedWords[], char board[][BOARD_DIM], int numWords);
void displayClues(FILE* output, Word anagrams[], int numWords);
