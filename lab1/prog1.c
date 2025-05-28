/*
Matthew Zampino
Fundamentals of Computing
Lab 1 - Part 1

Purpose:
To display the total number of points scored by a football team
given the number of touchdowns, extra points, field goals, and safeties.
*/

#include <stdio.h>

int main(void) {
	int touchdowns;
	int extraPoints;
	int fieldGoals;
	int safeties;

	int totalPoints;

	printf("Welcome to Football Score Calculator!\n\n");

	printf("How many touchdowns?\n");
	scanf("%d", &touchdowns);
	printf("How many extra points?\n");
	scanf("%d", &extraPoints);
	printf("How many field goals?\n");
	scanf("%d", &fieldGoals);
	printf("How many safeties?\n");
	scanf("%d", &safeties);

	totalPoints = 6*touchdowns + extraPoints + 3*fieldGoals + 2*safeties;

	printf("Total Points: %d\n", totalPoints);

	return 0;
}
