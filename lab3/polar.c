/*
 * Matthew Zampino
 * Fundamentals of Computing - Lab 3 Part 2
 * Purpose: Given x and y coordinates for a point, this program 
 * calculates and prints the quadrant and polar coordinates
 * (radius, angle in degrees) for that point.
 */

#include <stdio.h>
#include <math.h>

// function prototypes
int get_quadrant(double x, double y);
double get_radius(double x, double y);
double get_angle(double x, double y);
void show_info(int quad, double rad, double ang);

int main() {
	// declare x and y variables
	double x, y;

	// welcome user, receive x and y coordinates from user
	printf("Welcome to Rectangular to Polar Coordinates Converter!\n");
	printf("Enter x coordinate:\n");
	scanf("%lf", &x);
	printf("Enter y coordinate:\n");
	scanf("%lf", &y);

	// calculate and print results
	show_info(get_quadrant(x, y), get_radius(x, y), get_angle(x, y));
	
	return 0;
}

// given x and y values, returns the quadrant based on sign of 
// x and y -- 0 is always assumed to be positive
int get_quadrant(double x, double y) {
	if(x < 0) {
		// both negative
		if(y < 0)
			return 3;
		// x negative, y positive
		return 2;
	}
	// x positive, y negative
	if(y < 0)
		return 4;
	// both positive
	return 1;
}

// calculates and returns the radius using the pythagorean sum 
// of x and y
double get_radius(double x, double y) {
	return sqrt(pow(x, 2) + pow(y, 2));
}

// calculates the angle in radians using atan2, then converts
// to degrees
double get_angle(double x, double y) {
	double ang = atan2(y, x);
	return ang*(180/M_PI);
}

// prints the quadrant and polar coordinates of the point
void show_info(int quad, double rad, double ang) {
	printf("Quadrant: %d\n", quad);
	printf("Polar coordinates (radius, angle in degrees): %g, %g\n", rad, ang);
}
