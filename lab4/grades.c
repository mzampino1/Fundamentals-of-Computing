/*
 * Matthew Zampino
 * Fundamentals of Computing - Lab 4 Part 1
 * Purpose: Given a hard-coded array of grades, this program calculates and prints
 * the number of grades in the array, the average of the grades,
 * and the standard deviation of the grades.
 */

#include <stdio.h>
#include <math.h>

// function prototypes
float findAvg(int grades[], int size);
float findStdDev(int grades[], int size);

int main()
{
	// given array of grades
	int grades[] =
		{ 96,73,62,87,80,63,93,79,71,99,
		  82,83,80,97,89,82,93,92,95,89,
		  71,97,91,95,63,81,76,98,64,86,
		  74,79,98,82,77,68,87,70,75,97,
		  71,94,68,87,79 };
	
	// compute + print size of the array
	int size = sizeof(grades) / sizeof(grades[0]);
	printf("Number of grades in array: %d\n", size);

	// print results of calculations
	printf("Average: %f\n", findAvg(grades, size));
	printf("Standard deviation: %f\n", findStdDev(grades, size));
  
	return 0;
}

// computes average based on the grades array and its size
float findAvg(int grades[], int size) {
	int sum = 0;
	for(int i = 0; i < size; i++) {
		sum += grades[i];
	}
	// casts sum to float type so that float division is performed
	return (float)sum / size;
}

// computes standard deviation based on the grades array and its size
float findStdDev(int grades[], int size) {
	float sum = 0;
	for(int i = 0; i < size; i++) {
		sum += pow(grades[i] - findAvg(grades, size), 2);
	}
	return sqrt(sum / size);
}
