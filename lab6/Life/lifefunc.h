#define BOARD_SIZE 40
void makeBlankBoard(char board[][BOARD_SIZE]);
void printBoard(char board[][BOARD_SIZE]);
int interactiveOperation(char board[][BOARD_SIZE], char operation);
int batchOperation(char board[][BOARD_SIZE], char operation, FILE *fp);
void copyBoard(char oldBoard[][BOARD_SIZE], char newBoard[][BOARD_SIZE]);
void addLiveCell(char board[][BOARD_SIZE], int row, int col);
void removeLiveCell(char board[][BOARD_SIZE], int row, int col);
int countNeighbors(char board[][BOARD_SIZE], int row, int col);
void nextIteration(char currentBoard[][BOARD_SIZE]);
void playInfinitely(char currentBoard[][BOARD_SIZE]);
