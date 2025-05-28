/*
 * Matthew Zampino
 * Fundamentals of Computing - Lab 2 Part 1
 * Purpose: To create a multiplication table with rows Y and columns X
 */

#include <stdio.h>

int main() {

	// welcome user
	printf("Welcome to Multiplication Table Generator!\n");

	// receive input for size
	int x, y;
	printf("Please enter X and Y values (number of columns and rows)\nX: ");
	scanf("%d", &x);
	printf("Y: ");
	scanf("%d", &y);
	
	// first line
	printf("   *  ");
	for(int i = 1; i <= x; i++) {
		printf("%5d", i);
	}
	
	// second line
	printf("\n      ");
	for(int i = 0; i < x; i++) {
		printf("-----");
	}
	
	// remaining lines (table)
	printf("\n");
	for(int i = 1; i <= y; i++) {
		printf("%4d |", i);
		for(int j = 1; j <= x; j++) {
			int product = i*j;
			printf("%5d", product);
		}
		printf("\n");
	}	

	return 0;
}
