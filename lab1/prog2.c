/*
Matthew Zampino
Fundamentals of Computing
Lab 1 - Part 2

Purpose:
To calculate the distance between two points in a 2D plane
given coordinate values x1, y1, x2, and y2.
*/

#include <stdio.h>
#include <math.h>

int main() {	
	double x1;
	double y1;
	double x2;
	double y2;
	
	double distance;
	
	printf("Welcome to Distance Calculator!\n");
	printf("This program calculates the distance between two points in a 2D plane.\n");
	printf("You may enter integer and decimal values for the coordinates.\n");
	printf("These values can be positive or negative.\n\n");

	printf("Please enter the x value of the first point:\n");
	scanf("%lf", &x1);

	printf("Please enter the y value of the first point:\n");
	scanf("%lf", &y1);

	printf("Please enter the x value of the second point:\n");
	scanf("%lf", &x2);

	printf("Please enter the y value of the second point:\n");
	scanf("%lf", &y2);

	distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

	printf("\nThe distance between point 1 and point 2 is: %g\n", distance);
	
	return 0;
}
