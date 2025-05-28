#include <string.h>
#include <math.h>
#include <stdio.h>

#include "pathfunc.h"

// returns file pointer to file specified by user
FILE* openUserFile() {
	// infinite while loop reprompts user until valid file name is entered
	while(1) {
		// gets file name string from user input
		char fileName[20];
		printf("Please enter name of data file: ");
		fgets(fileName, 20, stdin);
		// removes newline from file name if necessary
		if(fileName[strlen(fileName) - 1] == '\n')
			fileName[strlen(fileName) - 1] = '\0';

		FILE* fp = fopen(fileName, "r");
		if(fp == NULL)
			printf("Error: file does not exist.\n\n");
		else
			return fp;
	}
}

// assigns point values from file to Point array, returns number of
// points assigned
int assignFilePoints(Point points[], FILE* fp) {
	// counts number of point values assigned
	int cnt = 0;

	while(1) {
		fscanf(fp, "%f", &points[cnt].x);

		// breaks out of while loop if end of file is reached when
		// attempting fscanf
		if(feof(fp))
			break;
		fscanf(fp, "%f", &points[cnt].y);

		// increments count at end so that the end of file iteration is
		// not considered
		cnt++;
	}

	return cnt;
}

// calculates and returns distance between two points
float calcDistance(Point p1, Point p2) {
	// calculates the x and y components of the displacement from
	// p1 to p2
	float xDist = p2.x - p1.x;
	float yDist = p2.y - p1.y;

	// finds magnitude of distance between p1 and p2
	return sqrt(pow(xDist, 2) + pow(yDist, 2));
}

// calculates and returns the path length for a sequence of points in a Point array
float calcPathLength(Point points[], int numPoints) {
	float pathLength = 0;
	for(int i = 0; i < numPoints - 1; i++) {
		pathLength += calcDistance(points[i], points[i+1]);
	}
	return pathLength;
}

// prints the number of points, the x and y values of the points in 
// a 2 column table, and the path length through the points
void printPointInfo(Point points[], int numPoints, float pathLength) {
	// prints number of points
	printf("There are %d points:\n\n", numPoints);

	// prints table of point coordinates
	printf("   x   |   y\n");
	printf(" ------+--------\n");
	// iterates through the points array, printing each point's x and
	// y value
	for(int i = 0; i < numPoints; i++) {
		printf(" %5g |  %5g\n", points[i].x, points[i].y);
	}

	printf("\n");

	// prints path length through the points
	printf("The length of the path through them is %.4g\n", pathLength);
}
