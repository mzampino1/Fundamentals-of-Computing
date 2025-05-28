/*
 * Matthew Zampino - Lab 2 Part 3
 * Fundamentals of Computing
 * Purpose: To generate a graph of the function 9*(0.5+sin(x)*cos(x)) for x
 * from 0.0 to 21.0 with the x-axis running vertically down the page, 
 * and to display the minimum and maximum over the range.
 */

#include <stdio.h>
#include <math.h>

int main() {
	
	// print first two lines of program (introduction, headers)
	printf("Plot for y = 9*(0.5+sin(x)*cos(x)) for x from 0.0 to 21.0\n");
	printf("   X     Y\n");

	// declare min and max variables (scope outside of for loop)
	float maxY = 0.0;
	float minY = 9*(0.5+sin(0.2)*cos(0.2));
	float maxX = 0.2;
	float minX = 0.2;

	// uses for loop to continue until x reaches 21.0
	// for loop used to prevent floating-point rounding errors
	// that could be possible if a while loop was used (e.g. while(x != 21))
	// start incrementation at 1 to make multiplication easier, 
	// incrementing x by 0.2: 21/0.2 = 105
	for(int i = 0; i <= 105; i++) {
		// print x value
		float x = i*0.2;
		printf("%5.2f  ", x);
	
		// print y value
		float y = 9*(0.5+sin(x)*cos(x));
		printf("%5.2f  ", y);

		// check if y value is greater than max or less than min, update variables if so
		if(y > maxY) {
			maxY = y;
			maxX = x;
		}
		if(y < minY) {
			minY = y;
			minX = x;
		}
		
		// use for loop to print number of hashtags based on y value 
		// scale: one hashtag represents 0.5, rounds up to nearest 0.5
		for(float j = 0.0; j < y; j += 0.5) {
			printf("#");
		}	
		printf("\n");
	}

	// print min and max of function
	printf("The maximum of %.2f was at %.2f\n", maxY, maxX);
	printf("The minimum of %.2f was at %.2f\n", minY, minX);
	
	return 0;
}
