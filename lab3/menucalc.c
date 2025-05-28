/*
 * Matthew Zampino
 * Fundamentals of Computing - Lab 3 Part 3
 * Purpose: This program uses a text menu to allow the 
 * user to add, subtract, multiply, or divide two
 * numbers of type double.
 */

#include <stdio.h>

// function prototypes

void welcomeUser();
void printMenu();
double add(double num1, double num2);
double subtract(double num1, double num2);
double multiply(double num1, double num2);
double divide(double num1, double num2);
int printResult(int operation, double num1, double num2);

int main() {
	
	// declare variable for operation selection
	int operation;

	// welcome user
	welcomeUser();

	// while loop that runs until zero is entered, which breaks out of the loop
	// (abbreviation for continue, which is a reserved word)
	while(1) {

		// print text menu and capture input for operation selection 
		printMenu();
		scanf("%d", &operation);

		// declare variables for numbers to be used in the calculation
		double x;
		double y;

		// prompt user to enter numbers for the calculation if an operation is selected,
		// terminate program if 0 is entered, and otherwise print error message
		if(operation >= 1 && operation <= 4) {
			printf("Please enter your two numbers in the desired order.\n");
			printf("Example: 1, 2 for subtraction would be 1 - 2\n");
			printf("First number:\n");
			scanf("%lf", &x);
			printf("Second number:\n");
			scanf("%lf", &y);
			printResult(operation, x, y);
		} 
		else if(operation == 0) {
			printf("Goodbye!\n");
			break; 
		}
		else
			printf("Error: please select a valid operation.\n");
		
		printf("\n");
	}

	return 0;
}

// prints welcome message
void welcomeUser() {
	printf("Welcome to Basic Operations Calculator!\n\n");
}
// prints text menu
void printMenu() {
	printf("Please enter the number corresponding to your operation.\n");
	printf("1 for addition\n");
	printf("2 for subtraction\n");
	printf("3 for multiplication\n");
	printf("4 for division\n");
	printf("0 to quit\n");
}
// adds two numbers together and returns the result
double add(double num1, double num2) {
	return num1 + num2;
}
// subtracts num2 from num1 and returns the result
double subtract(double num1, double num2) {
	return num1 - num2;
}
// multiplies num1 by num2 and returns the result
double multiply(double num1, double num2) {
	return num1 * num2;
}
// divides num1 by num2 and returns the result
double divide(double num1, double num2) {
	return num1 / num2;
}
// calculates and prints result of operation
int printResult(int operation, double num1, double num2) {
	switch(operation) {
		case 1:
			printf("Result: (%g) + (%g) = %g\n", num1, num2, add(num1, num2));
			break;
		case 2:
			printf("Result: (%g) - (%g) = %g\n", num1, num2, subtract(num1, num2));
			break;
		case 3:
			printf("Result: (%g) * (%g) = %g\n", num1, num2, multiply(num1, num2));
			break;
		// prints error message if division by zero is attempted
		case 4:
			if(num2 == 0) {
				printf("Error: cannot divide by zero.\n");
				break;
			}
			printf("Result: (%g) / (%g) = %g\n", num1, num2, divide(num1, num2));
			break;
	}
}
