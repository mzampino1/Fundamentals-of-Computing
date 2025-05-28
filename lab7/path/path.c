/*
 * Matthew Zampino
 * Fundamentals of Computing - Lab 7 Part 1
 * Purpose: This program reads coordinates of points in an
 * x-y plane from a data file and calculates the path length
 * between those points. It then displays the number of points,
 * the coordinates of the points in a two-column table, and 
 * the path length through the points.
 */

#include <stdio.h>

#include "pathfunc.h"

int main() {

	// declare array of points
	Point points[30];

	// fp points to file entered by user
	FILE* fp = openUserFile();

	// assigns points to array and records number
	// of points in file
	int numPoints = assignFilePoints(points, fp);
	fclose(fp);

	float pathLength = calcPathLength(points, numPoints);

	printf("\n");
	printPointInfo(points, numPoints, pathLength);

	return 0;
}
