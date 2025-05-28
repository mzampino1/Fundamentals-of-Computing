/*
 * Matthew Zampino
 * Fundamentals of Computing - Lab 4 Part 3
 * Purpose: This program displays a text menu that allows the user
 * to access various statistics about the Notre Dame football program's
 * win/loss record over the years. These statistics include: win/loss record 
 * for a given year, years with at least "n" losses or wins, 
 * years with at least "n" non-tie games played, and years with
 * a win percentage greater than or equal to a percentage "n"%.
 * The user is reprompted until "quit" is selected.
 */

#include <stdio.h>

// initializes arrays for wins and losses (as global variables)
#include "nd_data.h"

// function prototypes
int numYears();
void welcomeUser();
int menuSelection();
int performOperation(int selection);
void option1();
void option2();
void option3();
void option4();
void option5();

int main() {

	welcomeUser();

	// flag used for while loop to reprompt user
	int stop = 0;
	while(!stop) {
		// performOperation returns 1 if the "exit" option is selected,
		// stopping the while loop
		stop = performOperation(menuSelection());
	}
	
	printf("\nGoodbye!\n");

	return 0;
}

// returns number of years in array (used to iterate through array)
// can use either wins or losses, since both will always have same length
int numYears() {
	return sizeof(wins)/sizeof(wins[0]);
}

// prints welcome message + instructions for user
void welcomeUser() {
	printf("Welcome to ND Football Statistics!\n");
	printf("Please enter the integer corresponding to your desired action:\n\n");
}

// prints menu and captures input for user's selection
int menuSelection() {
	printf("1: display the record for a given year.\n");
	printf("2: display years with at least \"n\" losses.\n");
	printf("3: display years with at least \"n\" wins.\n");
	printf("4: display years with at least \"n\" non-tie games played.\n");
	printf("5: display years with a win percentage of at least \"n\"%%.\n");
	printf("6: exit\n");
	printf("Enter your choice: ");

	// returns selection entered by user
	int selection;
	scanf("%d", &selection);
	return selection;

}

// uses switch to perform function corresponding with user's selection
// returns 1 if "exit" is selected, 0 otherwise (to be stored in stop flag)
int performOperation(int selection) {
	switch(selection) {
		case 1:
			option1();
			printf("\n");
			return 0;
		case 2:
			option2();
			printf("\n");
			return 0;
		case 3:
			option3();
			printf("\n");
			return 0;
		case 4:
			option4();
			printf("\n");
			return 0;
		case 5:
			option5();
			printf("\n");
			return 0;
		case 6:
			return 1;
		// prints error message to user for invalid selection
		default:
			printf("Error: please enter a valid integer.\n\n");
			return 0;
	}
}

// displays the win/loss record for a given year
void option1() {
	// variable for maximum year to ensure program is usable if
	// arrays are updated
	int maxYear = 1900 + numYears() - 1;

	// uses while loop and if statement to validate input and 
	// reprompt user if input is invalid
	while(1) {
		// 1900 is always earliest year, maxYear is latest year
		printf("Enter the year (1900-%d): ", maxYear);

		int year;
		scanf("%d", &year);
		if(year >= 1900 && year <= maxYear) {
			printf("Wins: %d, Losses: %d\n", wins[year-1900], losses[year-1900]);
			break;
		} else
			printf("Error: please enter a valid year.\n\n");
	}
}

// displays the years with at least "n" losses
void option2() {
	// uses while loop and if statement to validate input and 
	// reprompt user if input is invalid
	while(1) {
		printf("Enter minimum number of losses: ");
		
		int n;
		scanf("%d", &n);
		if(n >= 0) {
			printf("Years with at least %d loss(es):\n", n);

			// uses for loop to print appropriate years
			// printCnt used to print 10 per row
			int printCnt = 0;
			for(int i = 0; i < numYears(); i++) {
				if(losses[i] >= n) {
					printf("%d ", 1900 + i);
					printCnt++;
					if(printCnt == 10) {
						printf("\n");
						printCnt = 0;
					}
				}
			}

			// prints extra line for formatting if number of appropriate 
			// years was not divisble by 10
			if(printCnt)
				printf("\n");
			break;
		} else
			printf("Error: please enter a positive value.\n\n");
	}
}

// displays the years with at least "n" wins
void option3() {
	// uses while loop and if statement to validate input and 
	// reprompt user if input is invalid
	while(1) {
		printf("Enter minimum number of wins: ");
		
		int n;
		scanf("%d", &n);
		if(n >= 0) {
			printf("Years with at least %d win(s):\n", n);

			// uses for loop to print appropriate years
			// printCnt used to print 10 per row
			int printCnt = 0;
			for(int i = 0; i < numYears(); i++) {
				if(wins[i] >= n) {
					printf("%d ", 1900 + i);
					printCnt++;
					if(printCnt == 10) {
						printf("\n");
						printCnt = 0;
					}
				}
			}
			// prints extra line for formatting if number of appropriate 
			// years was not divisble by 10
			if(printCnt)
				printf("\n");
			break;
		} else
			printf("Error: please enter a positive value.\n\n");
	}
}

// displays the years with at least "n" non-tie games played
void option4() {
	// uses while loop and if statement to validate input and 
	// reprompt user if input is invalid
	while(1) {
		printf("Enter minimum number of non-tie games played: ");
		
		int n;
		scanf("%d", &n);
		if(n >= 0) {
			printf("Years with at least %d non-tie game(s) played:\n", n);

			// uses for loop to print appropriate years
			// printCnt used to print 10 per row
			int printCnt = 0;
			for(int i = 0; i < numYears(); i++) {
				// sum wins and losses to get total non-tie games
				if(wins[i]+losses[i] >= n) {
					printf("%d ", 1900 + i);
					printCnt++;
					if(printCnt == 10) {
						printf("\n");
						printCnt = 0;
					}
				}
			}
			// prints extra line for formatting if number of appropriate 
			// years was not divisble by 10
			if(printCnt)
				printf("\n");
			break;
		} else
			printf("Error: please enter a positive value.\n\n");
	}
}


void option5() {
	// uses while loop and if statement to validate input and 
	// reprompt user if input is invalid
	while(1) {
		printf("Enter minimum win percentage (as an integer, e.g. 50)\n");
		printf("(Note: only considers non-tie games): ");
		int n;
		scanf("%d", &n);

		// if statement checks that percentage is valid
		if(n >= 0 && n <= 100) {
			printf("Years with a win percentage of at least %d%:\n", n);

			// uses for loop to print appropriate years
			// printCnt used to print 10 per row
			int printCnt = 0;
			for(int i = 0; i < numYears(); i++) {
				// calculates win percentage for each season using float division
				float winPercentage = ((float)wins[i]) / (wins[i] + losses[i]);
				winPercentage *= 100;

				if(winPercentage >= n) {
					printf("%d ", 1900 + i);
					printCnt++;
					if(printCnt == 10) {
						printf("\n");
						printCnt = 0;
					}
				}
			}
			// prints extra line for formatting if number of appropriate 
			// years was not divisble by 10
			if(printCnt)
				printf("\n");
			break;
		} else 
			printf("Error: please enter a valid win percentage.\n\n");
	}
}
